#include "config.h"
#include "SharedTimer.h"
#include "SEvent.h"
#include <wtf/Assertions.h>
#include <wtf/CurrentTime.h>
#include <wtf/MainThread.h>

namespace WebCore {


static void (*_timerFunction)();

static bool timerEvent(void*)
{
    if (_timerFunction)
        _timerFunction();

    return true;
}

void setSharedTimerFiredFunction(void (*func)())
{
    _timerFunction = func;
    SEvent_handler_add(SE_TIMER,timerEvent);
}


void stopSharedTimer()
{
}

void addNewTimer(double interval)
{
    stopSharedTimer();
    SEvent_add(SE_TIMER, &interval);
}

void setSharedTimerFireInterval(double interval)
{
    addNewTimer(interval);
}

}

