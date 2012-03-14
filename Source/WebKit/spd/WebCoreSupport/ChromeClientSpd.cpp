#include "config.h"
#include "ChromeClientSpd.h"

#include "FileChooser.h"
#include "FileIconLoader.h"
#include "Icon.h"
#include "NotImplemented.h"
#include "NavigationAction.h"
#include "WebView.h"
#include <wtf/text/CString.h>

using namespace WebCore;

namespace WebKit {

ChromeClientSpd::ChromeClientSpd(WebView* webView)
    : m_webView(webView)
{
    ASSERT(m_webView);
}

void ChromeClientSpd::chromeDestroyed()
{
    delete this;
}

FloatRect ChromeClientSpd::windowRect()
{
}

void ChromeClientSpd::setWindowRect(const FloatRect&)
{
    notImplemented();
}

FloatRect ChromeClientSpd::pageRect()
{
    return windowRect();
}

void ChromeClientSpd::focus()
{
    notImplemented();
}

void ChromeClientSpd::unfocus()
{
    notImplemented();
}

Page* ChromeClientSpd::createWindow(Frame*, const FrameLoadRequest&, const WindowFeatures&, const NavigationAction&)
{
    notImplemented();
    return 0;
}

void ChromeClientSpd::show()
{
    notImplemented();
}

bool ChromeClientSpd::canRunModal()
{
    notImplemented();
    return false;
}

void ChromeClientSpd::runModal()
{
    notImplemented();
}

void ChromeClientSpd::setToolbarsVisible(bool)
{
    notImplemented();
}

bool ChromeClientSpd::toolbarsVisible()
{
    return false;
}

void ChromeClientSpd::setStatusbarVisible(bool)
{
    notImplemented();
}

bool ChromeClientSpd::statusbarVisible()
{
    notImplemented();
    return false;
}

void ChromeClientSpd::setScrollbarsVisible(bool)
{
    notImplemented();
}

bool ChromeClientSpd::scrollbarsVisible()
{
    notImplemented();
    return false;
}

void ChromeClientSpd::setMenubarVisible(bool)
{
    notImplemented();
}

bool ChromeClientSpd::menubarVisible()
{
    notImplemented();
    return false;
}

void ChromeClientSpd::setResizable(bool)
{
    notImplemented();
}

void ChromeClientSpd::closeWindowSoon()
{
}

bool ChromeClientSpd::canTakeFocus(FocusDirection)
{
    return true;
}

void ChromeClientSpd::takeFocus(FocusDirection)
{
    unfocus();
}

void ChromeClientSpd::focusedNodeChanged(Node*)
{
    notImplemented();
}

void ChromeClientSpd::focusedFrameChanged(Frame*)
{
}

bool ChromeClientSpd::canRunBeforeUnloadConfirmPanel()
{
    return true;
}

bool ChromeClientSpd::runBeforeUnloadConfirmPanel(const String& message, Frame* frame)
{
    return runJavaScriptConfirm(frame, message);
}

void ChromeClientSpd::addMessageToConsole(MessageSource, MessageType, MessageLevel, const String&, unsigned int, const String&)
{
    notImplemented();
}

void ChromeClientSpd::runJavaScriptAlert(Frame*, const String& message)
{
    m_webView->runJavaScriptAlert(message);
}

bool ChromeClientSpd::runJavaScriptConfirm(Frame*, const String& message)
{
    return m_webView->runJavaScriptConfirm(message);
}

bool ChromeClientSpd::runJavaScriptPrompt(Frame*, const String& message, const String& defaultValue, String& result)
{
    return m_webView->runJavaScriptPrompt(message, defaultValue, result);
}

void ChromeClientSpd::setStatusbarText(const String&)
{
    notImplemented();
}

bool ChromeClientSpd::shouldInterruptJavaScript()
{
    notImplemented();
    return false;
}

KeyboardUIMode ChromeClientSpd::keyboardUIMode()
{
    return KeyboardAccessTabsToLinks;
}

IntRect ChromeClientSpd::windowResizerRect() const
{
    notImplemented();
    return IntRect();
}

void ChromeClientSpd::invalidateRootView(const IntRect&, bool)
{
    notImplemented();
}

void ChromeClientSpd::invalidateContentsAndRootView(const IntRect& updateRect, bool immediate)
{
}

void ChromeClientSpd::invalidateContentsForSlowScroll(const IntRect& updateRect, bool immediate)
{
    invalidateContentsAndRootView(updateRect, immediate);
}

void ChromeClientSpd::scroll(const IntSize&, const IntRect& rectToScroll, const IntRect&)
{
    invalidateContentsAndRootView(rectToScroll, false);
}

IntRect ChromeClientSpd::rootViewToScreen(const IntRect& rect) const
{
    notImplemented();
    return rect;
}

IntPoint ChromeClientSpd::screenToRootView(const IntPoint& point) const
{
    notImplemented();
    return point;
}

PlatformPageClient ChromeClientSpd::platformPageClient() const
{
    notImplemented();
    return 0;
}

void ChromeClientSpd::contentsSizeChanged(Frame*, const IntSize&) const
{
    notImplemented();
}

void ChromeClientSpd::scrollRectIntoView(const IntRect&) const
{
    notImplemented();
}

void ChromeClientSpd::scrollbarsModeDidChange() const
{
    notImplemented();
}

void ChromeClientSpd::mouseDidMoveOverElement(const HitTestResult&, unsigned)
{
    notImplemented();
}

void ChromeClientSpd::setToolTip(const String&, TextDirection)
{
    notImplemented();
}

void ChromeClientSpd::print(Frame*)
{
    notImplemented();
}

#if ENABLE(SQL_DATABASE)
void ChromeClientSpd::exceededDatabaseQuota(Frame*, const String&)
{
    notImplemented();
}
#endif

void ChromeClientSpd::reachedMaxAppCacheSize(int64_t)
{
    notImplemented();
}

void ChromeClientSpd::reachedApplicationCacheOriginQuota(SecurityOrigin*, int64_t)
{
    notImplemented();
}

#if ENABLE(TOUCH_EVENTS)
void ChromeClientSpd::needTouchEvents(bool)
{
    notImplemented();
}
#endif

#if USE(ACCELERATED_COMPOSITING)
void ChromeClientSpd::attachRootGraphicsLayer(Frame*, GraphicsLayer*)
{
    notImplemented();
}

void ChromeClientSpd::setNeedsOneShotDrawingSynchronization()
{
    notImplemented();
}

void ChromeClientSpd::scheduleCompositingLayerSync()
{
    notImplemented();
}
#endif

void ChromeClientSpd::runOpenPanel(Frame*, PassRefPtr<FileChooser> prpFileChooser)
{
    notImplemented();
}

void ChromeClientSpd::loadIconForFiles(const Vector<String>& filenames, FileIconLoader* loader)
{
    //loader->notifyFinished(Icon::createIconForFiles(filenames));
}

void ChromeClientSpd::setCursor(const Cursor&)
{
    notImplemented();
}

void ChromeClientSpd::setCursorHiddenUntilMouseMoves(bool)
{
    notImplemented();
}

void ChromeClientSpd::setLastSetCursorToCurrentCursor()
{
    notImplemented();
}

void ChromeClientSpd::formStateDidChange(const Node*)
{
    notImplemented();
}

void ChromeClientSpd::requestGeolocationPermissionForFrame(Frame*, Geolocation*)
{
    notImplemented();
}

void ChromeClientSpd::cancelGeolocationPermissionRequestForFrame(Frame*, Geolocation*)
{
    notImplemented();
}

bool ChromeClientSpd::selectItemWritingDirectionIsNatural()
{
    return false;
}

bool ChromeClientSpd::selectItemAlignmentFollowsMenuWritingDirection()
{
    return false;
}

bool ChromeClientSpd::hasOpenedPopup() const
{
    notImplemented();
    return false;
}

PassRefPtr<PopupMenu> ChromeClientSpd::createPopupMenu(PopupMenuClient* client) const
{
}

PassRefPtr<SearchPopupMenu> ChromeClientSpd::createSearchPopupMenu(PopupMenuClient* client) const
{
}

} // namespace WebKit
