#pragma once

namespace botNET
{
	namespace Diagnostics
	{

		__gc public class Log
		{
		public:
			static void WriteLine(String* line);

		private public:
			static StreamWriter* logger;
			static String* file;

		};

	}

}
