#include "config.h"
#include "ScrollbarThemeSpd.h"

#include "NotImplemented.h"
#include <stdio.h>

namespace WebCore {

ScrollbarTheme* ScrollbarTheme::nativeTheme()
{
    static ScrollbarThemeSpd theme;
    return &theme;
}

ScrollbarThemeSpd::~ScrollbarThemeSpd()
{
}

int ScrollbarThemeSpd::scrollbarThickness(ScrollbarControlSize controlSize)
{
    return 0; // we paint on top
}

void ScrollbarThemeSpd::registerScrollbar(Scrollbar* scrollbar)
{
}

void ScrollbarThemeSpd::unregisterScrollbar(Scrollbar* scrollbar)
{
}

}

