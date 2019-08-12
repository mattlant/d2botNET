#include "botnet.h"
#include ".\remotinguri.h"

namespace botNET
{
	namespace Remoting
	{

		TcpRemotingURI::TcpRemotingURI(String* host, String* classpath, UInt16 port)
		{
			this->mHost = host;
			this->mClassPath = classpath;
			this->mPort = port;


		}

		String* TcpRemotingURI::ToString()
		{
			return String::Format(S"tcp://{0}:{1}/{2}", mHost, mClassPath, mPort.ToString());
		}

		String* TcpRemotingURI::get_Host()
		{
			return this->mHost;
		}

		void TcpRemotingURI::set_Host(String* value)
		{
			this->mHost = value;
		}

		String* TcpRemotingURI::get_ClassPath()
		{
			return this->mClassPath;
		}

		void TcpRemotingURI::set_ClassPath(String* value)
		{
			this->mClassPath = value;
		}

		UInt16 TcpRemotingURI::get_Port()
		{
			return this->mPort;
		}

		void TcpRemotingURI::set_Port(UInt16 value)
		{
			this->mPort = value;
		}

	}

}
