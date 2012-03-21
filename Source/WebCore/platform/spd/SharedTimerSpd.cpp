#include "config.h"
#include "SharedTimer.h"
#include "Threading.h"
#include "VirtualUser.h"

#include <wtf/Assertions.h>
#include <wtf/CurrentTime.h>
#include <wtf/MainThread.h>

#include <event2/event-config.h>
#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/util.h>

#include <unistd.h>
#include <stdio.h>

namespace WebCore {

struct event timer;
struct event_base* base =  event_base_new();
int event_is_dispatch = 0;
static void (*_timerFunction)();

static void timer_cb(evutil_socket_t fd, short event, void *arg)
{
    //printf("Fired!\n");
    if(_timerFunction)
       _timerFunction();
    //printf("Fired return!\n");
}

void setSharedTimerFiredFunction(void (*func)())
{
    //printf("setSharedTimerFiredFunction\n");
    _timerFunction = func;
    event_assign(&timer,base,-1,0,timer_cb,(void*)&timer);
}


void stopSharedTimer()
{
    //printf("stop timer\n");
    event_del(&timer);
}

void setSharedTimerFireInterval(double interval)
{
    extern VirtualUser* pUser;
    if(pUser)
        pUser->exec();
    //printf("Thread[%d] set timer %f\n",currentThread(),interval);
    if(interval>-0.000001 && interval<0.000001 && _timerFunction)
    {
        _timerFunction();
        return;
    }
  
    struct timeval tv;
    evutil_timerclear(&tv);
    tv.tv_sec = 0;
    tv.tv_usec = interval*1000;
    event_add(&timer,&tv);
 
    if(!event_is_dispatch)
    {
        event_is_dispatch = 1;
    	event_base_dispatch(base);
    }

}

}

