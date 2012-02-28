/*
 * Copyright (C) 2006 Zack Rusin <zack@kde.org>
 * Copyright (C) 2006 Apple Computer, Inc.  All rights reserved.
 * Copyright (C) 2008 Kenneth Rohde Christiansen
 * Copyright (C) 2008 Diego Gonzalez
 * Copyright (C) 2009-2010 ProFUSION embedded systems
 * Copyright (C) 2009-2010 Samsung Electronics
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "ChromeClientSpd.h"

#include "FileChooser.h"
#include "FileIconLoader.h"
#include "FloatRect.h"
#include "FrameLoader.h"
#include "FrameLoaderClientSpd.h"
#include "HitTestResult.h"
#include "IntRect.h"
#include "KURL.h"
#include "NavigationAction.h"
#include "NotImplemented.h"
#include "PlatformString.h"
//#include "PopupMenuSpd.h"
//#include "SearchPopupMenuSpd.h"
#include "SecurityOrigin.h"
#include "ViewportArguments.h"
#include "WindowFeatures.h"
//#include "ewk_private.h"
//#include <Ecore_Evas.h>
//#include <Evas.h>
#include <wtf/text/CString.h>

#if ENABLE(NOTIFICATIONS)
#include "NotificationPresenterClientSpd.h"
#endif

#if ENABLE(SQL_DATABASE)
#include "DatabaseDetails.h"
#include "DatabaseTracker.h"
#endif

using namespace WebCore;

static inline spd_Object* kit(Frame* frame)
{
    if (!frame)
        return 0;

    FrameLoaderClientSpd* client = static_cast<FrameLoaderClientSpd*>(frame->loader()->client());
    return client ? client->webFrame() : 0;
}

namespace WebCore {

ChromeClientSpd::ChromeClientSpd(spd_Object* view)
    : m_view(view)
{
    ASSERT(m_view);
}

ChromeClientSpd::~ChromeClientSpd()
{
}

void ChromeClientSpd::chromeDestroyed()
{
    delete this;
}

void ChromeClientSpd::focusedNodeChanged(Node*)
{
    notImplemented();
}

void ChromeClientSpd::focusedFrameChanged(Frame*)
{
}

FloatRect ChromeClientSpd::windowRect()
{
/*    Ecore_Evas* ee = 0;
    int x, y, w, h;

    ee = ecore_evas_ecore_evas_get(evas_object_evas_get(m_view));
    ecore_evas_geometry_get(ee, &x, &y, &w, &h);
    return FloatRect(x, y, w, h);
*/
    return FloatRect(0, 0, 0, 0);
}

void ChromeClientSpd::setWindowRect(const FloatRect& rect)
{
    return;
/*
    if (!ewk_view_setting_enable_auto_resize_window_get(m_view))
        return;

    Ecore_Evas* ee = 0;
    IntRect intrect = IntRect(rect);

    ee = ecore_evas_ecore_evas_get(evas_object_evas_get(m_view));
    ecore_evas_move(ee, intrect.x(), intrect.y());
    ecore_evas_resize(ee, intrect.width(), intrect.height());
*/
}

FloatRect ChromeClientSpd::pageRect()
{
    return FloatRect(0, 0, 0, 0);
    //return ewk_view_page_rect_get(m_view);
}

void ChromeClientSpd::focus()
{
    //evas_object_focus_set(m_view, EINA_TRUE);
}

void ChromeClientSpd::unfocus()
{
    //evas_object_focus_set(m_view, EINA_FALSE);
}

Page* ChromeClientSpd::createWindow(Frame*, const FrameLoadRequest& frameLoadRequest, const WindowFeatures& features, const NavigationAction&)
{
//TODO jack add 2012-02-27
    return NULL;
/*
    Evas_Object* newView = ewk_view_window_create(m_view, EINA_TRUE, &features);
    if (!newView)
        return 0;

    return ewk_view_core_page_get(newView);
*/
}

