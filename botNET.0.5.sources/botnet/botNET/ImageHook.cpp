#include "botnet.h"
#include ".\imagehook.h"

#include ".\d2gfx.h"
#include ".\d2client.h"
#include ".\d2cmp.h"
#include ".\game.h"

using namespace System::IO;

void *memcpy2(void *dest, const void *src, size_t count)
{
	return (char *)memcpy(dest, src, count)+count;
}

//file helpers

HANDLE OpenFileRead(char *filename)
{
	return CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}

DWORD ReadFile(HANDLE hFile, void *buf, DWORD len)
//NOTE :- validates len bytes of buf
{
	DWORD numdone = 0;
	ReadFile(hFile, buf, len, &numdone, NULL);
	return numdone;
}

char *ReadFileLine(char *str, int len, HANDLE hFile)
{
	char ch, *p = str;
	while (--len) {
		if (!ReadFile(hFile, &ch, 1)) break;
		if ((*p++ = ch) == '\n') break;
	}
	*p = 0;
	return str[0]?str:0;
}

BYTE *AllocReadFile(char *filename)
{
	HANDLE hFile = OpenFileRead(filename);
	int filesize = GetFileSize(hFile, 0);
	if (filesize <= 0) return 0;
	BYTE *buf = new BYTE[filesize];
	ReadFile(hFile, buf, filesize);
	CloseHandle(hFile);
	return buf;
}

CellFile * LoadBmpCellFile(BYTE *buf1, int width, int height)
{
	BYTE *buf2 = new BYTE[(width*height*2)+height], *dest = buf2;

	for (int i = 0; i < height; i++) {
		BYTE *src = buf1+(i*((width+3)&-4)), *limit = src+width;
		while (src < limit) {
			BYTE *start = src, *limit2 = min(limit, src+0x7f), trans = !*src;
			do src++; while ((trans == (BYTE)!*src) && (src < limit2));
			if (!trans || (src < limit)) *dest++ = (trans?0x80:0)+(src-start);
			if (!trans) while (start < src) *dest++ = *start++;
		}
		*dest++ = 0x80;
	}

	static DWORD dc6head[] = {6, 1, 0, 0xeeeeeeee, 1, 1, 0x1c,  0, -1, -1, 0, 0, 0, -1, -1};
	dc6head[8] = width;
	dc6head[9] = height;
	BYTE *ret = new BYTE[dc6head[13] = sizeof(dc6head)+(dc6head[14] = dest-buf2)+3];
	memset(memcpy2(memcpy2(ret, dc6head, sizeof(dc6head)), buf2, dc6head[14]), 0xee, 3);
	delete buf2;

	return (CellFile *)ret;
}

CellFile * coreLoadBmpCellFile(char *filename)
{
	BYTE *ret = 0;
		
	BYTE *buf1 = AllocReadFile(filename);
	if(!buf1)
	{
		botNET::Game::Print(S"Could not read file");
		return NULL;
	}
	BITMAPFILEHEADER *bmphead1 = (BITMAPFILEHEADER *)buf1;
	BITMAPINFOHEADER *bmphead2 = (BITMAPINFOHEADER *)(buf1+sizeof(BITMAPFILEHEADER));
	if ((bmphead1->bfType == 'MB') && (bmphead2->biBitCount == 8) && (bmphead2->biCompression == BI_RGB)) {
		ret = (BYTE *)LoadBmpCellFile(buf1+bmphead1->bfOffBits, bmphead2->biWidth, bmphead2->biHeight);
	}
	else
		botNET::Game::Print(S"File was not in right format");
	delete buf1;

	return (CellFile *)ret;
}

CellFile *coreInitCellFile(CellFile *cf)
{
	if (cf) D2CMP::InitCellFile(cf, &cf, "?", 0, -1, "?");
	return cf;
}

void coreDeleteCellFile(CellFile *cf)
{
	if (cf) {
		D2CMP::DeleteCellFile(cf);
		delete cf;
	}
}


namespace botNET
{
	namespace Drawing
	{


		ImageHook::ImageHook(String * ImageName, int xPos, int yPos) : ScreenHook(xPos, yPos, 0xFF, (ScreenHookTransparency)1)
		{
			char __nogc* pStr = static_cast<char*>(Marshal::StringToHGlobalAnsi(ImageName).ToPointer()); 
			if(ImageName->IndexOf(S":", 1, 1))
			{
				if(!File::Exists(ImageName))
					throw new ArgumentException("File does not exist");
				image = coreLoadBmpCellFile(pStr);
				image = coreInitCellFile(image);
			}
			else
			{
				image = D2CLIENT::LoadUIImage(pStr);
			}
			Marshal::FreeHGlobal(pStr);
			imagename = ImageName;
			layer = -1;
			frame = 0;
			framespeed = frameskip = 2;
			this->_size = System::Drawing::Size(image->Blocks[0]->width, image->Blocks[0]->height);
			animated = false;
		}

