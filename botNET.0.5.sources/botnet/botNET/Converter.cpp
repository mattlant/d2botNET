#include "botnet.h"

#include "Converter.h"

using namespace System;

namespace botNET
{
	unsigned char Converter::HexToDigit(__wchar_t c)
	{
		switch (c)
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				return (unsigned char) (c - '0');
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
				return (unsigned char) (c - 'a' + 10);
			default:
				return 0;
		}
	}

	unsigned char Converter::ToByteArray(String __gc* s) __gc[]
	{
		s = s->ToLower()->Replace(S"-", S"")->Replace(S" ", S"")->Replace(S"\t", S"");

		if (s->Length % 2 != 0)
			return 0;

		for (int i = 0; i < s->Length; i++)
			if (!((s->Chars[i] >= 'a' && s->Chars[i] <= 'f') || (s->Chars[i] >= '0' && s->Chars[i] <= '9')))
				return 0;

		unsigned char a __gc[] = new unsigned char __gc[s->Length / 2];

		for (int i = 0; i < a->Length; i++)
			a[i] = (unsigned char) ((HexToDigit(s->Chars[2 * i]) * 16) + HexToDigit(s->Chars[2 * i + 1]));

		return a;
	}
}