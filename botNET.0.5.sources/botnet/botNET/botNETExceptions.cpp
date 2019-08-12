
#include "botnet.h"
#include "botnetexceptions.h"

#include "unitbase.h"


namespace botNET
{

	namespace Units 
	{

		///// UNIT EXCEPTION
		UnitException::UnitException(String* msg, UnitBase* unit) : Exception(msg)
		{
			this->_unit = unit;  
		} 

		UnitBase* UnitException::get_Unit()
		{
			return this->_unit;
		}

		//INVALID UNIT EXCEPTION
		InvalidUnitException::InvalidUnitException(UnitBase* unit) : UnitException("Unit is Invalid.", unit) 
		{}

		InvalidUnitException::InvalidUnitException(String* msg, UnitBase* unit) : UnitException(msg, unit) 
		{}

		//INVALID UNIT TYPE EXCEPTION
		InvalidUnitTypeException::InvalidUnitTypeException(UnitBase* unit) : UnitException("The passed Units' type is invalid.", unit) 
		{}

		InvalidUnitTypeException::InvalidUnitTypeException(String* msg, UnitBase* unit) : UnitException(msg, unit) 
		{}

		//INVALID UNIT TYPE EXCEPTION
		UnitOutOfRangeException::UnitOutOfRangeException(UnitBase* unit) : UnitException("Unit is out of range.", unit) 
		{}

		UnitOutOfRangeException::UnitOutOfRangeException(String* msg, UnitBase* unit) : UnitException(msg, unit) 
		{}


	}

}