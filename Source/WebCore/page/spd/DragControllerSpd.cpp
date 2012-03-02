#include "config.h"
#include "DragController.h"

#include "DragData.h"
#include "Frame.h"
#include "FrameView.h"
#include "Page.h"

namespace WebCore {

const int DragController::LinkDragBorderInset = 2;
const int DragController::MaxOriginalImageArea = 1500 * 1500;
const int DragController::DragIconRightInset = 7;
const int DragController::DragIconBottomInset = 3;

const float DragController::DragImageAlpha = 0.75f;

bool DragController::isCopyKeyDown(DragData*)
{
    return false;
}

DragOperation DragController::dragOperation(DragData* dragData)
{
    if (dragData->containsURL(0))
        return DragOperationCopy;

    return DragOperationNone;
}

const IntSize& DragController::maxDragImageSize()
{
    static const IntSize maxDragImageSize(400, 400);

    return maxDragImageSize;
}

void DragController::cleanupAfterSystemDrag()
{}

}
