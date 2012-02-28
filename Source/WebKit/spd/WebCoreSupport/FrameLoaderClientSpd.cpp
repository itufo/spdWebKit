/*
 * Copyright (C) 2006 Zack Rusin <zack@kde.org>
 * Copyright (C) 2006, 2011 Apple Inc. All rights reserved.
 * Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies)
 * Copyright (C) 2008 Collabora Ltd. All rights reserved.
 * Copyright (C) 2008 Holger Hans Peter Freyther
 * Copyright (C) 2008 Kenneth Rohde Christiansen
 * Copyright (C) 2009-2010 ProFUSION embedded systems
 * Copyright (C) 2009-2010 Samsung Electronics
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
#include "FrameLoaderClientSpd.h"

#include "APICast.h"
#include "DocumentLoader.h"
#include "FormState.h"
#include "FrameLoader.h"
//#include "FrameNetworkingContextSpd.h"
#include "FrameTree.h"
#include "FrameView.h"
#include "HTMLFormElement.h"
#include "MIMETypeRegistry.h"
#include "NotImplemented.h"
#include "Page.h"
#include "PluginDatabase.h"
#include "ProgressTracker.h"
#include "RenderPart.h"
#include "ResourceRequest.h"
#include "Settings.h"
#include "WebKitVersion.h"
//#include "ewk_logging.h"
//#include "ewk_private.h"
//#include <Ecore_Evas.h>
#include <wtf/text/CString.h>
#include <wtf/text/StringConcatenate.h>

using namespace WebCore;

namespace WebCore {

FrameLoaderClientSpd::FrameLoaderClientSpd(spd_Object* view)
    : m_view(view)
    , m_frame(0)
    , m_userAgent("")
    , m_customUserAgent("")
    , m_pluginView(0)
    , m_hasSentResponseToPlugin(false)
    , m_hasRepresentation(false)
{
}

static String composeUserAgent()
{
    //TODO jack add 2012-02-27
    return String("spider");
    //return String(ewk_settings_default_user_agent_get());
}

void FrameLoaderClientSpd::setCustomUserAgent(const String& agent)
{
    m_customUserAgent = agent;
}

const String& FrameLoaderClientSpd::customUserAgent() const
{
    return m_customUserAgent;
}

String FrameLoaderClientSpd::userAgent(const KURL&)
{
    if (!m_customUserAgent.isEmpty())
        return m_customUserAgent;

    if (m_userAgent.isEmpty())
        m_userAgent = composeUserAgent();
    return m_userAgent;
}

void FrameLoaderClientSpd::callPolicyFunction(FramePolicyFunction function, PolicyAction action)
{
//TODO jack add 2012-02-27
/*
    Frame* f = EWKPrivate::coreFrame(m_frame);
    ASSERT(f);
    (f->loader()->policyChecker()->*function)(action);
*/
}

WTF::PassRefPtr<DocumentLoader> FrameLoaderClientSpd::createDocumentLoader(const ResourceRequest& request, const SubstituteData& substituteData)
{
    RefPtr<DocumentLoader> loader = DocumentLoader::create(request, substituteData);
    if (substituteData.isValid())
        loader->setDeferMainResourceDataLoad(false);
    return loader.release();
}

void FrameLoaderClientSpd::dispatchWillSubmitForm(FramePolicyFunction function, PassRefPtr<FormState>)
{
    // FIXME: This is surely too simple
    ASSERT(function);
    callPolicyFunction(function, PolicyUse);
}

void FrameLoaderClientSpd::committedLoad(DocumentLoader* loader, const char* data, int length)
{
    if (!m_pluginView)
        loader->commitData(data, length);

    // We re-check here as the plugin can have been created
    if (m_pluginView) {
        if (!m_hasSentResponseToPlugin) {
            m_pluginView->didReceiveResponse(loader->response());
            m_hasSentResponseToPlugin = true;
        }
        m_pluginView->didReceiveData(data, length);
    }
}

