#include "config.h"
#include "PlatformScreen.h"

#include "NotImplemented.h"
#include "PlatformString.h"
#include "Widget.h"

#include <wtf/text/CString.h>

namespace WebCore {
 
int screenHorizontalDPI(Widget* widget)
{
    notImplemented();
    return 0;
}

int screenVerticalDPI(Widget* widget)
{
    notImplemented();
    return 0;
}

int screenDepth(Widget* widget)
{
    notImplemented();
    return 8;
}

int screenDepthPerComponent(Widget*)
{
    notImplemented();
    return 8;
}

bool screenIsMonochrome(Widget*)
{
    notImplemented();
    return false;
}

FloatRect screenRect(Widget* widget)
{
}

FloatRect screenAvailableRect(Widget* widget)
{
    notImplemented();
    return screenRect(widget);
}

}
