#pragma once


namespace botNET
{

	public __gc class YouAreAFuckingIdiotException : public ApplicationException
	{
	public:
		YouAreAFuckingIdiotException(String* reason) : ApplicationException(reason) {}
	};

	public __gc class YouShouldntBeCodingException : public YouAreAFuckingIdiotException
	{
	public:
		YouShouldntBeCodingException (String* reason) : YouAreAFuckingIdiotException(reason) {}
	};

	namespace Units
	{

		public __gc class UnitBase;

		public __gc class UnitException : public Exception
		{
		public:
			UnitException(String* msg, UnitBase* unit);
			__property UnitBase* get_Unit();
		private:
			UnitBase* _unit;
		};

		public __gc class InvalidUnitException : public UnitException
		{
		public:
			InvalidUnitException(UnitBase* unit);
			InvalidUnitException(String* msg, UnitBase* unit);
		};

		public __gc class InvalidUnitTypeException : public UnitException
		{
		public:
			InvalidUnitTypeException(UnitBase* unit);
			InvalidUnitTypeException(String* msg, UnitBase* unit);
		};

		public __gc class UnitOutOfRangeException : public UnitException
		{
		public:
			UnitOutOfRangeException(UnitBase* unit);
			UnitOutOfRangeException(String* msg, UnitBase* unit);
		};


	}

}