void FrameLoaderClientSpd::dispatchDidReplaceStateWithinPage()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidPushStateWithinPage()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidPopStateWithinPage()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidReceiveAuthenticationChallenge(DocumentLoader*, unsigned long  identifier, const AuthenticationChallenge&)
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidCancelAuthenticationChallenge(DocumentLoader*, unsigned long  identifier, const AuthenticationChallenge&)
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchWillSendRequest(DocumentLoader* loader, unsigned long identifier, ResourceRequest& coreRequest, const ResourceResponse& coreResponse)
{
    //TODO jack add 2012-02-27
    return;
/*
    CString url = coreRequest.url().string().utf8();
    DBG("Resource url=%s", url.data());

    Ewk_Frame_Resource_Request request = { 0, identifier };
    Ewk_Frame_Resource_Request orig = request; // Initialize const fields. 

    orig.url = request.url = url.data();

    ewk_frame_request_will_send(m_frame, &request);

    // We want to distinguish between a request for a document to be loaded into
    // the main frame, a sub-frame, or the sub-objects in that document (via Chromium).
    if (loader) {
        const FrameLoader* frameLoader = loader->frameLoader();
        const bool isMainFrameRequest = (loader == frameLoader->provisionalDocumentLoader() && frameLoader->isLoadingMainFrame());
        if (isMainFrameRequest)
            evas_object_smart_callback_call(m_view, "resource,request,willsend", &request);
    }

    if (request.url != orig.url) {
        coreRequest.setURL(KURL(KURL(), request.url));

        // Calling client might have changed our url pointer.
        // Free the new allocated string.
        free(const_cast<char*>(request.url));
    }
*/
}

bool FrameLoaderClientSpd::shouldUseCredentialStorage(DocumentLoader*, unsigned long)
{
    notImplemented();
    return false;
}

void FrameLoaderClientSpd::assignIdentifierToInitialRequest(unsigned long identifier, DocumentLoader*, const ResourceRequest& coreRequest)
{
    CString url = coreRequest.url().string().utf8();
    //DBG("Resource url=%s", url.data());

    //TODO jack add 2012-02-27
/*
    Ewk_Frame_Resource_Request request = { 0, identifier };
    ewk_frame_request_assign_identifier(m_frame, &request);
*/
}

void FrameLoaderClientSpd::postProgressStartedNotification()
{
    //ewk_frame_load_started(m_frame);
    postProgressEstimateChangedNotification();
}

void FrameLoaderClientSpd::postProgressEstimateChangedNotification()
{
    //ewk_frame_load_progress_changed(m_frame);
}

void FrameLoaderClientSpd::postProgressFinishedNotification()
{
   //TODO jack add 2012-02-27
   return;
/*
    if (m_loadError.isNull())
        ewk_frame_load_finished(m_frame, 0, 0, 0, 0, 0);
    else {
        ewk_frame_load_finished(m_frame,
                                m_loadError.domain().utf8().data(),
                                m_loadError.errorCode(),
                                m_loadError.isCancellation(),
                                m_loadError.localizedDescription().utf8().data(),
                                m_loadError.failingURL().utf8().data());
    }
*/
}

void FrameLoaderClientSpd::frameLoaderDestroyed()
{
/*
    if (m_frame)
        ewk_frame_core_gone(m_frame);
*/
    m_frame = 0;

    delete this;
}

void FrameLoaderClientSpd::dispatchDidReceiveResponse(DocumentLoader* loader, unsigned long, const ResourceResponse& response)
{
/*
    // Update our knowledge of request soup flags - some are only set
    // after the request is done.
    loader->request().setSoupMessageFlags(response.soupMessageFlags());

    m_response = response;
*/
}

void FrameLoaderClientSpd::dispatchDecidePolicyForResponse(FramePolicyFunction function, const ResourceResponse& response, const ResourceRequest& resourceRequest)
{
    // we need to call directly here (currently callPolicyFunction does that!)
    ASSERT(function);

    if (resourceRequest.isNull()) {
        callPolicyFunction(function, PolicyIgnore);
        return;
    }

    if (canShowMIMEType(response.mimeType()))
        callPolicyFunction(function, PolicyUse);
    else
        callPolicyFunction(function, PolicyDownload);
}

