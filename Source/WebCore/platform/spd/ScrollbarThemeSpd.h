#ifndef ScrollbarThemeSpd_h
#define ScrollbarThemeSpd_h

#include "ScrollbarTheme.h"

namespace WebCore {

class ScrollbarThemeSpd : public ScrollbarTheme {
public:
    virtual ~ScrollbarThemeSpd();

    virtual int scrollbarThickness(ScrollbarControlSize = RegularScrollbar);

    virtual void registerScrollbar(Scrollbar* scrollbar);
    virtual void unregisterScrollbar(Scrollbar* scrollbar);
};

}
#endif // ScrollbarThemeSpd_h

