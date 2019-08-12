#ifndef XMLFILEOUTPUT_H
#define XMLFILEOUTPUT_H

#include "botNET.h"

#include "IOutput.h"
#include "FileLogger.h"

using namespace System;
using namespace System::Xml;

namespace botNET
{
    namespace Diagnostics
    {
        // forward declaractions
        public __gc class LogEntry;

        public __gc class XmlLogger : public FileLogger
        {
        public:
            XmlLogger( String* filename );
            XmlLogger( String* filename, String* stylesheet );
            XmlLogger( String* filename, String* stylesheet, bool append );

            virtual void Flush();
            virtual void DoLog( LogEntry* entry );

            void Clear();
            void Load( String* filename );
            void Save( String* filename );

        protected:
            virtual void Dispose( bool disposing );
            XmlElement* GenerateXml( LogEntry* entry );

        private:
            void Init( String* filename, String* stylesheet, bool append );

        protected:
            XmlDocument* mDocument;
        };
    }
}

#endif