void FrameLoaderClientSpd::dispatchDecidePolicyForNewWindowAction(FramePolicyFunction function, const NavigationAction& action, const ResourceRequest& resourceRequest, PassRefPtr<FormState>, const String&)
{
/*
    ASSERT(function);
    ASSERT(m_frame);

    if (resourceRequest.isNull()) {
        callPolicyFunction(function, PolicyIgnore);
        return;
    }

    // if not acceptNavigationRequest - look at Qt -> PolicyIgnore;
    // FIXME: do proper check and only reset forms when on PolicyIgnore
    Frame* f = EWKPrivate::coreFrame(m_frame);
    f->loader()->resetMultipleFormSubmissionProtection();
    callPolicyFunction(function, PolicyUse);
*/
}

void FrameLoaderClientSpd::dispatchDecidePolicyForNavigationAction(FramePolicyFunction function, const NavigationAction& action, const ResourceRequest& resourceRequest, PassRefPtr<FormState>)
{
/*
    ASSERT(function);
    ASSERT(m_frame);

    if (resourceRequest.isNull()) {
        callPolicyFunction(function, PolicyIgnore);
        return;
    }

    // if not acceptNavigationRequest - look at Qt -> PolicyIgnore;
    // FIXME: do proper check and only reset forms when on PolicyIgnore
    char* url = strdup(resourceRequest.url().string().utf8().data());
    Ewk_Frame_Resource_Request request = { url, 0 };
    bool ret = ewk_view_navigation_policy_decision(m_view, &request);
    free(url);

    PolicyAction policy;
    if (!ret)
        policy = PolicyIgnore;
    else {
        if (action.type() == NavigationTypeFormSubmitted || action.type() == NavigationTypeFormResubmitted) {
            Frame* f = EWKPrivate::coreFrame(m_frame);
            f->loader()->resetMultipleFormSubmissionProtection();
        }
        policy = PolicyUse;
    }
    callPolicyFunction(function, policy);
*/
}

PassRefPtr<Widget> FrameLoaderClientSpd::createPlugin(const IntSize& pluginSize, HTMLPlugInElement* element, const KURL& url, const Vector<String>& paramNames, const Vector<String>& paramValues, const String& mimeType, bool loadManually)
{
   return NULL;
/*
    ASSERT(m_frame);
    ASSERT(m_view);

    return ewk_view_plugin_create(m_view, m_frame, pluginSize,
                                  element, url, paramNames, paramValues,
                                  mimeType, loadManually);
*/
}

PassRefPtr<Frame> FrameLoaderClientSpd::createFrame(const KURL& url, const String& name, HTMLFrameOwnerElement* ownerElement, const String& referrer, bool allowsScrolling, int marginWidth, int marginHeight)
{
    //TODO jack add 2012-02-27
    return NULL;
/*
    ASSERT(m_frame);
    ASSERT(m_view);

    return ewk_view_frame_create(m_view, m_frame, name, ownerElement, url, referrer);
*/
}

void FrameLoaderClientSpd::didTransferChildFrameToNewDocument(Page*)
{
/*
    ASSERT(m_frame);

    Frame* currentFrame = EWKPrivate::coreFrame(m_frame);
    spd_Object* currentView = ewk_frame_view_get(m_frame);
    Frame* parentFrame = currentFrame->tree()->parent();

    FrameLoaderClientSpd* client = static_cast<FrameLoaderClientSpd*>(parentFrame->loader()->client());
    spd_Object* clientFrame = client ? client->webFrame() : 0;
    spd_Object* clientView = ewk_frame_view_get(clientFrame);

    if (currentView != clientView) {
        ewk_frame_view_set(m_frame, clientView);
        m_view = clientView;
    }

    ASSERT(ewk_view_core_page_get(ewk_frame_view_get(m_frame)) == currentFrame->page());
*/
}

void FrameLoaderClientSpd::transferLoadingResourceFromPage(ResourceLoader*, const ResourceRequest&, Page*)
{
}

void FrameLoaderClientSpd::redirectDataToPlugin(Widget* pluginWidget)
{
    ASSERT(!m_pluginView);
    m_pluginView = static_cast<PluginView*>(pluginWidget);
    m_hasSentResponseToPlugin = false;
}

