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

#include "OpenIGTLinkCommon.h"

#include "igtlOSUtil.h"
#include "igtlTransformMessage.h"
#include "igtlPointMessage.h"
#include "igtlStringMessage.h"
#include "igtlServerSocket.h"

OpenIGTLinkPlugin::OpenIGTLinkPlugin()
    : GenericProcessor("OpenIGTLink")
{

    addIntParameter(Parameter::GLOBAL_SCOPE, "port", "The port to create the server", 18944, 0, 100000);
}

OpenIGTLinkPlugin::~OpenIGTLinkPlugin()
{
    // if (socket.IsNotNull())
    //     socket->CloseSocket();
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
    std::cout << "\nrecieve: " << message << std::endl;
    if (message.startsWith("IGTL"))
    {
        StringArray subMessages;
        subMessages.addTokens(message, ";", "\"");

        for (int m = 0; m < subMessages.size(); m++)
        {
            StringArray messageParts;
            messageParts.addTokens(subMessages[m], ":", "\"");

            int messageIdx = 1;
            String messageType = messageParts[messageIdx++];

            if (messageType.equalsIgnoreCase("Transform"))
            {
                if (messageParts.size() < 15)
                    return;

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
                // if (socket.IsNotNull())
                // {
                //     socket->Send(transMsg->GetPackPointer(), transMsg->GetPackSize());
                // }
            }
            else if (messageType.equalsIgnoreCase("Point"))
            {
                igtl::PointMessage::Pointer pointMsg = igtl::PointMessage::New();
                pointMsg->SetDeviceName(messageParts[messageIdx++].toStdString());
                for (; messageIdx < messageParts.size(); messageIdx++)
                {
                    StringArray pointParts;
                    pointParts.addTokens(messageParts[messageIdx], ",", "\"");
                    igtl::PointElement::Pointer point = igtl::PointElement::New();
                    point->SetPosition(pointParts[0].getFloatValue(), pointParts[1].getFloatValue(), pointParts[2].getFloatValue());
                    point->SetName(pointParts[3].toStdString().c_str());
                    point->SetGroupName("GROUP_0");
                    point->SetRGBA(0x00, 0x00, 0xFF, 0xFF);
                    point->SetRadius(75.0);
                    point->SetOwner("IMAGE_0");
                    pointMsg->AddPointElement(point);
                }
                pointMsg->Pack();
                // if (socket.IsNotNull())
                // {
                //     socket->Send(pointMsg->GetPackPointer(), pointMsg->GetPackSize());
                // }
            }
            else if (messageType.equalsIgnoreCase("String"))
            {
                igtl::StringMessage::Pointer strMsg = igtl::StringMessage::New();
                strMsg->SetDeviceName(messageParts[messageIdx++].toStdString());
                strMsg->SetString(messageParts[messageIdx++].toStdString());
                strMsg->Pack();
                // if (socket.IsNotNull())
                // {
                //     socket->Send(strMsg->GetPackPointer(), strMsg->GetPackSize());
                // }
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

    OpenIGTLinkCommon *c = new OpenIGTLinkCommon();
    c->test();
    c->startIGTLinkConnection(18944);
}