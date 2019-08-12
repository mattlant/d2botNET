#ifndef CHATLINEHANDLERPATCH_H
#define CHATLINEHANDLERPATCH_H

namespace botNET
{
namespace Imports
{
namespace Patches
{

void ChatBoxHandlerSTUB();
void __stdcall ChatLineHandler(char * msg);
void ChatLineHandlerSTUB(char * msg);

}
}
}

#endif