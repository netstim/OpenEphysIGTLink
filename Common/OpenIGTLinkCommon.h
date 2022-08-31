#include <CommonLibHeader.h>

#include "igtlOSUtil.h"
#include "igtlServerSocket.h"

class COMMON_LIB OpenIGTLinkCommon
{
public:
    // creation / deletion

    OpenIGTLinkCommon();

    ~OpenIGTLinkCommon();

    void test();

    int startIGTLinkConnection(int port);

    int isConnected();

private:
    static igtl::Socket::Pointer socket;

    JUCE_LEAK_DETECTOR(OpenIGTLinkCommon);
};
