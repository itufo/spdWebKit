#include "config.h"
#include "Widget.h"

#include "ChromeClient.h"
#include "Cursor.h"
#include "Frame.h"
#include "FrameView.h"
#include "GraphicsContext.h"
#include "IntRect.h"
#include "NotImplemented.h"
#include "Page.h"

#include <wtf/HashMap.h>
#include <wtf/text/CString.h>

namespace WebCore {

Widget::Widget(PlatformWidget widget)
{
}

Widget::~Widget()
{
}

IntRect Widget::frameRect() const
{
}

void Widget::setFrameRect(const IntRect& rect)
{
}

void Widget::setFocus(bool focused)
{
}

void Widget::setCursor(const Cursor& cursor)
{
}

void Widget::show()
{
}

void Widget::hide()
{
}

void Widget::paint(GraphicsContext* context, const IntRect&)
{
    notImplemented();
}

void Widget::setIsSelected(bool)
{
    notImplemented();
}

}