PassRefPtr<Widget> FrameLoaderClientSpd::createJavaAppletWidget(const IntSize&, HTMLAppletElement*, const KURL& baseURL,
                                                                const Vector<String>& paramNames, const Vector<String>& paramValues)
{
    notImplemented();
    return 0;
}

ObjectContentType FrameLoaderClientSpd::objectContentType(const KURL& url, const String& mimeType, bool shouldPreferPlugInsForImages)
{
    // FIXME: once plugin support is enabled, this method needs to correctly handle the 'shouldPreferPlugInsForImages' flag. See
    // WebCore::FrameLoader::defaultObjectContentType() for an example.
    UNUSED_PARAM(shouldPreferPlugInsForImages);

    if (url.isEmpty() && mimeType.isEmpty())
        return ObjectContentNone;

    // We don't use MIMETypeRegistry::getMIMETypeForPath() because it returns "application/octet-stream" upon failure
    String type = mimeType;
    if (type.isEmpty())
        type = MIMETypeRegistry::getMIMETypeForExtension(url.path().substring(url.path().reverseFind('.') + 1));

    if (type.isEmpty())
        return ObjectContentFrame;

    if (MIMETypeRegistry::isSupportedImageMIMEType(type))
        return ObjectContentImage;

#if 0 // PluginDatabase is disabled until we have Plugin system done.
    if (PluginDatabase::installedPlugins()->isMIMETypeRegistered(mimeType))
        return ObjectContentNetscapePlugin;
#endif

    if (MIMETypeRegistry::isSupportedNonImageMIMEType(type))
        return ObjectContentFrame;

    if (url.protocol() == "about")
        return ObjectContentFrame;

    return ObjectContentNone;
}

String FrameLoaderClientSpd::overrideMediaType() const
{
    notImplemented();
    return String();
}

void FrameLoaderClientSpd::dispatchDidClearWindowObjectInWorld(DOMWrapperWorld* world)
{
/*
    if (world != mainThreadNormalWorld())
        return;

    Frame* coreFrame = EWKPrivate::coreFrame(m_frame);
    ASSERT(coreFrame);

    Settings* settings = coreFrame->settings();
    if (!settings || !settings->isScriptEnabled())
        return;

    Ewk_Window_Object_Cleared_Event event;
    event.context = toGlobalRef(coreFrame->script()->globalObject(mainThreadNormalWorld())->globalExec());
    event.windowObject = toRef(coreFrame->script()->globalObject(mainThreadNormalWorld()));
    event.frame = m_frame;

    evas_object_smart_callback_call(m_view, "window,object,cleared", &event);

#if ENABLE(NETSCAPE_PLUGIN_API)
    ewk_view_js_window_object_clear(m_view, m_frame);
#endif
*/
}

void FrameLoaderClientSpd::documentElementAvailable()
{
    return;
}

void FrameLoaderClientSpd::didPerformFirstNavigation() const
{
    //ewk_frame_did_perform_first_navigation(m_frame);
}

void FrameLoaderClientSpd::registerForIconNotification(bool)
{
    notImplemented();
}

void FrameLoaderClientSpd::setMainFrameDocumentReady(bool)
{
    // this is only interesting once we provide an external API for the DOM
}

bool FrameLoaderClientSpd::hasWebView() const
{
    if (!m_view)
        return false;

    return true;
}

bool FrameLoaderClientSpd::hasFrameView() const
{
    notImplemented();
    return true;
}

void FrameLoaderClientSpd::dispatchDidFinishLoad()
{
    m_loadError = ResourceError(); /* clears previous error */
}

void FrameLoaderClientSpd::frameLoadCompleted()
{
    // Note: Can be called multiple times.
}

void FrameLoaderClientSpd::saveViewStateToItem(HistoryItem* item)
{
    //ewk_frame_view_state_save(m_frame, item);
}

void FrameLoaderClientSpd::restoreViewState()
{
    ASSERT(m_frame);
    ASSERT(m_view);

    //ewk_view_restore_state(m_view, m_frame);
}

void FrameLoaderClientSpd::updateGlobalHistoryRedirectLinks()
{
}

bool FrameLoaderClientSpd::shouldGoToHistoryItem(HistoryItem* item) const
{
    // FIXME: This is a very simple implementation. More sophisticated
    // implementation would delegate the decision to a PolicyDelegate.
    // See mac implementation for example.
    return item;
}

