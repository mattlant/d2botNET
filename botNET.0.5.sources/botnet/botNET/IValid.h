#ifndef IVALID_H
#define IVALID_H

namespace botNET
{
	__gc public __interface IValid
	{
	public:
		bool IsValid();
		void IsValidEx();
	};
}

#endif