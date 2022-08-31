#include "OpenIGTLinkCommon.h"

#include "igtlOSUtil.h"
#include "igtlTransformMessage.h"
#include "igtlPointMessage.h"
#include "igtlStringMessage.h"
#include "igtlServerSocket.h"

igtl::Socket::Pointer OpenIGTLinkCommon::socket = nullptr;

OpenIGTLinkCommon::OpenIGTLinkCommon()
{
}

OpenIGTLinkCommon::~OpenIGTLinkCommon()
{
    if (OpenIGTLinkCommon::socket.IsNotNull())
        OpenIGTLinkCommon::socket->CloseSocket();
}

int OpenIGTLinkCommon::startIGTLinkConnection(int port)
{
    igtl::ServerSocket::Pointer serverSocket = igtl::ServerSocket::New();
    int r = serverSocket->CreateServer(port);

    if (r < 0)
    {
        std::cout << "Cannot create a server socket." << std::endl;
    }
    else
    {
        OpenIGTLinkCommon::socket = serverSocket->WaitForConnection(1000);
        if (OpenIGTLinkCommon::socket.IsNotNull())
        {
            std::cout << "Client connected." << std::endl;
        }
        else
        {
            std::cout << "Client not connected." << std::endl;
        }
    }
    return 1;
}

int OpenIGTLinkCommon::isConnected()
{
    return OpenIGTLinkCommon::socket.IsNotNull();
}

void OpenIGTLinkCommon::test()
{
    std::cout << "test" << std::endl;
}
