#ifndef IOUTPUT_H
#define IOUTPUT_H

#include "botNET.h"

using namespace System;

namespace botNET
{
    namespace Diagnostics
    {
        // forward declarations
        public __gc class LogEntry;

        public __gc __interface IOutput : public IDisposable
        {
        public:
            // AutoFlush property
            __property bool get_AutoFlush();
            __property void set_AutoFlush( bool autoflush );

            // Disposed property
            __property bool get_Disposed();

            // LogLevel property
            __property LogLevelType get_LogLevel();
            __property void set_LogLevel( LogLevelType severity );

            void Clear();
            void Flush();
            void Log( LogEntry* entry );
        };
    }
}

#endif