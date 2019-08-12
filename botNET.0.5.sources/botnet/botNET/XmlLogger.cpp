#include "LogEntry.h"
#include "XmlLogger.h"

using namespace System;
using namespace System::IO;

namespace botNET
{
    namespace Diagnostics
    {
        XmlLogger::XmlLogger( String* filename )
            : FileLogger( filename )
        {
            Init( filename, 0, false );
        }

        XmlLogger::XmlLogger( String* filename, String* stylesheet )
            : FileLogger( filename )
        {
            Init( filename, stylesheet, false );
        }

        XmlLogger::XmlLogger( String* filename, String* stylesheet, bool append )
            : FileLogger( filename, append )
        {
            Init( filename, stylesheet, append );
        }

        void XmlLogger::Init( String* filename, String* stylesheet, bool append )
        {
            if( append )
                Load( mOutputFile );
            else
                mDocument = new XmlDocument();

            // need to check stylesheet here processing instruction
            if( stylesheet )
            {
                //
                IEnumerator* enumerator = mDocument->ChildNodes->GetEnumerator();
                for( int i = 0; enumerator->MoveNext(); )
                {
                    XmlNode* node = static_cast<XmlNode*>(enumerator->Current);
                    if( node->NodeType != XmlNodeType::ProcessingInstruction )
                        continue;

                    XmlProcessingInstruction* temp = static_cast<XmlProcessingInstruction*>(node);
                    if( temp->Name == "xml-stylesheet" )
                    {
                        node->RemoveChild( node );
                    }
                }

                // create stylesheet element
                String* data[] = { S"type=\"text/xsl\" href=\"", stylesheet, S"\"" };
                XmlProcessingInstruction* instruction =
                    mDocument->CreateProcessingInstruction( "xml-stylesheet", String::Concat( data ) );

                // add the child
                mDocument->PrependChild( instruction );
            }

            // check if the document root is there
            if( mDocument->DocumentElement == 0 )
            {
                mDocument->AppendChild( mDocument->CreateElement( "Log" ) );
            }
            else
            {
                // verify that the document root is a "Log" tag
            }
        }

        void XmlLogger::Dispose( bool disposing )
        {
            if( disposing )
            {
                __super::Dispose( disposing );
            }
        }

        void XmlLogger::DoLog( LogEntry* entry )
        {
            XmlElement* element = GenerateXml( entry );
            mDocument->DocumentElement->AppendChild( element );
        }

        void XmlLogger::Clear()
        {
            mDocument->DocumentElement->InnerText = "";
        }

        void XmlLogger::Flush()
        {
            Save( mOutputFile );
        }

        void XmlLogger::Load( String* filename )
        {
            mDocument = new XmlDocument();

            // load a previous log file if available
            if( File::Exists( mOutputFile ) )
            {
                try
                {
                    XmlTextReader* reader = new XmlTextReader( mOutputFile );
                    mDocument->Load( reader );
                    reader->Close();
                }
                catch( Exception*)
                {
                }
            }
            else
            {
                // error
            }
        }

        void XmlLogger::Save( String* filename )
        {
            try
            {
                XmlTextWriter* writer = new XmlTextWriter( filename, 0 );
                mDocument->Save( writer );
                writer->Close();
            }
            catch( Exception*)
            {
            }
        }

        XmlElement* XmlLogger::GenerateXml( LogEntry* entry )
        {
            // create root element
            XmlElement* root = mDocument->CreateElement( "LogEntry" );
            root->SetAttribute( S"type", entry->EntryType.ToString() );

            // create and initialize the date element
            XmlElement* date = mDocument->CreateElement( "Date" );
            date->InnerText = entry->Date.ToString( "d" );
            root->AppendChild( date );

            // create and initialize the time element
            XmlElement* time = mDocument->CreateElement( "Time" );
            time->InnerText = entry->Time.ToString();
            root->AppendChild( time );

            // create and initialize the message element
            XmlElement* message = mDocument->CreateElement( "Message" );
            message->InnerText = entry->Message->ToString();
            root->AppendChild( message );

            if( entry->FileName != 0 )
            {
                // create the FileName element
                XmlElement* filename = mDocument->CreateElement( "FileName" );
                filename->InnerText = entry->FileName;
                root->AppendChild( filename );
            }

            if( entry->Method != 0 )
            {
                // create the Method element
                XmlElement* method = mDocument->CreateElement( "Method" );
                method->InnerText = entry->Method->ToString();
                root->AppendChild( method );
            }

            if( entry->Stack != 0 )
            {
                StackTrace* stackTrace = entry->Stack;

                // create the stack element
                XmlElement* stack = mDocument->CreateElement( "Stack" );

                // enumerate the StackTrace
                for( int i = 0; i < stackTrace->FrameCount; i++ )
                {
                    // create a Method element
                    XmlElement* method1 = mDocument->CreateElement( "Method" );
                    method1->InnerText = stackTrace->GetFrame( i )->GetMethod()->ToString();
                    stack->AppendChild( method1 );
                }

                // add stack element
                root->AppendChild( stack );
            }

            return root;
        }
    }
}
