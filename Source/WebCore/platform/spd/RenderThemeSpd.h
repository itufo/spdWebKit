#ifndef RenderThemeSpd_h
#define RenderThemeSpd_h

#include "RenderTheme.h"
#include "RenderObject.h"
#include "ScrollTypes.h"
#include <wtf/PassRefPtr.h>
#include <wtf/RefCounted.h>

namespace WebCore {


class RenderThemeSpd : public RenderTheme {
public:
    RenderThemeSpd();

    ~RenderThemeSpd() { }


    // System fonts and colors for CSS.
    void systemFont(int cssValueId, FontDescription&) const;

};

} // namespace WebCore

#endif // RenderThemeSpd_h
