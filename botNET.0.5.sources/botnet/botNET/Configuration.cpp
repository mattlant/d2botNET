#include "botNET.h"
#include "Game.h"
#include "settings.h"
#include "Configuration.h"
#include "Profile.h"
#include "ProfileCollection.h"

namespace botNET
{
	namespace Configuration
	{
		Config::Config()
		{
			mProfiles = new ProfileCollection( this );

			mDocument = new XmlDocument();
			mDocument->AppendChild( mDocument->CreateElement( "Configuration" ) );
		}

		Config::Config( String* filename )
		{
			mProfiles = new ProfileCollection( this );

			Load( filename );
		}

		void Config::Load( String* filename )
		{
			AbsoluteLoad( String::Format( S"{0}\\{1}", Settings::Directories::gSettings , filename ) );
		}

		void Config::AbsoluteLoad( String* filename )
		{
            // load configuration file
            if( !File::Exists( filename ) )
            {
				throw new FileNotFoundException( "Configuration file not found." );
            }

            mDocument = new XmlDocument();

			try
            {
                XmlTextReader* reader = new XmlTextReader( filename );
                mDocument->Load( reader );
                reader->Close();

				XmlNodeList* profiles = mDocument->DocumentElement->SelectNodes( S"Profile" );
				IEnumerator* enumerator = profiles->GetEnumerator();
				while( enumerator->MoveNext() )
				{
					System::Xml::XmlNode* profile = dynamic_cast<System::Xml::XmlNode*>( enumerator->Current );
					mDocument->DocumentElement->RemoveChild( profile );

					mProfiles->Add( profile );
				}
            }
            catch( Exception* exception )
            {
				Game::Print( exception );
            }
		}

        void Config::Save( String* filename )
        {
			AbsoluteSave( String::Format( S"{0}\\{1}", Settings::Directories::gSettings , filename ) );
		}

		void Config::AbsoluteSave( String* filename )
        {
            try
            {
				IEnumerator* enumerator = mProfiles->GetEnumerator();
				while( enumerator->MoveNext() )
				{
					Profile* profile = dynamic_cast<Profile*>( enumerator->Current );
					mDocument->DocumentElement->AppendChild( profile->mNode );
				}

				XmlTextWriter* writer = new XmlTextWriter( filename, 0 );
                mDocument->Save( writer );
                writer->Close();
            }
            catch( Exception*)
            {
            }
        }

		System::Xml::XmlNode* Config::get_XmlNode()
		{
			return mDocument->DocumentElement;
		}

		System::Xml::XmlNode* Config::CreateEntry( String* path )
		{
			// verify we have a valid formed input path
			if( path->StartsWith( "/" ) || path->EndsWith( "/" ) )
			{
				throw new ArgumentException( S"Path must contain '/' followed by a name" );
			}

			// check if the parent exists
			System::Xml::XmlNode* node = NULL;
			if( path->LastIndexOf( '/' ) == -1 )
			{
				node = mDocument->DocumentElement;
			}
			else
			{
				String* parent = path->Substring( 0, path->LastIndexOf( '/' ) );
				node = mDocument->DocumentElement->SelectSingleNode( parent );
				if( !node )
				{
					node = CreateEntry( parent );
				}
			}

			// create and append the new child node
			String* name = path->Substring( path->LastIndexOf( '/' )+1 );
			node->AppendChild( mDocument->CreateElement( name ) );

			return mDocument->DocumentElement->SelectSingleNode( path );
		}

		ProfileCollection* Config::get_Profiles()
		{
			return mProfiles;
		}

		Profile* Config::GetProfile( String* name )
		{
			IEnumerator* enumerator = mProfiles->GetEnumerator();
			while( enumerator->MoveNext() )
			{
				Profile* profile = dynamic_cast<Profile*>( enumerator->Current );
				if( String::Compare( profile->Name, name ) == 0 )
					return profile;
			}

			return NULL;
		}