bool FrameLoaderClientSpd::shouldStopLoadingForHistoryItem(HistoryItem* item) const
{
    return true;
}

void FrameLoaderClientSpd::didDisplayInsecureContent()
{
    //ewk_frame_mixed_content_displayed_set(m_frame, true);
}

void FrameLoaderClientSpd::didRunInsecureContent(SecurityOrigin*, const KURL&)
{
    //ewk_frame_mixed_content_run_set(m_frame, true);
}

void FrameLoaderClientSpd::didDetectXSS(const KURL&, bool)
{
    notImplemented();
}

void FrameLoaderClientSpd::makeRepresentation(DocumentLoader*)
{
    m_hasRepresentation = true;
}

void FrameLoaderClientSpd::forceLayout()
{
    //ewk_frame_force_layout(m_frame);
}

void FrameLoaderClientSpd::forceLayoutForNonHTML()
{
}

void FrameLoaderClientSpd::setCopiesOnScroll()
{
    // apparently mac specific (Qt comment)
}

void FrameLoaderClientSpd::detachedFromParent2()
{
}

void FrameLoaderClientSpd::detachedFromParent3()
{
}

void FrameLoaderClientSpd::loadedFromCachedPage()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidHandleOnloadEvents()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidReceiveServerRedirectForProvisionalLoad()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidCancelClientRedirect()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchWillPerformClientRedirect(const KURL&, double, double)
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidChangeLocationWithinPage()
{
/*
    ewk_frame_uri_changed(m_frame);

    if (ewk_view_frame_main_get(m_view) != m_frame)
        return;
    ewk_view_uri_changed(m_view);
*/
}

void FrameLoaderClientSpd::dispatchWillClose()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidReceiveIcon()
{
    /* report received favicon only for main frame. */
/*
    if (ewk_view_frame_main_get(m_view) != m_frame)
        return;

    ewk_view_frame_main_icon_received(m_view);
*/
}

void FrameLoaderClientSpd::dispatchDidStartProvisionalLoad()
{
/*
    ewk_frame_load_provisional(m_frame);
    if (ewk_view_frame_main_get(m_view) == m_frame)
        ewk_view_load_provisional(m_view);
*/
}

void FrameLoaderClientSpd::dispatchDidReceiveTitle(const StringWithDirection& title)
{
/*
    // FIXME: use direction of title.
    CString cs = title.string().utf8();
    ewk_frame_title_set(m_frame, cs.data());

    if (ewk_view_frame_main_get(m_view) != m_frame)
        return;
    ewk_view_title_set(m_view, cs.data());
*/
}

void FrameLoaderClientSpd::dispatchDidChangeIcons(WebCore::IconType)
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidCommitLoad()
{
/*
    ewk_frame_uri_changed(m_frame);
    if (ewk_view_frame_main_get(m_view) != m_frame)
        return;
    ewk_view_title_set(m_view, 0);
    ewk_view_uri_changed(m_view);
*/
}

void FrameLoaderClientSpd::dispatchDidFinishDocumentLoad()
{
    //ewk_frame_load_document_finished(m_frame);
}

void FrameLoaderClientSpd::dispatchDidFirstLayout()
{
    //ewk_frame_load_firstlayout_finished(m_frame);
}

void FrameLoaderClientSpd::dispatchDidFirstVisuallyNonEmptyLayout()
{
    //ewk_frame_load_firstlayout_nonempty_finished(m_frame);
}

void FrameLoaderClientSpd::dispatchShow()
{
    //ewk_view_load_show(m_view);
}

void FrameLoaderClientSpd::cancelPolicyCheck()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidLoadMainResource(DocumentLoader*)
{
    notImplemented();
}

void FrameLoaderClientSpd::revertToProvisionalState(DocumentLoader*)
{
    m_hasRepresentation = true;
}

void FrameLoaderClientSpd::willChangeTitle(DocumentLoader*)
{
    // no need for, dispatchDidReceiveTitle is the right callback
}

void FrameLoaderClientSpd::didChangeTitle(DocumentLoader*)
{
    // no need for, dispatchDidReceiveTitle is the right callback
}

