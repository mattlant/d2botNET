#ifndef REMOTINGURI_H
#define REMOTINGURI_H




namespace botNET
{
	namespace Remoting
	{

		public __gc class TcpRemotingURI
		{
		public:
			TcpRemotingURI(String* host, String* classpath, UInt16 port);

			__property String* get_Host();
			__property void set_Host(String* value);

			__property String* get_ClassPath();
			__property void set_ClassPath(String* value);

			__property UInt16 get_Port();
			__property void set_Port(UInt16 value);

			String* ToString();

		private:
			String* mHost;
			String* mClassPath;
			UInt16 mPort;

		};

	}

}

#endif