#include "config.h"
#include "SystemTime.h"

#include "NotImplemented.h"
#include <limits>

namespace WebCore {

float userIdleTime()
{
    notImplemented();
    // Return an arbitrarily high userIdleTime so that releasing pages from the page cache isn't postponed.
    return std::numeric_limits<float>::max();
}

} // namespace WebCore