		ImageHook::ImageHook(String * ImageName, int xPos, int yPos, int Layer) : ScreenHook(xPos, yPos, 0xFF, (ScreenHookTransparency)1)
		{
			char __nogc* pStr = static_cast<char*>(Marshal::StringToHGlobalAnsi(ImageName).ToPointer()); 
			if(ImageName->IndexOf(S":", 1, 1))
			{
				if(!File::Exists(ImageName))
					throw new ArgumentException("File does not exist");
				image = coreLoadBmpCellFile(pStr);
				image = coreInitCellFile(image);
			}
			else
			{
				image = D2CLIENT::LoadUIImage(pStr);
			}
			Marshal::FreeHGlobal(pStr);
			imagename = ImageName;
			layer = Layer;
			frame = 0;
			framespeed = frameskip = 2;
			this->_size = System::Drawing::Size(image->Blocks[0]->width, image->Blocks[0]->height);
			animated = false;
		}

		ImageHook::ImageHook(String * ImageName, int xPos, int yPos, int Layer, bool IsAnimated) : ScreenHook(xPos, yPos, 0xFF, (ScreenHookTransparency)1)
		{
			char __nogc* pStr = static_cast<char*>(Marshal::StringToHGlobalAnsi(ImageName).ToPointer()); 
			if(ImageName->IndexOf(S":", 1, 1))
			{
				if(!File::Exists(ImageName))
					throw new ArgumentException("File does not exist");
				image = coreLoadBmpCellFile(pStr);
				image = coreInitCellFile(image);
			}
			else
			{
				image = D2CLIENT::LoadUIImage(pStr);
			}
			Marshal::FreeHGlobal(pStr);
			imagename = ImageName;
			layer = Layer;
			frame = 0;
			framespeed = frameskip = 2;
			this->_size = System::Drawing::Size(image->Blocks[0]->width, image->Blocks[0]->height);
			animated = IsAnimated;
		}

		ImageHook::ImageHook(String * ImageName, int xPos, int yPos, int Layer, bool IsAnimated, bool Exposed) : ScreenHook(xPos, yPos, 0xFF, (ScreenHookTransparency)1)
		{
			char __nogc* pStr = static_cast<char*>(Marshal::StringToHGlobalAnsi(ImageName).ToPointer()); 
			if(ImageName->IndexOf(S":", 1, 1))
			{
				if(!File::Exists(ImageName))
					throw new ArgumentException("File does not exist");
				image = coreLoadBmpCellFile(pStr);
				image = coreInitCellFile(image);
			}
			else
			{
				image = D2CLIENT::LoadUIImage(pStr);
			}
			Marshal::FreeHGlobal(pStr);
			imagename = ImageName;
			layer = Layer;
			frame = 0;
			framespeed = frameskip = 2;
			this->_size = System::Drawing::Size(image->Blocks[0]->width, image->Blocks[0]->height);
			animated = IsAnimated;
			this->Exposed = Exposed;
		}

		ImageHook::~ImageHook(void)
		{
			if(imagename->IndexOf(S":", 1, 1))
				coreDeleteCellFile(image);
			else
				D2CLIENT::UnloadUIImage(image);
		}

		void ImageHook::Draw()
		{
			__super::Draw();
			CellContext img;
			img.ptCellFileUnk = 0;
			img.ptCellFile = image;
			img.frame = frame;
			img._3 = 0;
			//RECT rect;
			//rect.left = this->_point.X;
			//rect.top = this->_point.Y;
			//rect.right = this->_point.X + this->_size.Width;
			//rect.bottom = this->_point.Y + this->_size.Height; 
			D2GFX::PrintImage(&img, this->_point.X, this->_point.Y + this->_size.Height, layer, 5, 0);
			//D2GFX::PrintImageNonStatic(&img, this->_point.X, this->_point.Y + this->_size.Height, &rect, -1);

			if(animated)
			{
				if(--frameskip <= 0)
				{
					frameskip = framespeed;
					if(--frame < 0)
						frame = image->frames - 1;
				}		
			}
		}

	}
}

