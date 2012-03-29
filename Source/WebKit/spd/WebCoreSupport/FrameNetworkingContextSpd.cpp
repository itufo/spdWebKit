#include "config.h"
#include "FrameNetworkingContextSpd.h"

#include "NotImplemented.h"
#include "ResourceError.h"

using namespace WebCore;

namespace WebKit {

FrameNetworkingContextSpd::FrameNetworkingContextSpd(Frame* frame, const String& userAgent)
    : FrameNetworkingContext(frame)
    , m_userAgent(userAgent)
{
}

String FrameNetworkingContextSpd::userAgent() const
{
    return m_userAgent;
}

String FrameNetworkingContextSpd::referrer() const
{
    return frame()->loader()->referrer();
}

WebCore::ResourceError FrameNetworkingContextSpd::blockedError(const WebCore::ResourceRequest&) const
{
    notImplemented();
    return WebCore::ResourceError();
}

} // namespace WebKit
