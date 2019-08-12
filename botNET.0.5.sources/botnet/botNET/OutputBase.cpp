#include "OutputBase.h"

namespace botNET
{
    namespace Diagnostics
    {
        OutputBase::OutputBase()
        {
        }

        OutputBase::~OutputBase()
        {
              Dispose( false );
        }

        bool OutputBase::get_AutoFlush()
        {
            return mAutoFlush;
        }

        void OutputBase::set_AutoFlush( bool autoflush )
        {
            mAutoFlush = autoflush;
        }

        bool OutputBase::get_Disposed()
        {
            return mDisposed;
        }

        LogLevelType OutputBase::get_LogLevel()
        {
            return mLogLevel;
        }

        void OutputBase::set_LogLevel( LogLevelType severity )
        {
            mLogLevel = severity;
        }

        void OutputBase::Dispose()
        {
            Dispose( true );
            GC::SuppressFinalize( this );
        }

        void OutputBase::Dispose( bool disposing )
        {
            if( disposing )
            {
                mDisposed = true;
            }
        }
    }
}
