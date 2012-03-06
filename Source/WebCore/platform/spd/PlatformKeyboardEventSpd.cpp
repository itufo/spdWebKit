#include "config.h"
#include "PlatformKeyboardEvent.h"

#include "NotImplemented.h"
#include "TextEncoding.h"
#include <stdio.h>
#include <wtf/CurrentTime.h>

namespace WebCore {

void PlatformKeyboardEvent::disambiguateKeyDownEvent(Type type, bool)
{
}

bool PlatformKeyboardEvent::currentCapsLockState()
{
    notImplemented();
    return false;
}

void PlatformKeyboardEvent::getCurrentModifierState(bool& shiftKey, bool& ctrlKey, bool& altKey, bool& metaKey)
{
}

}
