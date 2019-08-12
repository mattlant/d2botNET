#ifndef LOGGER_H
#define LOGGER_H

#include "botNET.h"

#include "botNETThread.h"

using namespace System;
using namespace System::Collections;
using namespace System::Threading;

using namespace botNET::Threading;

namespace botNET
{
    namespace Diagnostics
    {
        // forward declarations
        public __gc __interface IOutput;
        public __gc class OutputCollection;
        public __gc class LogEntry;

        public __gc class Logger : public IDisposable
        {
        public:
            Logger();
            Logger( OutputCollection* outputs );
            ~Logger();

            void Dispose();

            // Asynchronous property
            __property bool get_Asynchronous();
            __property void set_Asynchronous( bool async );

            // Disposed property
            __property bool get_Disposed();

            // Enabled property
            __property bool get_Enabled();
            __property void set_Enabled( bool enabled );

            // LogLevel property
            __property LogLevelType get_LogLevel(); 
            __property void set_LogLevel( LogLevelType severity );

            // Outputs property
            __property OutputCollection* get_Outputs();
            __property void set_Outputs( OutputCollection *output );

            // Log functions
            void LogTrace( Object* message );
            void LogTrace( Object* message, StackFrame* frame, StackTrace* stack );
            void LogTrace( String* format, [ParamArray] Object* args[] );
			void LogEvent( Object* message );
            void LogEvent( Object* message, StackFrame* frame, StackTrace* stack );
            void LogEvent( String* format, [ParamArray] Object* args[] );
            void LogWarning( Object* message );
            void LogWarning( Object* message, StackFrame* frame, StackTrace* stack );
            void LogWarning( String* format, [ParamArray] Object* args[] );
            void LogError( Object* message );
            void LogError( Object* message, StackFrame* frame, StackTrace* stack );
            void LogError( String* format, [ParamArray] Object* args[] );
            void LogCritical( Object* message );
            void LogCritical( Object* message, StackFrame* frame, StackTrace* stack );
            void LogCritical( String* format, [ParamArray] Object* args[] );

            // Log functions
            void Log( LogEntry* entry );
            void Log( int type, Object* message );
            void Log( int type, Object* message, StackFrame* frame, StackTrace* stack );

            //
            void Clear();
            void Flush();

        protected:
            void Dispatch( LogEntry* entry );
            void EntryDispatchThread();
            virtual void Dispose( bool disposing );

        protected:
            bool mEnabled;
            bool mAsynchronous;
            bool mDisposed;
            botNETThread* mThread;
            LogLevelType mLogLevel;
            OutputCollection* mOutputs;
            Queue* mEntryQueue;
            ManualResetEvent* mDispatchEvent;
        };
    }
}

#endif
