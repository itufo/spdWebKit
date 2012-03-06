#include "config.h"

#include "Icon.h"

#include "GraphicsContext.h"
#include "MIMETypeRegistry.h"
#include "NotImplemented.h"
#include "PassRefPtr.h"
#include "PlatformString.h"

namespace WebCore {

Icon::Icon()
    : m_icon(0)
{
    notImplemented();
}

Icon::~Icon()
{
}

PassRefPtr<Icon> Icon::createIconForFiles(const Vector<String>& filenames)
{
    notImplemented();
    return 0;
}

void Icon::paint(GraphicsContext* context, const IntRect& rect)
{
    notImplemented();
}

}
