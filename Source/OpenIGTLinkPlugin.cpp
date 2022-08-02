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

    addIntParameter(Parameter::GLOBAL_SCOPE, "port", "The port to create the server", 18944, 0, 100000);
}

OpenIGTLinkPlugin::~OpenIGTLinkPlugin()
{
    if (socket.IsNotNull())
        socket->CloseSocket();
}

AudioProcessorEditor *OpenIGTLinkPlugin::createEditor()
{
    editor = std::make_unique<OpenIGTLinkPluginEditor>(this);
    return editor.get();
}

void OpenIGTLinkPlugin::updateSettings()
{
}

void OpenIGTLinkPlugin::process(AudioBuffer<float> &buffer)
{
    checkForEvents(true);
}

void OpenIGTLinkPlugin::handleTTLEvent(TTLEventPtr event)
{
}

void OpenIGTLinkPlugin::handleSpike(SpikePtr event)
{
}

void OpenIGTLinkPlugin::handleBroadcastMessage(String message)
{
    // Example message: IGTL:Transform:TransformName:1:0:0:0:0:1:0:0:0:0:1:0
    if (message.startsWith("IGTL"))
    {
        StringArray messageParts;
        messageParts.addTokens(message, ":", "\"");
        if (messageParts.size() < 15)
        {
            return;
        }

        int messageIdx = 1;
        String messageType = messageParts[messageIdx++];

        if (messageType.equalsIgnoreCase("Transform"))
        {
            igtl::TransformMessage::Pointer transMsg = igtl::TransformMessage::New();
            transMsg->SetDeviceName(messageParts[messageIdx++].toStdString());
            igtl::Matrix4x4 matrix;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    matrix[i][j] = std::stof(messageParts[messageIdx++].toStdString());
                }
            }
            transMsg->SetMatrix(matrix);
            transMsg->Pack();
            if (socket.IsNotNull())
            {
                socket->Send(transMsg->GetPackPointer(), transMsg->GetPackSize());
            }
        }
    }
}

void OpenIGTLinkPlugin::saveCustomParametersToXml(XmlElement *parentElement)
{
}

void OpenIGTLinkPlugin::loadCustomParametersFromXml(XmlElement *parentElement)
{
}

void OpenIGTLinkPlugin::startIGTLConnection()
{
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