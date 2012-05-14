#include "config.h"
#include "FrameLoaderClientSpd.h"

#include "DocumentLoader.h"
#include "FrameLoader.h"
#include "FrameNetworkingContextSpd.h"
#include "FrameView.h"
#include "HTMLFormElement.h"
#include "MIMETypeRegistry.h"
#include "NotImplemented.h"
#include "Page.h"
#include "PluginDatabase.h"
#include "RenderPart.h"
//#include "SystemInfo.h"
#include "WebKitVersion.h"
#include "WebView.h"
#include <wtf/text/StringConcatenate.h>

using namespace WebCore;

namespace WebKit {

FrameLoaderClientSpd::FrameLoaderClientSpd(WebView* view)
    : m_webView(view)
    , m_pluginView(0)
{
    ASSERT(m_webView);
}

FrameLoaderClientSpd::~FrameLoaderClientSpd()
{
}

String FrameLoaderClientSpd::userAgent(const KURL&)
{
    DEFINE_STATIC_LOCAL(String, userAgentString, ());

    if (userAgentString.isNull()) {
        String webKitVersion = String::format("%d.%d", WEBKIT_MAJOR_VERSION, WEBKIT_MINOR_VERSION);
        //userAgentString = makeString("Mozilla/5.0 (", "X11; Linux i686; rv:5.0.1", ") AppleWebKit/", webKitVersion, " (KHTML, like Gecko) Mobile Safari/", webKitVersion);
        userAgentString = makeString("Mozilla/5.0 (X11; Linux i686; rv:11.0) Gecko/20100101 Firefox/11.0");
    }

    return userAgentString;
}

PassRefPtr<DocumentLoader> FrameLoaderClientSpd::createDocumentLoader(const WebCore::ResourceRequest& request, const SubstituteData& substituteData)
{
    return DocumentLoader::create(request, substituteData);
}

void FrameLoaderClientSpd::committedLoad(DocumentLoader* loader, const char* data, int length)
{
    if (m_pluginView) {
        if (!m_hasSentResponseToPlugin) {
            m_pluginView->didReceiveResponse(loader->response());
            m_hasSentResponseToPlugin = true;
        }
        m_pluginView->didReceiveData(data, length);
    } else
        loader->commitData(data, length);
}

bool FrameLoaderClientSpd::shouldUseCredentialStorage(DocumentLoader*, unsigned long)
{
    notImplemented();
    return false;
}

void FrameLoaderClientSpd::dispatchDidReceiveAuthenticationChallenge(DocumentLoader*, unsigned long, const AuthenticationChallenge&)
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidCancelAuthenticationChallenge(DocumentLoader*, unsigned long, const AuthenticationChallenge&)
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchWillSendRequest(DocumentLoader*, unsigned long, WebCore::ResourceRequest&, const WebCore::ResourceResponse&)
{
    notImplemented();
}

void FrameLoaderClientSpd::assignIdentifierToInitialRequest(unsigned long, DocumentLoader*, const WebCore::ResourceRequest&)
{
    notImplemented();
}

void FrameLoaderClientSpd::postProgressStartedNotification()
{
    notImplemented();
}

void FrameLoaderClientSpd::postProgressEstimateChangedNotification()
{
    notImplemented();
}

void FrameLoaderClientSpd::postProgressFinishedNotification()
{
    notImplemented();
}

void FrameLoaderClientSpd::frameLoaderDestroyed()
{
    m_webView = 0;
    m_frame = 0;
    delete this;
}

void FrameLoaderClientSpd::dispatchDidReceiveResponse(DocumentLoader*, unsigned long, const ResourceResponse& response)
{
    m_response = response;
}

void FrameLoaderClientSpd::dispatchDecidePolicyForResponse(FramePolicyFunction policyFunction, const WebCore::ResourceResponse& response, const WebCore::ResourceRequest&)
{
    //return;
    if (canShowMIMEType(response.mimeType()))
        (m_frame->loader()->policyChecker()->*policyFunction)(PolicyUse);
    else
        (m_frame->loader()->policyChecker()->*policyFunction)(PolicyDownload);
}

void FrameLoaderClientSpd::dispatchDecidePolicyForNewWindowAction(FramePolicyFunction policyFunction, const NavigationAction&, const WebCore::ResourceRequest&, PassRefPtr<FormState>, const String&)
{
    (m_frame->loader()->policyChecker()->*policyFunction)(PolicyUse);
}

void FrameLoaderClientSpd::dispatchDecidePolicyForNavigationAction(FramePolicyFunction policyFunction, const NavigationAction&, const WebCore::ResourceRequest&, PassRefPtr<FormState>)
{
    (m_frame->loader()->policyChecker()->*policyFunction)(PolicyUse);
}

void FrameLoaderClientSpd::dispatchWillSubmitForm(FramePolicyFunction policyFunction, PassRefPtr<FormState>)
{
    (m_frame->loader()->policyChecker()->*policyFunction)(PolicyUse);
}

PassRefPtr<Widget> FrameLoaderClientSpd::createPlugin(const IntSize&, HTMLPlugInElement*, const KURL&, const Vector<String>&, const Vector<String>&, const String&, bool)
{
    return 0;
}

PassRefPtr<Frame> FrameLoaderClientSpd::createFrame(const KURL& url, const String& name, HTMLFrameOwnerElement* ownerElement,
                                                 const String& referrer, bool allowsScrolling, int marginWidth, int marginHeight)
{
    return m_webView->createFrame(url, name, ownerElement, referrer, allowsScrolling, marginWidth, marginHeight);
}

void FrameLoaderClientSpd::didTransferChildFrameToNewDocument(Page*)
{
}

void FrameLoaderClientSpd::transferLoadingResourceFromPage(ResourceLoader*, const WebCore::ResourceRequest&, Page*)
{
}

void FrameLoaderClientSpd::redirectDataToPlugin(Widget* pluginWidget)
{
    ASSERT(!m_pluginView);
    m_pluginView = static_cast<PluginView*>(pluginWidget);
    m_hasSentResponseToPlugin = false;
}

PassRefPtr<Widget> FrameLoaderClientSpd::createJavaAppletWidget(const IntSize&, HTMLAppletElement*, const KURL&, const Vector<String>&, const Vector<String>&)
{
    notImplemented();
    return 0;
}

ObjectContentType FrameLoaderClientSpd::objectContentType(const KURL& url, const String& mimeType, bool shouldPreferPlugInsForImages)
{
    return FrameLoader::defaultObjectContentType(url, mimeType, shouldPreferPlugInsForImages);
}

String FrameLoaderClientSpd::overrideMediaType() const
{
    notImplemented();
    return String();
}

void FrameLoaderClientSpd::dispatchDidClearWindowObjectInWorld(DOMWrapperWorld*)
{
    notImplemented();
}

void FrameLoaderClientSpd::documentElementAvailable()
{
    notImplemented();
}

void FrameLoaderClientSpd::didPerformFirstNavigation() const
{
    notImplemented();
}

void FrameLoaderClientSpd::registerForIconNotification(bool)
{
    notImplemented();
}

void FrameLoaderClientSpd::setMainFrameDocumentReady(bool)
{
    notImplemented();
}

bool FrameLoaderClientSpd::hasWebView() const
{
    return true;
}

void FrameLoaderClientSpd::dispatchDidFinishLoad()
{
    notImplemented();
}

void FrameLoaderClientSpd::frameLoadCompleted()
{
    notImplemented();
}

void FrameLoaderClientSpd::saveViewStateToItem(HistoryItem*)
{
    notImplemented();
}

void FrameLoaderClientSpd::restoreViewState()
{
    notImplemented();
}

bool FrameLoaderClientSpd::shouldGoToHistoryItem(HistoryItem* item) const
{
    return item;
}

bool FrameLoaderClientSpd::shouldStopLoadingForHistoryItem(HistoryItem* item) const
{
    return true;
}

void FrameLoaderClientSpd::didDisplayInsecureContent()
{
    notImplemented();
}

void FrameLoaderClientSpd::didRunInsecureContent(SecurityOrigin*, const KURL&)
{
    notImplemented();
}

void FrameLoaderClientSpd::didDetectXSS(const KURL&, bool)
{
    notImplemented();
}

void FrameLoaderClientSpd::makeRepresentation(DocumentLoader*)
{
    notImplemented();
}

void FrameLoaderClientSpd::forceLayout()
{
    notImplemented();
}

void FrameLoaderClientSpd::forceLayoutForNonHTML()
{
    notImplemented();
}

void FrameLoaderClientSpd::setCopiesOnScroll()
{
    notImplemented();
}

void FrameLoaderClientSpd::detachedFromParent2()
{
    notImplemented();
}

void FrameLoaderClientSpd::detachedFromParent3()
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
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidPushStateWithinPage()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidReplaceStateWithinPage()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidPopStateWithinPage()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchWillClose()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidReceiveIcon()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidStartProvisionalLoad()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidReceiveTitle(const StringWithDirection&)
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidChangeIcons(WebCore::IconType)
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidCommitLoad()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidFinishDocumentLoad()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidFirstLayout()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidFirstVisuallyNonEmptyLayout()
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchShow()
{
    notImplemented();
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
    notImplemented();
}

void FrameLoaderClientSpd::willChangeTitle(DocumentLoader*)
{
    notImplemented();
}

void FrameLoaderClientSpd::didChangeTitle(DocumentLoader* documentLoader)
{
    setTitle(documentLoader->title(), documentLoader->url());
}

bool FrameLoaderClientSpd::canHandleRequest(const WebCore::ResourceRequest&) const
{
    notImplemented();
    return true;
}

bool FrameLoaderClientSpd::canShowMIMEType(const String& type) const
{

    return (MIMETypeRegistry::isSupportedImageMIMEType(type)
            || MIMETypeRegistry::isSupportedNonImageMIMEType(type)
            || MIMETypeRegistry::isSupportedMediaMIMEType(type));
    //        || PluginDatabase::installedPlugins()->isMIMETypeRegistered(type));

}

bool FrameLoaderClientSpd::canShowMIMETypeAsHTML(const String&) const
{
    notImplemented();
    return false;
}

bool FrameLoaderClientSpd::representationExistsForURLScheme(const String&) const
{
    notImplemented();
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
        documentLoader->writer()->setEncoding(m_response.textEncodingName(), false);
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

void FrameLoaderClientSpd::setTitle(const StringWithDirection&, const KURL&)
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidReceiveContentLength(DocumentLoader*, unsigned long, int)
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidFinishLoading(DocumentLoader*, unsigned long)
{
    notImplemented();
}

void FrameLoaderClientSpd::dispatchDidFailLoading(DocumentLoader*, unsigned long, const ResourceError&)
{
    notImplemented();
}

bool FrameLoaderClientSpd::dispatchDidLoadResourceFromMemoryCache(DocumentLoader*, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&, int)
{
    notImplemented();
    return false;
}

void FrameLoaderClientSpd::dispatchDidFailProvisionalLoad(const ResourceError& error)
{
    dispatchDidFailLoad(error);
}

void FrameLoaderClientSpd::dispatchDidFailLoad(const ResourceError&)
{
    notImplemented();
}

void FrameLoaderClientSpd::download(ResourceHandle*, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&)
{
    notImplemented();
}

ResourceError FrameLoaderClientSpd::cancelledError(const WebCore::ResourceRequest& request)
{
    ResourceError error("Error", -999, request.url().string(),
                        "Request cancelled");
    error.setIsCancellation(true);
    return error;
}

ResourceError FrameLoaderClientSpd::blockedError(const WebCore::ResourceRequest&)
{
    return ResourceError();
}

ResourceError FrameLoaderClientSpd::cannotShowURLError(const WebCore::ResourceRequest&)
{
    return ResourceError();
}

ResourceError FrameLoaderClientSpd::interruptedForPolicyChangeError(const WebCore::ResourceRequest&)
{
    return ResourceError();
}

ResourceError FrameLoaderClientSpd::cannotShowMIMETypeError(const WebCore::ResourceResponse&)
{
    return ResourceError();
}

ResourceError FrameLoaderClientSpd::fileDoesNotExistError(const WebCore::ResourceResponse&)
{
    return ResourceError();
}

ResourceError FrameLoaderClientSpd::pluginWillHandleLoadError(const WebCore::ResourceResponse&)
{
    return ResourceError();
}

bool FrameLoaderClientSpd::shouldFallBack(const ResourceError& error)
{
    return !(error.isCancellation());
}

bool FrameLoaderClientSpd::canCachePage() const
{
    return true;
}

Frame* FrameLoaderClientSpd::dispatchCreatePage(const NavigationAction&)
{
    notImplemented();
    return 0;
}

void FrameLoaderClientSpd::dispatchUnableToImplementPolicy(const ResourceError&)
{
    notImplemented();
}

void FrameLoaderClientSpd::setMainDocumentError(DocumentLoader*, const ResourceError& error)
{
    if (!m_pluginView)
        return;

    m_pluginView->didFail(error);
    m_pluginView = 0;
    m_hasSentResponseToPlugin = false;
}

void FrameLoaderClientSpd::startDownload(const WebCore::ResourceRequest&, const String& /* suggestedName */)
{
    notImplemented();
}

void FrameLoaderClientSpd::updateGlobalHistory()
{
    notImplemented();
}

void FrameLoaderClientSpd::updateGlobalHistoryRedirectLinks()
{
    notImplemented();
}

void FrameLoaderClientSpd::savePlatformDataToCachedFrame(CachedFrame*)
{
    notImplemented();
}

void FrameLoaderClientSpd::transitionToCommittedFromCachedFrame(CachedFrame*)
{
    notImplemented();
}


void FrameLoaderClientSpd::transitionToCommittedForNewPage()
{
    Page* page = m_frame->page();
    ASSERT(page);

    bool isMainFrame = m_frame == page->mainFrame();

    m_frame->setView(0);

    RefPtr<FrameView> frameView;
    if (isMainFrame) {
        IntSize initialSize;
        frameView = FrameView::create(m_frame, initialSize);
    } else
        frameView = FrameView::create(m_frame);

        m_frame->setView(frameView);

    if (m_frame->ownerRenderer())
        m_frame->ownerRenderer()->setWidget(frameView);

}

/*
void FrameLoaderClientSpd::transitionToCommittedForNewPage()
{
    Page* page = m_frame->page();
    ASSERT(page);

    bool isMainFrame = m_frame == page->mainFrame();

    m_frame->setView(0);

    RefPtr<FrameView> frameView;
    if (isMainFrame) {
        RECT rect;
        m_webView->frameRect(&rect);
        frameView = FrameView::create(m_frame, IntRect(rect).size());
    } else
        frameView = FrameView::create(m_frame);

    m_frame->setView(frameView);

    if (m_frame->ownerRenderer())
        m_frame->ownerRenderer()->setWidget(frameView);

}
*/
void FrameLoaderClientSpd::didSaveToPageCache()
{
}

void FrameLoaderClientSpd::didRestoreFromPageCache()
{
}

void FrameLoaderClientSpd::dispatchDidBecomeFrameset(bool)
{
}

PassRefPtr<WebCore::FrameNetworkingContext> FrameLoaderClientSpd::createNetworkingContext()
{
    return FrameNetworkingContextSpd::create(m_frame, userAgent(KURL()));
}

} // namespace WebKit
