#include "config.h"
#include "KURL.h"

namespace WebCore {

String KURL::fileSystemPath() const
{
    if (!isValid() || !protocolIs("file"))
        return String();

    return String(path());
}

} // namespace WebCore