bool FrameLoaderClientSpd::canHandleRequest(const ResourceRequest&) const
{
    notImplemented();
    return true;
}

bool FrameLoaderClientSpd::canShowMIMETypeAsHTML(const String& MIMEType) const
{
    notImplemented();
    return false;
}

bool FrameLoaderClientSpd::canShowMIMEType(const String& MIMEType) const
{
    if (MIMETypeRegistry::isSupportedImageMIMEType(MIMEType))
        return true;

    if (MIMETypeRegistry::isSupportedNonImageMIMEType(MIMEType))
        return true;

#if 0 // PluginDatabase is disabled until we have Plugin system done.
    if (PluginDatabase::installedPlugins()->isMIMETypeRegistered(MIMEType))
        return true;
#endif

    return false;
}

bool FrameLoaderClientSpd::representationExistsForURLScheme(const String&) const
{
    return false;
}

String FrameLoaderClientSpd::generatedMIMETypeForURLScheme(const String&) const
{
    notImplemented();
    return String();
}

void FrameLoaderClientSpd::finishedLoading(DocumentLoader* documentLoader)
{
    if (!m_pluginView) {
        if (m_hasRepresentation)
            documentLoader->writer()->setEncoding("", false);
        return;
    }
    m_pluginView->didFinishLoading();
    m_pluginView = 0;
    m_hasSentResponseToPlugin = false;
}


void FrameLoaderClientSpd::provisionalLoadStarted()
{
    notImplemented();
}

void FrameLoaderClientSpd::didFinishLoad()
{
    notImplemented();
}

void FrameLoaderClientSpd::prepareForDataSourceReplacement()
{
    notImplemented();
}

void FrameLoaderClientSpd::setTitle(const StringWithDirection& title, const KURL& url)
{
    // no need for, dispatchDidReceiveTitle is the right callback
}

void FrameLoaderClientSpd::dispatchDidReceiveContentLength(DocumentLoader*, unsigned long identifier, int dataLength)
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidFinishLoading(DocumentLoader*, unsigned long identifier)
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidFailLoading(DocumentLoader* loader, unsigned long identifier, const ResourceError& err)
{
    notImplemented();
}

bool FrameLoaderClientSpd::dispatchDidLoadResourceFromMemoryCache(DocumentLoader*, const ResourceRequest&, const ResourceResponse&, int length)
{
    notImplemented();
    return false;
}

void FrameLoaderClientSpd::dispatchDidLoadResourceByXMLHttpRequest(unsigned long, const String&)
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidFailProvisionalLoad(const ResourceError& err)
{
    dispatchDidFailLoad(err);
}

void FrameLoaderClientSpd::dispatchDidFailLoad(const ResourceError& err)
{
/*
    if (!shouldFallBack(err))
        return;

    m_loadError = err;
    ewk_frame_load_error(m_frame,
                         m_loadError.domain().utf8().data(),
                         m_loadError.errorCode(), m_loadError.isCancellation(),
                         m_loadError.localizedDescription().utf8().data(),
                         m_loadError.failingURL().utf8().data());
*/
}

void FrameLoaderClientSpd::download(ResourceHandle*, const ResourceRequest& request, const ResourceResponse&)
{
/*
    if (!m_view)
        return;

    CString url = request.url().string().utf8();
    Ewk_Download download;

    download.url = url.data();
    ewk_view_download_request(m_view, &download);
*/
}

// copied from WebKit/Misc/WebKitErrors[Private].h
enum {
    WebKitErrorCannotShowMIMEType = 100,
    WebKitErrorCannotShowURL = 101,
    WebKitErrorFrameLoadInterruptedByPolicyChange = 102,
    WebKitErrorCannotUseRestrictedPort = 103,
    WebKitErrorCannotFindPlugIn = 200,
    WebKitErrorCannotLoadPlugIn = 201,
    WebKitErrorJavaUnavailable = 202,
};

ResourceError FrameLoaderClientSpd::cancelledError(const ResourceRequest& request)
{
    ResourceError error("Error", -999, request.url().string(),
                        "Request cancelled");
    error.setIsCancellation(true);
    return error;
}

