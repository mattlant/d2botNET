#include "OutputCollection.h"

namespace botNET
{
    namespace Diagnostics
    {
        int OutputCollection::Add( IOutput* output )
        {
            return List->Add( output );
        }

        int OutputCollection::IndexOf( IOutput* output )
        {
            return List->IndexOf( output );
        }

        void OutputCollection::Insert( int index, IOutput* output )
        {
            List->Insert( index, output );
        }

        void OutputCollection::Remove( IOutput* output )
        {
            List->Remove( output );
        }

        bool OutputCollection::Contains( IOutput* output )
        {
            return List->Contains( output );
        }
    }
}