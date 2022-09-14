#ifndef OpenIGTLinkLogic_H_DEFINED
#define OpenIGTLinkLogic_H_DEFINED

#include <CommonLibHeader.h>
#include "igtlSmartPointer.h"

namespace igtl
{
    class Socket;
    extern template class SmartPointer<Socket>;
}

class COMMON_LIB OpenIGTLinkLogic
{
public:
    OpenIGTLinkLogic();

    ~OpenIGTLinkLogic();

    bool startIGTLinkConnection(int port);

    bool isConnected();

    void closeConnection();

    void sendTransformMessage(String deviceName, Array<float> values);
    void sendStringMessage(String deviceName, String sendString);
    void sendPointMessage(String deviceName, Array<float> values);

    static int currentPort;

private:
    static igtl::SmartPointer<igtl::Socket> socket;

    JUCE_LEAK_DETECTOR(OpenIGTLinkLogic);
};

#endif