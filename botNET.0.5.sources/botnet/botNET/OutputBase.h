#ifndef OUTPUTBASE_H
#define OUTPUTBASE_H

#include "botNET.h"

#include "IOutput.h"

using namespace System;

namespace botNET
{
    namespace Diagnostics
    {
        // forward declarations
        public __gc class LogEntry;

        public __gc __abstract class OutputBase : public IOutput
        {
        public:
            OutputBase();
            ~OutputBase();

            // AutoFlush property
            __property bool get_AutoFlush();
            __property void set_AutoFlush( bool autoflush );

            // Disposed property
            __property bool get_Disposed();

            // LogLevel property
            __property LogLevelType get_LogLevel();
            __property void set_LogLevel( LogLevelType severity );

            void Dispose();

            virtual void Log( LogEntry* entry ) = 0;
            virtual void DoLog( LogEntry* entry ) = 0;

        protected:
            virtual void Dispose( bool disposing );

        protected:
            bool mAutoFlush;
            bool mDisposed;
            LogLevelType mLogLevel;
        };
    }
}

#endif
