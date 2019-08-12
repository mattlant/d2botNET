#include "ProfileCollection.h"

namespace botNET
{
	namespace Configuration
	{
		ProfileCollection::ProfileCollection( Config* config )
		{
			// verify it isn't null, maybe ArgumentException if it is
			mConfig = config;
		}

		int ProfileCollection::Add( Profile* profile )
		{
			return this->List->Add( mConfig->mDocument->ImportNode( profile->mNode, true ) );
		}

		int ProfileCollection::Add( XmlNode* node )
		{
			return this->List->Add( new Profile( mConfig, node ) );
		}

		void ProfileCollection::Remove( Profile* profile )
		{
			this->List->Remove( profile );
		}

		int ProfileCollection::Contains( Profile* profile )
		{
			return this->List->Contains( profile );
		}

		int ProfileCollection::IndexOf( Profile* profile )
		{
			return this->List->IndexOf( profile );
		}

		void ProfileCollection::Reverse()
		{
			this->InnerList->Reverse();
		}

		void ProfileCollection::Reverse(int index, int count)
		{
			this->InnerList->Reverse();
		}

		void ProfileCollection::Sort()
		{
			this->InnerList->Sort();
		}

		void ProfileCollection::Sort(IComparer* comparer)
		{
			this->InnerList->Sort(comparer);
		}

		void ProfileCollection::Sort(int index, int count, IComparer* comparer)
		{
			this->InnerList->Sort(index, count, comparer);
		}

		bool ProfileCollection::get_IsSynchronized()
		{
			return this->InnerList->IsSynchronized;
		}

		System::Object* ProfileCollection::get_SyncRoot()
		{
			return this->InnerList->SyncRoot;
		}
	}
}