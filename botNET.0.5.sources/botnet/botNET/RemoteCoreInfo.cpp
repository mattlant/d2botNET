
using namespace System::Diagnostics;
using namespace System::Runtime::Remoting;
using namespace System::Runtime::Remoting::Channels;
using namespace System::Runtime::Remoting::Channels::Tcp;

#include "botnet.h"
#include "remotecoreinfo.h"
#include "AssemblyLoader.h"
#include "RemoteAssemblyLoader.h"
#include "remotinguri.h"
#include "settings.h"

namespace botNET
{
	namespace Remoting
	{

		Int32 RemoteCoreInfo::get_D2Handle()
		{
			return Process::GetCurrentProcess()->Handle.ToInt32();
		}

		Int32 RemoteCoreInfo::get_Port()
		{
			return Settings::Remoting::gUsedRemotingPort;
		}


		
		
		
		void RemoteCoreInfo::Initialize()
		{
			System::Windows::Forms::MessageBox::Show("Remoting");
			TcpRemotingURI* uri = new TcpRemotingURI(S"localhost", S"RemoteCoreInfo", Settings::Remoting::gBaseRemotingPort);

			// go thru ports, attach to botnets
			// get first port that has no botnet, and use that
			while(uri->Port < UInt16::MaxValue)
			{
				TcpClientChannel* tempchan;
				try{
						
					tempchan = new TcpClientChannel();
					ChannelServices::RegisterChannel(tempchan);
					RemoteCoreInfo* tempobj = __try_cast<RemoteCoreInfo*>(System::Activator::GetObject(__typeof(RemoteCoreInfo), uri->ToString()));
					ChannelServices::UnregisterChannel(tempchan);
				}
				catch(Exception*)
				{
					ChannelServices::UnregisterChannel(tempchan);
					Settings::Remoting::gUsedRemotingPort = uri->Port;
					break;
				}
				uri->Port++;
			}

			if(uri->Port == UInt16::MaxValue)
			{
				throw new ApplicationException("Could not find a suitable port for remoting");
			}

			TcpServerChannel* channel = new TcpServerChannel(Settings::Remoting::gUsedRemotingPort);
			ChannelServices::RegisterChannel(channel);
			RemotingConfiguration::RegisterWellKnownServiceType(__typeof(RemoteCoreInfo), "RemoteCoreInfo", WellKnownObjectMode::Singleton);
			RemotingConfiguration::RegisterWellKnownServiceType(__typeof(RemoteAssemblyLoader), "RemoteAssemblyLoader", WellKnownObjectMode::Singleton);
		}



	}
}