void ChromeClientSpd::show()
{
    //ewk_view_ready(m_view);
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

void ChromeClientSpd::setToolbarsVisible(bool visible)
{
    //ewk_view_toolbars_visible_set(m_view, visible);
}

bool ChromeClientSpd::toolbarsVisible()
{
    bool visible;

    //ewk_view_toolbars_visible_get(m_view, &visible);
    return visible;
}

void ChromeClientSpd::setStatusbarVisible(bool visible)
{
    //ewk_view_statusbar_visible_set(m_view, visible);
}

bool ChromeClientSpd::statusbarVisible()
{
    bool visible;

    //ewk_view_statusbar_visible_get(m_view, &visible);
    return visible;
}

void ChromeClientSpd::setScrollbarsVisible(bool visible)
{
    //ewk_view_scrollbars_visible_set(m_view, visible);
}

bool ChromeClientSpd::scrollbarsVisible()
{
    bool visible;

    //ewk_view_scrollbars_visible_get(m_view, &visible);
    return visible;
}

void ChromeClientSpd::setMenubarVisible(bool visible)
{
    //ewk_view_menubar_visible_set(m_view, visible);
}

bool ChromeClientSpd::menubarVisible()
{
    bool visible;

    //ewk_view_menubar_visible_get(m_view, &visible);
    return visible;
}

void ChromeClientSpd::createSelectPopup(PopupMenuClient* client, int selected, const IntRect& rect)
{
    //ewk_view_popup_new(m_view, client, selected, rect);
}

bool ChromeClientSpd::destroySelectPopup()
{
    return true;
    //return ewk_view_popup_destroy(m_view);
}

void ChromeClientSpd::setResizable(bool)
{
    notImplemented();
}

void ChromeClientSpd::closeWindowSoon()
{
    //ewk_view_window_close(m_view);
}

bool ChromeClientSpd::canTakeFocus(FocusDirection coreDirection)
{
//TODO jack add 2012-02-27
    return true;
/*
    // This is called when cycling through links/focusable objects and we
    // reach the last focusable object.
    ASSERT(coreDirection == FocusDirectionForward || coreDirection == FocusDirectionBackward);

    Ewk_Focus_Direction direction = static_cast<Ewk_Focus_Direction>(coreDirection);

    return !ewk_view_focus_can_cycle(m_view, direction);
*/
}

void ChromeClientSpd::takeFocus(FocusDirection)
{
    unfocus();
}

bool ChromeClientSpd::canRunBeforeUnloadConfirmPanel()
{
    return true;
}

bool ChromeClientSpd::runBeforeUnloadConfirmPanel(const String& message, Frame* frame)
{
    return runJavaScriptConfirm(frame, message);
}

void ChromeClientSpd::addMessageToConsole(MessageSource, MessageType, MessageLevel, const String& message,
                                          unsigned int lineNumber, const String& sourceID)
{
    //ewk_view_add_console_message(m_view, message.utf8().data(), lineNumber, sourceID.utf8().data());
}

void ChromeClientSpd::runJavaScriptAlert(Frame* frame, const String& message)
{
    //ewk_view_run_javascript_alert(m_view, kit(frame), message.utf8().data());
}

bool ChromeClientSpd::runJavaScriptConfirm(Frame* frame, const String& message)
{
    return true;
    //return ewk_view_run_javascript_confirm(m_view, kit(frame), message.utf8().data());
}

bool ChromeClientSpd::runJavaScriptPrompt(Frame* frame, const String& message, const String& defaultValue, String& result)
{
    return true;
/*
    char* value = 0;
    ewk_view_run_javascript_prompt(m_view, kit(frame), message.utf8().data(), defaultValue.utf8().data(), &value);
    if (value) {
        result = String::fromUTF8(value);
        free(value);
        return true;
    }
    return false;
*/
}

void ChromeClientSpd::setStatusbarText(const String& string)
{
    //ewk_view_statusbar_text_set(m_view, string.utf8().data());
}

bool ChromeClientSpd::shouldInterruptJavaScript()
{ 
    //TODO jack add 2012-02-27
    return false;
    //return ewk_view_should_interrupt_javascript(m_view);
}

KeyboardUIMode ChromeClientSpd::keyboardUIMode()
{
    return KeyboardAccessTabsToLinks;
}

IntRect ChromeClientSpd::windowResizerRect() const
{
    notImplemented();
    // Implementing this function will make repaint being
    // called during resize, but as this will be done with
    // a minor delay it adds a weird "filling" effect due
    // to us using an evas image for showing the cairo
    // context. So instead of implementing this function
    // we call paint directly during resize with
    // the new object size as its argument.
    return IntRect();
}

void ChromeClientSpd::contentsSizeChanged(Frame* frame, const IntSize& size) const
{
/*
    ewk_frame_contents_size_changed(kit(frame), size.width(), size.height());
    if (ewk_view_frame_main_get(m_view) == kit(frame))
        ewk_view_contents_size_changed(m_view, size.width(), size.height());
*/
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
    return m_view;
}

void ChromeClientSpd::scrollbarsModeDidChange() const
{
}

void ChromeClientSpd::mouseDidMoveOverElement(const HitTestResult& hit, unsigned modifierFlags)
{
/*
    // FIXME, compare with old link, look at Qt impl.
    bool isLink = hit.isLiveLink();
    if (isLink) {
        KURL url = hit.absoluteLinkURL();
        if (!url.isEmpty() && url != m_hoveredLinkURL) {
            const char* link[2];
            TextDirection dir;
            CString urlStr = url.string().utf8();
            CString titleStr = hit.title(dir).utf8();
            link[0] = urlStr.data();
            link[1] = titleStr.data();
            ewk_view_mouse_link_hover_in(m_view, link);
            m_hoveredLinkURL = url;
        }
    } else if (!isLink && !m_hoveredLinkURL.isEmpty()) {
        ewk_view_mouse_link_hover_out(m_view);
        m_hoveredLinkURL = KURL();
    }
*/
}

void ChromeClientSpd::setToolTip(const String& toolTip, TextDirection)
{
    //ewk_view_tooltip_text_set(m_view, toolTip.utf8().data());
}

void ChromeClientSpd::print(Frame* frame)
{
    notImplemented();
}

void ChromeClientSpd::reachedMaxAppCacheSize(int64_t spaceNeeded)
{
    // FIXME: Free some space.
    notImplemented();
}

void ChromeClientSpd::reachedApplicationCacheOriginQuota(SecurityOrigin*, int64_t)
{
    notImplemented();
}

#if ENABLE(TOUCH_EVENTS)
void ChromeClientSpd::needTouchEvents(bool needed)
{
    //ewk_view_need_touch_events_set(m_view, needed);
}
#endif

#if ENABLE(SQL_DATABASE)
void ChromeClientSpd::exceededDatabaseQuota(Frame* frame, const String& databaseName)
{
/*
    uint64_t quota;
    SecurityOrigin* origin = frame->document()->securityOrigin();

    DatabaseDetails details = DatabaseTracker::tracker().detailsForNameAndOrigin(databaseName, origin);
    quota = ewk_view_exceeded_database_quota(m_view,
                                             kit(frame), databaseName.utf8().data(),
                                             details.currentUsage(), details.expectedUsage());
*/
    /* if client did not set quota, and database is being created now, the
     * default quota is applied
     */
/*
    if (!quota && !DatabaseTracker::tracker().hasEntryForOrigin(origin))
        quota = ewk_settings_web_database_default_quota_get();

    DatabaseTracker::tracker().setQuota(origin, quota);
*/
}
#endif

#if ENABLE(NOTIFICATIONS)
NotificationPresenter* ChromeClientSpd::notificationPresenter() const
{
    notImplemented();
    return 0;
}
#endif

void ChromeClientSpd::runOpenPanel(Frame* frame, PassRefPtr<FileChooser> prpFileChooser)
{
/*
    RefPtr<FileChooser> chooser = prpFileChooser;
    Eina_List* selectedFilenames = 0;
    void* filename;
    Vector<String> filenames;

    const FileChooserSettings& settings = chooser->settings();
    bool confirm = ewk_view_run_open_panel(m_view, kit(frame), settings.allowsMultipleFiles, settings.acceptMIMETypes, &selectedFilenames);

    if (!confirm)
        return;

    EINA_LIST_FREE(selectedFilenames, filename) {
        filenames.append((char*)filename);
        free(filename);
    }

    if (chooser->settings().allowsMultipleFiles)
        chooser->chooseFiles(filenames);
    else
        chooser->chooseFile(filenames[0]);
*/
}

void ChromeClientSpd::formStateDidChange(const Node*)
{
    notImplemented();
}

void ChromeClientSpd::setCursor(const Cursor&)
{
    notImplemented();
}

void ChromeClientSpd::setCursorHiddenUntilMouseMoves(bool)
{
    notImplemented();
}

void ChromeClientSpd::requestGeolocationPermissionForFrame(Frame*, Geolocation*)
{
    // See the comment in WebCore/page/ChromeClient.h
    notImplemented();
}

void ChromeClientSpd::cancelGeolocationPermissionRequestForFrame(Frame*, Geolocation*)
{
    notImplemented();
}

void ChromeClientSpd::cancelGeolocationPermissionForFrame(Frame*, Geolocation*)
{
    notImplemented();
}

void ChromeClientSpd::invalidateContents(const IntRect& updateRect, bool immediate)
{
    notImplemented();
}

void ChromeClientSpd::invalidateRootView(const IntRect& updateRect, bool immediate)
{
    notImplemented();
}

void ChromeClientSpd::invalidateContentsAndRootView(const IntRect& updateRect, bool immediate)
{
/*
    if (updateRect.isEmpty())
        return;

    Evas_Coord x, y, w, h;

    x = updateRect.x();
    y = updateRect.y();
    w = updateRect.width();
    h = updateRect.height();
    ewk_view_repaint(m_view, x, y, w, h);
*/
}

void ChromeClientSpd::invalidateContentsForSlowScroll(const IntRect& updateRect, bool immediate)
{
    invalidateContentsAndRootView(updateRect, immediate);
}

void ChromeClientSpd::scroll(const IntSize& scrollDelta, const IntRect& rectToScroll, const IntRect& clipRect)
{
    //ewk_view_scroll(m_view, scrollDelta.width(), scrollDelta.height(), rectToScroll.x(), rectToScroll.y(), rectToScroll.width(), rectToScroll.height(), clipRect.x(), clipRect.y(), clipRect.width(), clipRect.height());
}

void ChromeClientSpd::cancelGeolocationPermissionRequestForFrame(Frame*)
{
    notImplemented();
}

void ChromeClientSpd::iconForFiles(const Vector<String, 0u>&, PassRefPtr<FileChooser>)
{
    notImplemented();
}

void ChromeClientSpd::loadIconForFiles(const Vector<String>&, FileIconLoader*)
{
    notImplemented();
}

void ChromeClientSpd::dispatchViewportPropertiesDidChange(const ViewportArguments& arguments) const
{
    //ewk_view_viewport_attributes_set(m_view, arguments);
}

bool ChromeClientSpd::selectItemWritingDirectionIsNatural()
{
    return true;
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
    return NULL;
    //return adoptRef(new PopupMenuSpd(client));
}

PassRefPtr<SearchPopupMenu> ChromeClientSpd::createSearchPopupMenu(PopupMenuClient* client) const
{
    return NULL;
    //return adoptRef(new SearchPopupMenuSpd(client));
}

#if USE(ACCELERATED_COMPOSITING)
void ChromeClientSpd::attachRootGraphicsLayer(Frame* frame, GraphicsLayer* rootLayer)
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

ChromeClient::CompositingTriggerFlags ChromeClientSpd::allowedCompositingTriggers() const
{
    return 0;
}
#endif

#if ENABLE(FULLSCREEN_API)
bool ChromeClientSpd::supportsFullScreenForElement(const WebCore::Element* element, bool withKeyboard)
{
    if (withKeyboard)
        return false;

    return true;
}

void ChromeClientSpd::enterFullScreenForElement(WebCore::Element* element)
{
    element->document()->webkitWillEnterFullScreenForElement(element);
    element->document()->webkitDidEnterFullScreenForElement(element);
}

void ChromeClientSpd::exitFullScreenForElement(WebCore::Element* element)
{
    element->document()->webkitWillExitFullScreenForElement(element);
    element->document()->webkitDidExitFullScreenForElement(element);
}
#endif
}
