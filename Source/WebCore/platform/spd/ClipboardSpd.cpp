#include "config.h"

#include "Clipboard.h"
#include "DOMStringList.h"
#include "DataTransferItemList.h"
#include "Editor.h"
#include "FileList.h"
#include "NotImplemented.h"
#include <wtf/text/StringHash.h>

namespace WebCore {

PassRefPtr<Clipboard> Clipboard::create(ClipboardAccessPolicy, DragData*, Frame*)
{
    return 0;
}

}