ResourceError FrameLoaderClientSpd::blockedError(const ResourceRequest& request)
{
    return ResourceError("Error", WebKitErrorCannotUseRestrictedPort, request.url().string(),
                         "Request blocked");
}

ResourceError FrameLoaderClientSpd::cannotShowURLError(const ResourceRequest& request)
{
    return ResourceError("Error", WebKitErrorCannotShowURL, request.url().string(),
                         "Cannot show URL");
}

ResourceError FrameLoaderClientSpd::interruptedForPolicyChangeError(const ResourceRequest& request)
{
    return ResourceError("Error", WebKitErrorFrameLoadInterruptedByPolicyChange,
                         request.url().string(), "Frame load interrupted by policy change");
}

ResourceError FrameLoaderClientSpd::cannotShowMIMETypeError(const ResourceResponse& response)
{
    return ResourceError("Error", WebKitErrorCannotShowMIMEType, response.url().string(),
                         "Cannot show mimetype");
}

ResourceError FrameLoaderClientSpd::fileDoesNotExistError(const ResourceResponse& response)
{
    return ResourceError("Error", -998 /* ### */, response.url().string(),
                         "File does not exist");
}

ResourceError FrameLoaderClientSpd::pluginWillHandleLoadError(const ResourceResponse&)
{
    notImplemented();
    return ResourceError("Error", 0, "", "");
}

bool FrameLoaderClientSpd::shouldFallBack(const ResourceError& error)
{
    return !(error.isCancellation() || (error.errorCode() == WebKitErrorFrameLoadInterruptedByPolicyChange));
}

bool FrameLoaderClientSpd::canCachePage() const
{
    return false;
}

Frame* FrameLoaderClientSpd::dispatchCreatePage(const NavigationAction&)
{ 
    //TODO jack add 2012-02-27
    return NULL;
/*
    if (!m_view)
        return 0;

    spd_Object* newView = ewk_view_window_create(m_view, EINA_FALSE, 0);
    spd_Object* mainFrame;
    if (!newView)
        mainFrame = m_frame;
    else
        mainFrame = ewk_view_frame_main_get(newView);

    return EWKPrivate::coreFrame(mainFrame);
*/
}

void FrameLoaderClientSpd::dispatchUnableToImplementPolicy(const ResourceError&)
{
    notImplemented();
}

void FrameLoaderClientSpd::setMainDocumentError(DocumentLoader* loader, const ResourceError& error)
{
    if (!m_pluginView)
        return;
    m_pluginView->didFail(error);
    m_pluginView = 0;
    m_hasSentResponseToPlugin = false;
}

void FrameLoaderClientSpd::startDownload(const ResourceRequest& request, const String& /* suggestedName */)
{
    //TODO jack add 2012-02-27
    return ;
/*
    if (!m_view)
        return;

    CString url = request.url().string().utf8();
    Ewk_Download download;

    download.url = url.data();
    ewk_view_download_request(m_view, &download);
*/
}

void FrameLoaderClientSpd::updateGlobalHistory()
{
    notImplemented();
}

void FrameLoaderClientSpd::savePlatformDataToCachedFrame(CachedFrame*)
{
    notImplemented();
}

void FrameLoaderClientSpd::transitionToCommittedFromCachedFrame(CachedFrame*)
{
}

void FrameLoaderClientSpd::transitionToCommittedForNewPage()
{
/*
    ASSERT(m_frame);
    ASSERT(m_view);

    ewk_frame_view_create_for_view(m_frame, m_view);

    if (m_frame == ewk_view_frame_main_get(m_view)) {
        ewk_view_frame_view_creation_notify(m_view);
        ewk_view_frame_main_cleared(m_view);
    }
*/
}

void FrameLoaderClientSpd::didSaveToPageCache()
{
}

void FrameLoaderClientSpd::didRestoreFromPageCache()
{
}

void FrameLoaderClientSpd::dispatchDidBecomeFrameset(bool)
{
}

PassRefPtr<FrameNetworkingContext> FrameLoaderClientSpd::createNetworkingContext()
{
    //TODO jack add 2012-02-27
    return NULL;
    //return FrameNetworkingContextSpd::create(EWKPrivate::coreFrame(m_frame), m_frame);
}

}
