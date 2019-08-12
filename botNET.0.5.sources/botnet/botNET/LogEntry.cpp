#include "LogEntry.h"

using namespace System;
using namespace System::Diagnostics;

namespace botNET
{
    namespace Diagnostics
    {
        LogEntry::LogEntry( int type, Object* message, StackFrame* frame, StackTrace* stack )
            : mDateTime( DateTime::Now), mMessage( message ),
              mEntryType( type ),  mFrame( frame ), mTrace( stack )
        {
        }

        LogEntry::~LogEntry()
        {
            Dispose();
        }

        bool LogEntry::get_Disposed()
        {
            return mDisposed;
        }


        int LogEntry::get_EntryType()
        {
            return mEntryType;
        }

        void LogEntry::set_EntryType( int id )
        {
            mEntryType = id;
        }

        // Date property
        DateTime LogEntry::get_Date()
        {
            return mDateTime.Date;
        }

        // Time property
        TimeSpan LogEntry::get_Time()
        {
            return mDateTime.TimeOfDay;
        }

        // Filename property
        String* LogEntry::get_FileName()
        {
            if( mFrame == 0 ) return 0;

            return mFrame->GetFileName();
        }

        // Method property
        MethodBase* LogEntry::get_Method()
        {
            if( mFrame == 0 ) return 0;

            return mFrame->GetMethod();
        }

        // Message property
        System::Object* LogEntry::get_Message()
        {
            return mMessage->ToString();
        }

        // Stack property
        StackTrace* LogEntry::get_Stack()
        {
            return mTrace;
        }

        void LogEntry::Dispose()
        {
            Dispose( true );
            GC::SuppressFinalize( this );
        }

        void LogEntry::Dispose( bool disposing )
        {
            if( disposing )
            {
                mDisposed = true;
            }
        }
    }
}
