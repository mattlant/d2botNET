#ifndef OUTPUTCOLLECTION_H
#define OUTPUTCOLLECTION_H

#include "IOutput.h"

using namespace System;
using namespace System::Collections;

namespace botNET
{
    namespace Diagnostics
    {
        public __gc class OutputCollection : public CollectionBase
        {
        public:
            int Add( IOutput* output );
            int IndexOf( IOutput* output );
            void Insert( int index, IOutput* output );
            void Remove( IOutput* output );
            bool Contains( IOutput* output );

        protected:
        };
    }
}

#endif