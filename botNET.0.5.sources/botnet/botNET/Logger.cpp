// This is the main DLL file.

#include "IOutput.h"
#include "LogEntry.h"
#include "Logger.h"
#include "OutputCollection.h"

using namespace System;
using namespace System::Collections;
using namespace System::Diagnostics;

using namespace botNET::Threading;

namespace botNET
{
    namespace Diagnostics
    {
        Logger::Logger()
            : mAsynchronous( true ), mOutputs( new OutputCollection() ),
              mDispatchEvent( new ManualResetEvent( true ) ),
              mEntryQueue( new Queue() )
        {
            if( mAsynchronous )
            {
                mThread = new botNETThread( new ThreadStart( this, &Logger::EntryDispatchThread ), ThreadType::Persistant );
                mThread->Name = S"Logger Thread";
                mThread->Start();
            }
        }

        Logger::Logger( OutputCollection* outputs )
            : mAsynchronous( true ), mOutputs( outputs ),
              mDispatchEvent( new ManualResetEvent( true ) ),
              mEntryQueue( new Queue() )
        {
        }

        Logger::~Logger()
        {
            Dispose();
        }

        bool Logger::get_Disposed()
        {
            return mDisposed;
        }

        bool Logger::get_Asynchronous()
        {
            return mAsynchronous;
        }

        void Logger::set_Asynchronous( bool async )
        {
            mAsynchronous = async;
            // need to join the thread?
        }

        bool Logger::get_Enabled()
        {
            return mEnabled;
        }

        void Logger::set_Enabled( bool enabled )
        {
            mEnabled = enabled;
        }

        LogLevelType Logger::get_LogLevel()
        {
            return mLogLevel;
        }

        void Logger::set_LogLevel( LogLevelType severity )
        {
            mLogLevel = severity;
        }

        OutputCollection* Logger::get_Outputs()
        {
            return mOutputs;
        }

        void Logger::set_Outputs( OutputCollection *output )
        {
            mOutputs = output;
        }

        void Logger::Dispose()
        {
            Dispose( true );
            GC::SuppressFinalize( this );
        }

        void Logger::Dispose( bool disposing )
        {
            if( disposing )
            {
                IEnumerator* enumerator = mOutputs->GetEnumerator();
                while( enumerator->MoveNext() )
                {
                    // get this output instance
                    IOutput* output = static_cast<IOutput*>(enumerator->Current);
                    output->Dispose();
                }

                mDisposed = true;
            }
        }

        void Logger::LogTrace( Object* message )
        {
            Log( new LogEntry( LogLevelType::Trace, message, 0, 0 ) );
        }

        void Logger::LogTrace( String* format, [ParamArray] Object* args[] )
        {
			LogTrace(String::Format(format, args));
        }

        void Logger::LogTrace( Object* message, StackFrame* frame, StackTrace* stack )
        {
            Log( new LogEntry( LogLevelType::Trace, message, frame, stack ) );
        }

        void Logger::LogEvent( Object* message )
        {
            Log( new LogEntry( LogLevelType::Event, message, 0, 0 ) );
        }

        void Logger::LogEvent( Object* message, StackFrame* frame, StackTrace* stack )
        {
            Log( new LogEntry( LogLevelType::Event, message, frame, stack ) );
        }

         void Logger::LogEvent( String* format, [ParamArray] Object* args[] )
        {
			LogEvent(String::Format(format, args));
        }

       void Logger::LogWarning( Object* message )
        {
            Log( new LogEntry( LogLevelType::Warning, message, 0, 0 ) );
        }

        void Logger::LogWarning( Object* message, StackFrame* frame, StackTrace* stack )
        {
            Log( new LogEntry( LogLevelType::Warning, message, frame, stack ) );
        }

        void Logger::LogWarning( String* format, [ParamArray] Object* args[] )
        {
			LogWarning(String::Format(format, args));
        }

       void Logger::LogError( Object* message )
        {
            Log( new LogEntry( LogLevelType::Error, message, 0, 0 ) );
        }

        void Logger::LogError( Object* message, StackFrame* frame, StackTrace* stack )
        {
            Log( new LogEntry( LogLevelType::Error, message, frame, stack ) );
        }

        void Logger::LogError( String* format, [ParamArray] Object* args[] )
        {
			LogError(String::Format(format, args));
        }

       void Logger::LogCritical( Object* message )
        {
            Log( new LogEntry( LogLevelType::Critical, message, 0, 0 ) );
        }

        void Logger::LogCritical( Object* message, StackFrame* frame, StackTrace* stack )
        {
            Log( new LogEntry( LogLevelType::Critical, message, frame, stack ) );
        }

        void Logger::LogCritical( String* format, [ParamArray] Object* args[] )
        {
			LogCritical(String::Format(format, args));
        }

        void Logger::Log( LogEntry* entry )
        {
            if( entry->EntryType < mLogLevel || mOutputs->Count < 1 )
            {
                // dispose here?
                return;
            }

            if( mAsynchronous )
            {
                Monitor::Enter( mEntryQueue );
                mEntryQueue->Enqueue( entry );
                Monitor::Exit( mEntryQueue );

                // signal that entries are pending dispatch
                mDispatchEvent->Set();
            }
            else
            {
                Monitor::Enter( this );
                Dispatch( entry );
                Monitor::Exit( this );
            }
        }

        void Logger::Log( int type, Object* message )
        {
            Log( new LogEntry( type, message, 0, 0 ) );
        }

        void Logger::Log( int type, Object* message, StackFrame* frame, StackTrace* stack )
        {
            Log( new LogEntry( type, message, frame, stack ) );
        }

        void Logger::Clear()
        {
            // need to process the queue if asynchronous
            // maybe create a new queue and get ref to old queue to keep
            // asynch operations occurring.

            IEnumerator* enumerator = mOutputs->GetEnumerator();
            while( enumerator->MoveNext() )
            {
                IOutput* output = static_cast<IOutput*>(enumerator->Current);
                output->Clear();
            }
        }

        void Logger::Flush()
        {
            // need to process the queue if asynchronous
            // maybe create a new queue and get ref to old queue to keep
            // asynch operations occurring.

            IEnumerator* enumerator = mOutputs->GetEnumerator();
            while( enumerator->MoveNext() )
            {
                IOutput* output = static_cast<IOutput*>(enumerator->Current);
                output->Flush();
            }
        }

        void Logger::Dispatch( LogEntry* entry )
        {
            IEnumerator* enumerator = mOutputs->GetEnumerator();
            while( enumerator->MoveNext() )
            {
                // get this output instance
                IOutput* output = static_cast<IOutput*>(enumerator->Current);

                // check if the output wants this entry
                if( entry->EntryType < output->LogLevel )
                    return;

                // log the entry
                output->Log( entry );
            }
        }

        void Logger::EntryDispatchThread()
        {
            LogEntry* entry;

            while( mAsynchronous )  // should I exit if enabled is set to false?
            {
                // wait for an entry to be logged
                mDispatchEvent->WaitOne();

                // check if queue is empty
                if( mEntryQueue->Count < 1 )
                {
                    mDispatchEvent->Reset();
                    continue;
                }
                else
                {
                    // get next entry to dispatch
                    Monitor::Enter( mEntryQueue );
                    entry = static_cast<LogEntry*>(mEntryQueue->Dequeue());
                    Monitor::Exit( mEntryQueue );

                    // dispatch the entry
                    Dispatch( entry );

                    // dispose of entry
                    entry->Dispose();
                }
            }
        }
    }
}
