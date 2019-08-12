#include "botnet.h"
#include ".\distance.h"
#include "distance.h"
#include "unitbase.h"




namespace botNET
{
	namespace Mapping
	{

		float Distance::Manhattan(float x1, float y1, float x2, float y2) 
		{
			return Math::Abs(x2-x1) + Math::Abs(y2-y1);
		}

		int Distance::Manhattan(int x1, int y1, int x2, int y2) 
		{
			return Math::Abs(x2-x1) + Math::Abs(y2-y1);
		}

		float Distance::Manhattan(System::Drawing::Point c1, System::Drawing::Point c2) 
		{
			return Manhattan((float)c1.X, (float)c1.Y, (float)c2.X, (float)c2.Y);
		}

		float Distance::Euclidian(float x1, float y1, float x2, float y2) 
		{
			return (float)Math::Sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		}

		int Distance::Euclidian(int x1, int y1, int x2, int y2) 
		{
			return (int)Math::Sqrt((double)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
		}

		float Distance::Euclidian(System::Drawing::Point c1, System::Drawing::Point c2) 
		{
			return Manhattan((float)c1.X, (float)c1.Y, (float)c2.X, (float)c2.Y);
		}

		float Distance::EuclidianNoSqrt(float x1, float y1, float x2, float y2) 
		{
			return (float)Math::Floor((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		}

		int Distance::EuclidianNoSqrt(int x1, int y1, int x2, int y2) 
		{
			return (int)Math::Floor((double)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
		}

		float Distance::EuclidianNoSqrt(System::Drawing::Point c1, System::Drawing::Point c2) 
		{
			return EuclidianNoSqrt((float)c1.X, (float)c1.Y, (float)c2.X, (float)c2.Y);
		}

		float Distance::DiagShortcut(float x1, float y1, float x2, float y2) 
		{
			float dy = Math::Abs(y2-y1);
			float dx = Math::Abs(x2-x1);
			if (dy <= dx) return (float)(dy*0.414 + dx); else return (float)(dx*0.414 + dy);
		}

		int Distance::DiagShortcut(int x1, int y1, int x2, int y2) 
		{
			float dy = (float)Math::Abs(y2-y1);
			float dx = (float)Math::Abs(x2-x1);
			if (dy <= dx) return (int)(dy*0.414 + dx); else return (int)(dx*0.414 + dy);
		}

		float Distance::DiagShortcut(System::Drawing::Point c1, System::Drawing::Point c2) 
		{
			return DiagShortcut((float)c1.X, (float)c1.Y, (float)c2.X, (float)c2.Y);
		}

		float Distance::MaxDxDy(float x1, float y1, float x2, float y2) 
		{
			float dy = Math::Abs(y2-y1);
			float dx = Math::Abs(x2-x1);
			return (dx>dy)?dx:dy;
		}

		int Distance::MaxDxDy(int x1, int y1, int x2, int y2) 
		{
			int dy = Math::Abs(y2-y1);
			int dx = Math::Abs(x2-x1);
			return (dx>dy)?dx:dy;
		}

		float Distance::MaxDxDy(System::Drawing::Point c1, System::Drawing::Point c2) 
		{
			return MaxDxDy((float)c1.X, (float)c1.Y, (float)c2.X, (float)c2.Y);
		}

		float Distance::GetAngle(float x1, float y1, float x2, float y2) 
		{
			return (float)Math::Floor((Math::Atan2(y2-y1 , x2-x1)) * 180 / 3.1415);
		}

		float Distance::GetAngle(System::Drawing::Point c1, System::Drawing::Point c2) 
		{
			return (float)Math::Floor((Math::Atan2((float)c2.Y-(float)c1.Y , (float)c2.X-(float)c1.X)) * 180 / 3.1415);
		}

	}

}