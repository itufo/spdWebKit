#ifndef ContextMenuClientSpd_h
#define ContextMenuClientSpd_h

#include "ContextMenuClient.h"

class WebView;

namespace WebKit {

class ContextMenuClientSpd : public WebCore::ContextMenuClient {
public:
    ContextMenuClientSpd(WebView*);

    virtual void contextMenuDestroyed();

    virtual PassOwnPtr<WebCore::ContextMenu> customizeMenu(PassOwnPtr<WebCore::ContextMenu>);
    virtual void contextMenuItemSelected(WebCore::ContextMenuItem*, const WebCore::ContextMenu*);

    virtual void downloadURL(const WebCore::KURL&);
    virtual void copyImageToClipboard(const WebCore::HitTestResult&);
    virtual void searchWithGoogle(const WebCore::Frame*);
    virtual void lookUpInDictionary(WebCore::Frame*);
    virtual void speak(const WTF::String&);
    virtual void stopSpeaking();
    virtual bool isSpeaking();

private:
    WebView* m_webView;
};

} // namespace WebKit

#endif // ContextMenuClientSpd_h
