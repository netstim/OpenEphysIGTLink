/*
------------------------------------------------------------------

This file is part of the Open Ephys GUI
Copyright (C) 2022 Open Ephys

------------------------------------------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "OpenIGTLinkPlugin.h"

#include "OpenIGTLinkPluginEditor.h"


#include "igtlOSUtil.h"
#include "igtlTransformMessage.h"
#include "igtlServerSocket.h"

OpenIGTLinkPlugin::OpenIGTLinkPlugin()
    : GenericProcessor("OpenIGTLink")
{

    transMsg = igtl::TransformMessage::New();
    transMsg->SetDeviceName("Tracker");

    serverSocket = igtl::ServerSocket::New();
    int r = serverSocket->CreateServer(18944);

    if (r < 0)
    {
        std::cout << "Cannot create a server socket." << std::endl;
    }
    else
    {
        socket = serverSocket->WaitForConnection(1000);
        if (socket.IsNotNull())
        {
            std::cout << "Client connected." << std::endl;
        }
        else
        {
            std::cout << "Client not connected." << std::endl;
        }
    }

}


OpenIGTLinkPlugin::~OpenIGTLinkPlugin()
{
    if (socket.IsNotNull())
        socket->CloseSocket();
}


AudioProcessorEditor* OpenIGTLinkPlugin::createEditor()
{
    editor = std::make_unique<OpenIGTLinkPluginEditor>(this);
    return editor.get();
}


void OpenIGTLinkPlugin::updateSettings()
{


}


void OpenIGTLinkPlugin::process(AudioBuffer<float>& buffer)
{

    checkForEvents(true); 
}


void OpenIGTLinkPlugin::handleTTLEvent(TTLEventPtr event)
{
    igtl::Matrix4x4 matrix;
    transMsg->SetMatrix(matrix);
    transMsg->Pack();
    if (socket.IsNotNull())
    {
        // socket->Send(transMsg->GetPackPointer(), transMsg->GetPackSize());
    }
}


void OpenIGTLinkPlugin::handleSpike(SpikePtr event)
{

}


void OpenIGTLinkPlugin::handleBroadcastMessage(String message)
{

}


void OpenIGTLinkPlugin::saveCustomParametersToXml(XmlElement* parentElement)
{

}


void OpenIGTLinkPlugin::loadCustomParametersFromXml(XmlElement* parentElement)
{

}
