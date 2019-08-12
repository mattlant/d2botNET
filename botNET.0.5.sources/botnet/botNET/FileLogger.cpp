#include "FileLogger.h"

using namespace System;
using namespace System::IO;

namespace botNET
{
    namespace Diagnostics
    {
        FileLogger::FileLogger( String* filename )
            : mOutputFile( filename )
        {
        }

        FileLogger::FileLogger( String* filename, bool append )
            : mOutputFile( filename )
        {
            if( append )
                Load( filename );
        }

        void FileLogger::Dispose( bool disposing )
        {
            if( disposing )
            {
                if( mAutoSave )
                {
                    Save( mOutputFile );
                }

                __super::Dispose( disposing );
            }
        }

        bool FileLogger::get_AutoSave()
        {
            return mAutoSave;
        }


        void FileLogger::set_AutoSave( bool autosave )
        {
            mAutoSave = autosave;
        }

        String* FileLogger::get_OutputFile()
        {
           return mOutputFile;
        }


        void FileLogger::set_OutputFile( String* filename )
        {
           mOutputFile = filename;
        }

        void FileLogger::Log( LogEntry* entry )
        {
            DoLog( entry );

            if( mAutoFlush )
                Flush();
        }
    }
}