		Profile* Config::CreateProfile( String* name )
		{
			XmlElement* element = mDocument->CreateElement( S"Profile" );
			element->SetAttribute( S"name", name );
			Profile* profile = new Profile( this, element );
			mProfiles->Add( profile );

			return profile;
		}

		bool Config::GetAttribute( String* path, String* name, bool value )
		{
			return Boolean::Parse( GetAttribute( path, name, __box( value )->ToString() ) );
		}

		void Config::SetAttribute( String* path, String* name, bool value )
		{
			SetAttribute( path, name, __box( value )->ToString() );
		}

		int Config::GetAttribute( String* path, String* name, int value )
		{
			return Int32::Parse( GetAttribute( path, name, __box( value )->ToString() ) );
		}

		void Config::SetAttribute( String* path, String* name, int value )
		{
			SetAttribute( path, name, __box( value )->ToString() );
		}

		String* Config::GetAttribute( String* path, String* name, String* value )
		{
			// verify we have a valid formed input path
			if( path->StartsWith( "/" ) || path->EndsWith( "/" ) )
			{
				throw new ArgumentException( S"Path must not start or end with a '/'" );
			}

			String* newpath = String::Format( "{0}/@{1}", path, name );
			System::Xml::XmlNode* node = mDocument->DocumentElement->SelectSingleNode( newpath );
            if( !node )
			{
                return value;
			}

			return node->Value;
		}

		void Config::SetAttribute( String* path, String* name, String* value )
		{
			// verify we have a valid formed input path
			if( path->StartsWith( "/" ) || path->EndsWith( "/" ) )
			{
				throw new ArgumentException( S"Path must not start or end with a '/'" );
			}

			String* newpath = String::Format( "{0}/@{1}", path, name );
			System::Xml::XmlNode* node = mDocument->DocumentElement->SelectSingleNode( newpath );
            if( !node )
			{
				throw new InvalidOperationException( S"Node not found, can't set attribute on imaginary node" );
			}

			node->Value = value;
		}

		bool Config::GetValue( String* path, bool value )
		{
			return Boolean::Parse( GetValue( path, __box( value )->ToString() ) );
		}

		void Config::SetValue( String* path, bool value )
		{
			SetValue( path, __box( value )->ToString() );
		}

		int Config::GetValue( String* path, int value )
		{
			return Int32::Parse( GetValue( path, __box( value )->ToString() ) );
		}

		void Config::SetValue( String* path, int value )
		{
			SetValue( path, __box( value )->ToString() );
		}

		String* Config::GetValue( String* path, String* value )
		{
			// verify we have a valid formed input path
			if( path->StartsWith( "/" ) || path->EndsWith( "/" ) )
			{
				throw new ArgumentException( S"Path must not start or end with a '/'" );
			}

			System::Xml::XmlNode* node = mDocument->DocumentElement->SelectSingleNode( path );
			if( !node || !node->HasChildNodes )
                return value;

			// check for children
			if( node->ChildNodes->Count > 1 || node->FirstChild->NodeType != XmlNodeType::Text )
				throw new InvalidOperationException( S"Node has children can't Get/SetValue on non-leaf nodes" );

			return node->InnerText;
		}

		void Config::SetValue( String* path, String* value )
		{
			// verify we have a valid formed input path
			if( path->StartsWith( "/" ) || path->EndsWith( "/" ) )
			{
				throw new ArgumentException( S"Path must not start or end with a '/'" );
			}

			System::Xml::XmlNode* node = mDocument->DocumentElement->SelectSingleNode( path );
			if( !node )
				node = CreateEntry( path ); 

			// check for children
			if( node->HasChildNodes && ( node->ChildNodes->Count > 1 || node->FirstChild->NodeType != XmlNodeType::Text ) )
				throw new InvalidOperationException( S"Node has children can't Get/SetValue on non-leaf nodes" );

			// set value
			node->InnerText = value;
		}
	};
};
