#ifndef CONVERTER_H
#define CONVERTER_H

using namespace System;

namespace botNET
{
	__gc private __sealed class Converter
	{
	private:
		static unsigned char HexToDigit(__wchar_t c);

	public:
		static unsigned char ToByteArray(String __gc* s) __gc[];
	};
}

#endif