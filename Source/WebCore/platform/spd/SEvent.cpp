/*
 * SEvent.cpp
 *
 *  Created on: 2012-3-28
 *      Author: jack
 */
#include "SEvent.h"
#include <queue>
#include <map>
#include <iostream>
#include <functional>
#include <ctime>
#include <cstdlib>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct _timerevent
{

}timerevent;

static bool quit = true;
static SEventType nextType = 10;
priority_queue<double> pq1; //默认最大堆
priority_queue<double, vector<double>, greater<double> > timer; //最小堆
queue<pair<SEventType,void*> > event;
map<SEventType, SEvent_cb> handler;
static struct timeval init_tv,end_tv;

bool SEvent_init()
{
    gettimeofday(&init_tv, NULL);
    return true;
}

SEventType SEvent_type_new()
{
    return nextType++;
}

bool SEvent_handler_add(SEventType type, SEvent_cb cb)
{
    handler[type] = cb;
    return true;
}

bool SEvent_add(SEventType type, void* data)
{
    switch (type)
    {
    case SE_TIMER:
    {
        double interval = *((double*)data);
        struct timeval curtime;
        gettimeofday(&curtime,NULL);
        double firetime = (curtime.tv_sec-init_tv.tv_sec)*1000.0
                +(curtime.tv_usec-init_tv.tv_usec)/1000.0+interval;
        timer.push(firetime);
        break;
    }
    default:
        event.push(pair<SEventType,void*>(type,data));
        break;
    }
    return true;
}

int SEvent_loop_begin()
{
    quit = false;
    while(!quit)
    {
        if(!event.empty())
        {
            pair<SEventType,void*> ev = event.front();
            event.pop();

            handler[ev.first](ev.second);
        }
        else if(!timer.empty())
        {
           double t = timer.top();
           //printf("%f\n",t);
           timer.pop();
           handler[SE_TIMER](NULL);
        }
        else{
            usleep(1000);
        }
    }
    return 0;
}

bool SEvent_stop(SEventType type)
{
    if(type == SE_TIMER)
    {
        while(!timer.empty())
            timer.pop();
    }
    return true;
}

int SEvent_loop_quit()
{
    quit = true;
    return 0;
}

int SEvent_shutdown()
{
    while(!event.empty())
        event.pop();
    while(!timer.empty())
        timer.pop();
    return 0;
}

/*
bool fired(void *data)
{
    printf("fired\n");
    sleep(1);
    double interval = 0.1;
    SEvent_add(SE_TIMER,&interval);
    return true;
}

bool OnLoad(void* data)
{
    char* url = (char*)data;
    printf("load %s\n",url);
}

int main()
{
    SEvent_init();
    SEventType SE_LOAD = SEvent_type_new();
    SEvent_handler_add(SE_TIMER,fired);
    SEvent_handler_add(SE_LOAD,OnLoad);
    double interval = 0.1;
    SEvent_add(SE_TIMER,&interval);
    char* url = "http://";
    SEvent_add(SE_LOAD,url);
    url = "http://wwww";
    SEvent_add(SE_LOAD,url);
    SEvent_loop_begin();
    return 0;
}
*/
