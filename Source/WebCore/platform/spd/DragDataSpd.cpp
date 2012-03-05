#include "config.h"
#include "DragData.h"

#include "Document.h"
#include "DocumentFragment.h"

namespace WebCore {

bool DragData::canSmartReplace() const
{
    return false;
}

bool DragData::containsColor() const
{
    return false;
}

bool DragData::containsFiles() const
{
    return false;
}

unsigned DragData::numberOfFiles() const
{
    return 0;
}

void DragData::asFilenames(Vector<String>& result) const
{
}

bool DragData::containsPlainText() const
{
    return false;
}

String DragData::asPlainText(Frame*) const
{
    return String();
}

Color DragData::asColor() const
{
    return Color();
}

bool DragData::containsCompatibleContent() const
{
    return false;
}

bool DragData::containsURL(Frame*, FilenameConversionPolicy filenamePolicy) const
{
    return false;
}

String DragData::asURL(Frame*, FilenameConversionPolicy filenamePolicy, String* title) const
{
    return String();
}

PassRefPtr<DocumentFragment> DragData::asFragment(Frame*, PassRefPtr<Range>, bool, bool&) const
{
    return 0;
}

}
