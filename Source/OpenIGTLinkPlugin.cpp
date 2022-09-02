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

    OpenIGTLinkCommon *openIGTLinkLogic = new OpenIGTLinkCommon();
}

OpenIGTLinkPlugin::~OpenIGTLinkPlugin()
{
    openIGTLinkLogic->closeConnection();
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
}

void OpenIGTLinkPlugin::saveCustomParametersToXml(XmlElement *parentElement)
{
}

void OpenIGTLinkPlugin::loadCustomParametersFromXml(XmlElement *parentElement)
{
}

bool OpenIGTLinkPlugin::startIGTLConnection()
{
    return openIGTLinkLogic->startIGTLinkConnection(getParameter("port")->getValue());
}

void OpenIGTLinkPlugin::closeIGTLConnection()
{
    openIGTLinkLogic->closeConnection();
}