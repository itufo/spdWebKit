#include "config.h"
#include "EventLoop.h"

#include <Ecore.h>

namespace WebCore {

void EventLoop::cycle()
{
    printf("EventLoop::cycle()\n");
    ecore_main_loop_iterate();
}

} // namespace WebCore
