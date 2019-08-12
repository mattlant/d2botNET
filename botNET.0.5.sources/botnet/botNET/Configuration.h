#ifndef ICONFIGURATION_H
#define ICONFIGURATION_H

namespace botNET
{
	namespace Configuration
	{
		// forward declarations
		__gc public class Profile;
		__gc public class ProfileCollection;

		__gc public class Config
		{
		public private:
			XmlDocument* mDocument;

		private:
			ProfileCollection* mProfiles;

		public:
			Config();
			Config( String* filename );

			__property ProfileCollection* get_Profiles();
			__property System::Xml::XmlNode* get_XmlNode();

			void Load( String* filename );
			void Save( String* filename );

			Profile* GetProfile( String* name );
			Profile* CreateProfile( String* name );

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
			System::Xml::XmlNode* CreateEntry( String* path );

			void AbsoluteLoad( String* filename );
			void AbsoluteSave( String* filename );

			static Config* gGlobalConfig;

		};
	}
}

#endif