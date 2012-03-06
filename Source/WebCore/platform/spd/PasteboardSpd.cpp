#include "config.h"
#include "Pasteboard.h"

#include "DocumentFragment.h"
#include "Frame.h"
#include "Image.h"
#include "KURL.h"
#include "NotImplemented.h"
#include "PlatformString.h"
#include "RenderImage.h"
#include "markup.h"
#include <wtf/text/CString.h>

namespace WebCore {

Pasteboard* Pasteboard::generalPasteboard()
{
    static Pasteboard* pasteboard = new Pasteboard();
    return pasteboard;
}

Pasteboard::Pasteboard()
{
    notImplemented();
}

void Pasteboard::writePlainText(const String&)
{
    notImplemented();
}

void Pasteboard::writeSelection(Range* selectedRange, bool canSmartCopyOrDelete, Frame* frame)
{
    notImplemented();
}

void Pasteboard::writeURL(const KURL&, const String&, Frame*)
{
    notImplemented();
}

void Pasteboard::writeImage(Node* node, const KURL&, const String&)
{
    notImplemented();
}

void Pasteboard::writeClipboard(Clipboard*)
{
    notImplemented();
}

void Pasteboard::clear()
{
    notImplemented();
}

bool Pasteboard::canSmartReplace()
{
    notImplemented();
    return false;
}

PassRefPtr<DocumentFragment> Pasteboard::documentFragment(Frame* frame, PassRefPtr<Range> context,
                                                          bool allowPlainText, bool& chosePlainText)
{
    notImplemented();
    return 0;
}

String Pasteboard::plainText(Frame*)
{
    notImplemented();
    return String();
}

}
