#ifndef DragClientSpd_h
#define DragClientSpd_h

#include "DragClient.h"

namespace WebKit {

class DragClientSpd : public WebCore::DragClient {
public:
    virtual void willPerformDragDestinationAction(WebCore::DragDestinationAction, WebCore::DragData*);
    virtual void willPerformDragSourceAction(WebCore::DragSourceAction, const WebCore::IntPoint&, WebCore::Clipboard*);
    virtual WebCore::DragDestinationAction actionMaskForDrag(WebCore::DragData*);

    virtual WebCore::DragSourceAction dragSourceActionMaskForPoint(const WebCore::IntPoint&);

    virtual void startDrag(WebCore::DragImageRef, const WebCore::IntPoint&, const WebCore::IntPoint&, WebCore::Clipboard*, WebCore::Frame*, bool = false);

    virtual void dragControllerDestroyed();
};

} // namespace WebKit

#endif // DragClientSpd_h
