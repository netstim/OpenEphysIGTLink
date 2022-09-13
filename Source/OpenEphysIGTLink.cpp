#include "OpenEphysIGTLink.h"

#include "igtlOSUtil.h"
#include "igtlTransformMessage.h"
#include "igtlPointMessage.h"
#include "igtlStringMessage.h"
#include "igtlServerSocket.h"

igtl::Socket::Pointer OpenIGTLinkLogic::socket = nullptr;
int OpenIGTLinkLogic::currentPort = 18944;

OpenIGTLinkLogic::OpenIGTLinkLogic()
{
}

OpenIGTLinkLogic::~OpenIGTLinkLogic()
{
    closeConnection();
}

bool OpenIGTLinkLogic::startIGTLinkConnection(int port)
{
    igtl::ServerSocket::Pointer serverSocket = igtl::ServerSocket::New();
    int r = serverSocket->CreateServer(port);

    if (r >= 0)
    {
        OpenIGTLinkLogic::socket = serverSocket->WaitForConnection(1000);
    }

    return isConnected();
}

bool OpenIGTLinkLogic::isConnected()
{
    return (OpenIGTLinkLogic::socket != nullptr);
}

void OpenIGTLinkLogic::closeConnection()
{
    if (isConnected())
        OpenIGTLinkLogic::socket->CloseSocket();
    OpenIGTLinkLogic::socket = nullptr;
}

void OpenIGTLinkLogic::sendStringMessage(String deviceName, String sendString)
{
    igtl::StringMessage::Pointer strMsg = igtl::StringMessage::New();
    strMsg->SetDeviceName(deviceName.toStdString());
    strMsg->SetString(sendString.toStdString());
    strMsg->Pack();
    std::cout << sendString.toStdString() << std::endl;
    if (isConnected())
    {
        std::cout << "sending" << std::endl;
        OpenIGTLinkLogic::socket->Send(strMsg->GetPackPointer(), strMsg->GetPackSize());
    }
}
void OpenIGTLinkLogic::sendPointMessage(String deviceName, Array<float> values)
{
    igtl::PointMessage::Pointer pointMsg = igtl::PointMessage::New();
    pointMsg->SetDeviceName(deviceName.toStdString());
    for (int i = 0; i < values.size();)
    {
        igtl::PointElement::Pointer point = igtl::PointElement::New();
        point->SetPosition(values[i++], values[i++], values[i++]);
        point->SetName(std::to_string(i / 3).c_str());
        point->SetGroupName("GROUP_0");
        point->SetRGBA(0x00, 0x00, 0xFF, 0xFF);
        point->SetRadius(75.0);
        point->SetOwner("IMAGE_0");
        pointMsg->AddPointElement(point);
    }
    pointMsg->Pack();
    if (isConnected())
        OpenIGTLinkLogic::socket->Send(pointMsg->GetPackPointer(), pointMsg->GetPackSize());
}

void OpenIGTLinkLogic::sendTransformMessage(String deviceName, Array<float> values)
{
    igtl::TransformMessage::Pointer transMsg = igtl::TransformMessage::New();
    transMsg->SetDeviceName(deviceName.toStdString());

    igtl::Matrix4x4 matrix;
    int arrayIdx = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j] = values[arrayIdx++];
        }
    }

    transMsg->SetMatrix(matrix);
    transMsg->Pack();

    if (isConnected())
        OpenIGTLinkLogic::socket->Send(transMsg->GetPackPointer(), transMsg->GetPackSize());
}