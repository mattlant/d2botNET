#ifndef PROFILECOLLECTION_H
#define PROFILECOLLECTION_H

#include "botNET.h"
#include "Configuration.h"
#include "Profile.h"

namespace botNET
{
	namespace Configuration
	{
		public __gc class ProfileCollection : public System::Collections::CollectionBase
		{
		private:
			Config* mConfig;

		public:
			int Add( Profile* profile );
			int Add( XmlNode* profile );
			void Remove( Profile* profile );
			int Contains( Profile* profile );
			int IndexOf( Profile* profile );

			// TODO: Should this be sortable?
			void Reverse();
			void Reverse(int index, int count);

			void Sort();
			void Sort(IComparer* comparer);
			void Sort(int index, int count, IComparer* comparer);

			__property bool get_IsSynchronized();
			__property Object* get_SyncRoot();

		public private:
			ProfileCollection( Config* config );
		};
	}
}

#endif