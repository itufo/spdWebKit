#ifndef InspectorClientSpd_h
#define InspectorClientSpd_h

#include "InspectorClient.h"

class WebView;

namespace WebKit {

class InspectorClientSpd : public WebCore::InspectorClient {
public:
    InspectorClientSpd(WebView* webView);
    ~InspectorClientSpd();

    virtual void inspectorDestroyed();

    virtual void openInspectorFrontend(WebCore::InspectorController*);
    virtual void closeInspectorFrontend();
    virtual void bringFrontendToFront();

    virtual void highlight();
    virtual void hideHighlight();

    virtual void populateSetting(const WTF::String& key, WTF::String* value);
    virtual void storeSetting(const WTF::String& key, const WTF::String& value);

    virtual bool sendMessageToFrontend(const WTF::String&);

    void releaseFrontendPage();

private:
    WebView* m_inspectedWebView;
};

} // namespace WebKit

#endif // InspectorClientSpd_h
