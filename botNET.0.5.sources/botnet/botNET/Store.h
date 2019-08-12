#pragma once


namespace botNET
{
	namespace Units
	{
		__gc public class Item;
	}

	__gc public class Store
	{
	public:
		static void Repair();
		static void Repair(botNET::Units::Item * item);

	};

}
