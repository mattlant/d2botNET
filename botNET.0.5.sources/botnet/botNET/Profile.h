#ifndef IPROFILE_H
#define IPROFILE_H

namespace botNET
{
	namespace Configuration
	{
		// forward declarations
		__gc public class Config;

		__gc public class Profile
		{
		public private:
			Config* mConfig;
			System::Xml::XmlNode* mNode;

		public:
			__property String* get_Name();
			__property System::Xml::XmlNode* get_XmlNode();

			bool GetAttribute( String* path, String* name, bool value );
			void SetAttribute( String* path, String* name, bool value );
			int GetAttribute( String* path, String* name, int value );
			void SetAttribute( String* path, String* name, int value );
			String* GetAttribute( String* path, String* name, String* value );
			void SetAttribute( String* path, String* name, String* value );

			bool GetValue( String* path, bool value );
			void SetValue( String* path, bool value );
			int GetValue( String* path, int value );
			void SetValue( String* path, int value );
			String* GetValue( String* path, String* value );
			void SetValue( String* path, String* value );

		public private:
			Profile( Config* config, XmlNode* node );

			System::Xml::XmlNode* CreateEntry( String* path );
		};
	}
}

#endif