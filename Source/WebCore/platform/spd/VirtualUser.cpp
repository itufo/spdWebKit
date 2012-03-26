/*
 * VirtualUser.cpp
 *
 *  Created on: 2012-3-21
 *      Author: jack
 */
#include "config.h"
#include "Threading.h"
#include "markup.h"
#include "SharedTimer.h"
#include "VirtualUser.h"
#include <event2/event.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

namespace WebCore
{

VirtualUser* pUser = NULL;
//pthread_mutex_t user_option_mutex = PTHREAD_MUTEX_INITIALIZER;

void server_loop(void* data)
{
    VirtualUser* user = (VirtualUser*) data;
    while (1)
    {
        //pthread_mutex_lock(user_option_mutex);
        printf("Option>\n");
        char op[32] = {0};
        gets(op);
        user->setOption(op);
        printf("%s\n", op);
        //pthread_mutex_unlock(user_option_mutex);
        //user->timer().startOneShot(0);
    }
}

VirtualUser::VirtualUser(Frame* frame) :
        m_frame(frame), m_userTimer(this, &VirtualUser::userTimerFired)
{
    createThread(server_loop, this, "virtualuser");
    pUser = this;
}

void VirtualUser::init()
{
}

void VirtualUser::clearAction()
{
    m_action = "";
}

void VirtualUser::setOption(char* op)
{
    if(op == NULL)
        return;
    if(strcmp(op,"OP_DUMP")==0)
    {
        m_option = OP_DUMP;
    }
    else if (strncmp(op,"http://",strlen("http://"))==0)
    {
        m_option = OP_LOAD;
        m_action = op;
    }
}

WebCore::Timer<VirtualUser>& VirtualUser::timer()
{
    return m_userTimer;
}

void VirtualUser::load(String& url)
{
    printf("VirtualUser::load()\n");

}

void VirtualUser::startTimer()
{
    //m_userTimer.startRepeating(3);
    //m_userTimer.startOneShot(0);
}

String VirtualUser::getHTML()
{
    return createMarkup(m_frame->document());
}

String VirtualUser::getAction()
{
    return m_action;
}

int VirtualUser::exec()
{
    switch (m_option)
    {
    case OP_NULL:
        break;
    case OP_LOAD:
        m_option = OP_NULL;
        m_frame->loader()->stopAllLoaders();
        extern struct event_base* base;
        if(base)
        {
            //struct event_base* old_base = base;
            base = NULL; 
            //event_base_free(old_base);
            stopSharedTimer();
        }
        return -1;
    case OP_DUMP:
        m_option = OP_NULL;
        printf("%s\n",getHTML().utf8(false).data());
        break;
    default:
        break;
    }
    return 0;
}

void VirtualUser::userTimerFired(Timer<VirtualUser>*)
{
    printf("VirtualUser::userTimerFired()\n");
    m_userTimer.startOneShot(10);
    /*    if(url == NULL)
     return;
     printf("load %s\n",url);
     m_view->stop();
     m_view->innerText().show();
     String strUrl(url);
     m_view->load(strUrl);
     */
    //setNextFireTime(3000);
}

} // namespace WebCore
