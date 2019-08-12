#ifndef LOGENTRY_H
#define LOGENTRY_H

#include "botNET.h"

using namespace System;
using namespace System::Diagnostics;
using namespace System::Reflection;

namespace botNET
{
    namespace Diagnostics
    {
        public __gc class LogEntry : public IDisposable
        {
        public:
            LogEntry( int type, Object* message, StackFrame* frame, StackTrace* stack );
            ~LogEntry();

            // EntryType property
            __property int get_EntryType();
            __property void set_EntryType( int id );

            // Date property
            __property DateTime get_Date();

            // Disposed property
            __property bool get_Disposed();

            // Time property
            __property TimeSpan get_Time();

            // Filename property
            __property String* get_FileName();

            // Method property
            __property MethodBase* get_Method();

            // Message property
            __property Object* get_Message();

            // Stack property
            __property StackTrace* get_Stack();

            void Dispose();

        protected:
            virtual void Dispose( bool disposing );

        protected:
            bool mDisposed;
            DateTime mDateTime;
            StackFrame* mFrame;
            StackTrace* mTrace;
            Object* mMessage;
            int mEntryType;
        };
    }
}

#endif
