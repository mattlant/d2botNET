#include "botNET.h"
#include "Profile.h"

namespace botNET
{
	namespace Configuration
	{
		Profile::Profile( Config* config, System::Xml::XmlNode* node )
		{
			mConfig = config;
			mNode   = node;

			// TODO: Verify that this profile has a name
		}

		String* Profile::get_Name()
		{
			// ? check if has attributes?
			return dynamic_cast<XmlAttribute*>( mNode->Attributes->GetNamedItem( S"name" ) )->Value;
		}

		System::Xml::XmlNode* Profile::get_XmlNode()
		{
			return mNode;
		}

		System::Xml::XmlNode* Profile::CreateEntry( String* path )
		{
			// verify we have a valid formed input path
			if( path->StartsWith( "/" ) || path->EndsWith( "/" ) )
				throw new ArgumentException( S"Path must not start or end with a '/'" );

			// check if the parent exists
			System::Xml::XmlNode* node = NULL;
			if( path->LastIndexOf( '/' ) == -1 )
			{
				node = mNode;
			}
			else
			{
				String* parent = path->Substring( 0, path->LastIndexOf( '/' ) );
				node = mNode->SelectSingleNode( parent );
				if( !node )
				{
					node = CreateEntry( parent );
				}
			}

			// create and append the new child node
			String* name = path->Substring( path->LastIndexOf( '/' )+1 );
			node->AppendChild( mNode->OwnerDocument->CreateElement( name ) );

			return mNode->SelectSingleNode( path );
		}

		bool Profile::GetAttribute( String* path, String* name, bool value )
		{
			return Boolean::Parse( GetAttribute( path, name, __box( value )->ToString() ) );
		}

		void Profile::SetAttribute( String* path, String* name, bool value )
		{
			SetAttribute( path, name, __box( value )->ToString() );
		}

		int Profile::GetAttribute( String* path, String* name, int value )
		{
			return Int32::Parse( GetAttribute( path, name, __box( value )->ToString() ) );
		}

		void Profile::SetAttribute( String* path, String* name, int value )
		{
			SetAttribute( path, name, __box( value )->ToString() );
		}

		String* Profile::GetAttribute( String* path, String* name, String* value )
		{
			// verify we have a valid formed input path
			if( path->StartsWith( "/" ) || path->EndsWith( "/" ) )
			{
				throw new ArgumentException( S"Path must not start or end with a '/'" );
			}

			String* newpath = String::Format( "{0}/@{1}", path, name );
			System::Xml::XmlNode* node = mNode->SelectSingleNode( newpath );
            if( !node )
			{
				// check if it is under the document root element
				node = mNode->OwnerDocument->DocumentElement->SelectSingleNode( newpath );
				if( !node )
	                return value;
			}

			return node->Value;
		}

		void Profile::SetAttribute( String* path, String* name, String* value )
		{
			// verify we have a valid formed input path
			if( path->StartsWith( "/" ) || path->EndsWith( "/" ) )
			{
				throw new ArgumentException( S"Path must not start or end with a '/'" );
			}

			String* newpath = String::Format( "{0}/@{1}", path, name );
			System::Xml::XmlNode* node = mNode->SelectSingleNode( newpath );
            if( !node )
			{
				throw new InvalidOperationException( S"Node not found in profile, can't set attribute on imaginary node" );
			}

			node->Value = value;
		}

		bool Profile::GetValue( String* path, bool value )
		{
			return Boolean::Parse( GetValue( path, __box( value )->ToString() ) );
		}

		void Profile::SetValue( String* path, bool value )
		{
			SetValue( path, __box( value )->ToString() );
		}

		int Profile::GetValue( String* path, int value )
		{
			return Int32::Parse( GetValue( path, __box( value )->ToString() ) );
		}

		void Profile::SetValue( String* path, int value )
		{
			SetValue( path, __box( value )->ToString() );
		}

		String* Profile::GetValue( String* path, String* value )
		{
			// verify we have a valid formed input path
			if( path->StartsWith( "/" ) || path->EndsWith( "/" ) )
			{
				throw new ArgumentException( S"Path must not start or end with a '/'" );
			}

			System::Xml::XmlNode* node = mNode->SelectSingleNode( path );
            if( !node )
			{
				// check if it is under the document root element
				node = mNode->OwnerDocument->DocumentElement->SelectSingleNode( path );
				if( !node )
	                return value;
			}
			if( !node->HasChildNodes )
			{
				return value;
			}

			// check if node has children
			if( node->ChildNodes->Count > 1 || node->FirstChild->NodeType != XmlNodeType::Text )
				throw new InvalidOperationException( S"Node has children can't Get/SetValue on non-leaf nodes" );

			return node->InnerText;
		}

		void Profile::SetValue( String* path, String* value )
		{
			// verify we have a valid formed input path
			if( path->StartsWith( "/" ) || path->EndsWith( "/" ) )
			{
				throw new ArgumentException( S"Path must not start or end with a '/'" );
			}

			System::Xml::XmlNode* node = mNode->SelectSingleNode( path );
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
