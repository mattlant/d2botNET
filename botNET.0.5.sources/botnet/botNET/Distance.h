#ifndef DISTANCE_H
#define DISTANCE_H


namespace botNET
{
	namespace Units 
	{
		public __gc class UnitBase;
	}

	namespace Mapping
	{

		public __sealed __gc class Distance
		{
		public:
			static float Manhattan(float x1, float y1, float x2, float y2); 
			static int Manhattan(int x1, int y1, int x2, int y2); 
			static float Manhattan(System::Drawing::Point c1, System::Drawing::Point c2) ;
			static float Euclidian(float x1, float y1, float x2, float y2) ;
			static int Euclidian(int x1, int y1, int x2, int y2) ;
			static float Euclidian(System::Drawing::Point c1, System::Drawing::Point c2) ;
			static float EuclidianNoSqrt(float x1, float y1, float x2, float y2) ;
			static int EuclidianNoSqrt(int x1, int y1, int x2, int y2) ;
			static float EuclidianNoSqrt(System::Drawing::Point c1, System::Drawing::Point c2) ;
			static float DiagShortcut(float x1, float y1, float x2, float y2) ;
			static int DiagShortcut(int x1, int y1, int x2, int y2) ;
			static float DiagShortcut(System::Drawing::Point c1, System::Drawing::Point c2) ;
			static float MaxDxDy(float x1, float y1, float x2, float y2) ;
			static int MaxDxDy(int x1, int y1, int x2, int y2) ;
			static float MaxDxDy(System::Drawing::Point c1, System::Drawing::Point c2) ;
			static float GetAngle(float x1, float y1, float x2, float y2) ;
			static float GetAngle(System::Drawing::Point c1, System::Drawing::Point c2) ;

		};

	}

}


#endif