#ifndef OPENIGTLINKCOMMON_H_DEFINED
#define OPENIGTLINKCOMMON_H_DEFINED

#include <CommonLibHeader.h>

#include "igtlOSUtil.h"
#include "igtlServerSocket.h"

class COMMON_LIB OpenIGTLinkCommon
{
public:
    OpenIGTLinkCommon();

    ~OpenIGTLinkCommon();

    bool startIGTLinkConnection(int port);

    bool isConnected();

    void closeConnection();

    void sendTransformMessage(String deviceName, Array<float> values);
    void sendStringMessage(String deviceName, String sendString);
    void sendPointMessage(String deviceName, Array<float> values);

private:
    static igtl::Socket::Pointer socket;

    JUCE_LEAK_DETECTOR(OpenIGTLinkCommon);
};

#endif