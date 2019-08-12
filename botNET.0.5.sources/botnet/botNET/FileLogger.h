#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "botNET.h"

#include "IOutput.h"
#include "OutputBase.h"

using namespace System;
using namespace System::Xml;

namespace botNET
{
    namespace Diagnostics
    {
        // forward declaractions
        public __gc class LogEntry;

        public __gc __abstract class FileLogger : public OutputBase
        {
        public:
            FileLogger( String* filename );
            FileLogger( String* filename, bool append );

            // AutoSave property - on log dispose
            __property bool get_AutoSave();
            __property void set_AutoSave( bool autoSave );

            // OutputFilename property
            __property String* get_OutputFile();
            __property void set_OutputFile( String* filename );

            virtual void Load( String* filename ) = 0;
            virtual void Save( String* filename ) = 0;

            virtual void Log( LogEntry* entry );

        protected:
            virtual void Dispose( bool disposing );

        protected:
            bool mAutoSave;
            String* mOutputFile;
        };
    }
}

#endif
