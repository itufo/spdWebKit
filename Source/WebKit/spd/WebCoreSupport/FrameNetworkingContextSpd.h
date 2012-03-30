#ifndef FrameNetworkingContextSpd_h
#define FrameNetworkingContextSpd_h

#include "FrameNetworkingContext.h"

namespace WebKit {

class FrameNetworkingContextSpd : public WebCore::FrameNetworkingContext {
public:
    static PassRefPtr<FrameNetworkingContextSpd> create(WebCore::Frame* frame, const WTF::String& userAgent)
    {
        return adoptRef(new FrameNetworkingContextSpd(frame, userAgent));
    }

    virtual WTF::String userAgent() const;
    virtual WTF::String referrer() const;
    virtual WebCore::ResourceError blockedError(const WebCore::ResourceRequest&) const;

private:
    FrameNetworkingContextSpd(WebCore::Frame* frame, const WTF::String& userAgent);

    WTF::String m_userAgent;
};

} // namespace WebKit

#endif // FrameNetworkingContextSpd_h
