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

#include "OpenIGTLinkPluginEditor.h"

OpenIGTLinkPluginEditor::OpenIGTLinkPluginEditor(GenericProcessor *parentNode)
    : GenericEditor(parentNode)
{

    addTextBoxParameterEditor("port", 15, 25);

    // add connect button
    connectButton = new UtilityButton("Connect", Font("Small Text", 13, Font::plain));
    connectButton->setRadius(3.0f);
    connectButton->setBounds(15, 75, 65, 18);
    connectButton->addListener(this);
    connectButton->setTooltip("Connect to IGTL client.");
    addAndMakeVisible(connectButton);

    desiredWidth = 150;
}

void OpenIGTLinkPluginEditor::buttonClicked(Button *button)
{
    if (button == connectButton)
    {
        OpenIGTLinkPlugin *processor = (OpenIGTLinkPlugin *)getProcessor();
        bool connected = false;
        if (connectButton->getLabel().equalsIgnoreCase("Connect"))
        {
            connected = processor->openIGTLinkLogic->startIGTLinkConnection(processor->getParameter("port")->getValue());
        }
        else
        {
            processor->openIGTLinkLogic->closeConnection();
        }
        connectButton->setLabel(connected ? "Disconnect" : "Connect");
    }
}