#include "config.h"

#include "AXObjectCache.h"
#include "CookieStorage.h"
#include "Editor.h"
#include "FTPDirectoryDocument.h"
#include "FrameView.h"
#include "KURL.h"
#include "NotImplemented.h"
#include "PluginView.h"
#include "ScrollbarTheme.h"
#include "SharedBuffer.h"

#include <float.h>

using namespace WebCore;

namespace WebCore {

void getSupportedKeySizes(Vector<String>&)
{
    notImplemented();
}

String signedPublicKeyAndChallengeString(unsigned keySizeIndex, const String &challengeString, const KURL &url)
{
    return String();
}
/*
void setCookieStoragePrivateBrowsingEnabled(bool)
{
    notImplemented();
}

void startObservingCookieChanges()
{
    notImplemented();
}

void stopObservingCookieChanges()
{
    notImplemented();
}
*/
}

