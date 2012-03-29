#include "config.h"
#include "InspectorClientSpd.h"

#include "NotImplemented.h"

using namespace WebCore;

namespace WebKit {

InspectorClientSpd::InspectorClientSpd(WebView* webView)
    : m_inspectedWebView(webView)
{
}

InspectorClientSpd::~InspectorClientSpd()
{
}

void InspectorClientSpd::inspectorDestroyed()
{
    delete this;
}

void InspectorClientSpd::openInspectorFrontend(InspectorController* controller)
{
    notImplemented();
}

void InspectorClientSpd::closeInspectorFrontend()
{
    notImplemented();
}

void InspectorClientSpd::bringFrontendToFront()
{
    notImplemented();
}

void InspectorClientSpd::releaseFrontendPage()
{
    notImplemented();
}

void InspectorClientSpd::highlight()
{
    notImplemented();
}

void InspectorClientSpd::hideHighlight()
{
    notImplemented();
}

void InspectorClientSpd::populateSetting(const String& key, String* value)
{
    notImplemented();
}

void InspectorClientSpd::storeSetting(const String& key, const String& value)
{
    notImplemented();
}

bool InspectorClientSpd::sendMessageToFrontend(const String& message)
{
    notImplemented();
    return false;
}

} // namespace WebKit
