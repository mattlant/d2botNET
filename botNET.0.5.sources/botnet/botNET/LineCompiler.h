#ifndef LINECOMPILER_H
#define LINECOMPILER_H

#include "CompilerEnum.h"

using namespace System;
using namespace System::CodeDom::Compiler;

namespace botNET
{
	namespace Compiler
	{
		__gc public __sealed class LineCompiler
		{
		private:
			static void CheckAndRootPaths(String * files[]);
			static void AddReferences(CompilerParameters * params);

		public:
			static void Execute(String * code, CompilerEnum lang);
			static void ExecuteOnNewThread(String * code, CompilerEnum lang);
			static System::Reflection::Assembly * CompileInMemory(String * files[], CompilerEnum lang);
			static bool CompileToDisk(String * files[], CompilerEnum lang, String * outfile, bool silent);

		private:
			__gc __sealed class ExecuteThreadStarter
			{
			private:
				String * _code;
				CompilerEnum _lang;

			public:
				ExecuteThreadStarter(String * code, CompilerEnum lang);

				void Start();
			};
		};
	}
}

#endif