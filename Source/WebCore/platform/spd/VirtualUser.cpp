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
#include <Ecore.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

namespace WebCore
{

VirtualUser* pUser = NULL;
//pthread_mutex_t user_option_mutex = PTHREAD_MUTEX_INITIALIZER;

void server_loop(void* data)
{
    while (1)
    {
        if(pUser == NULL)
        {
            sleep(1);
            continue;
        }
        //pthread_mutex_lock(user_option_mutex);
        printf("Option>\n");
        char op[32] = {0};
        gets(op);
        pUser->setOption(op);
        printf("%s\n", op);
        //pthread_mutex_unlock(user_option_mutex);
        //user->timer().startOneShot(0);
    }
}

VirtualUser::VirtualUser(Frame* frame) :
        m_frame(frame), m_userTimer(this, &VirtualUser::userTimerFired)
{
    pUser = this;
}

void VirtualUser::init()
{
    createThread(server_loop, NULL, "virtualuser");
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

void VirtualUser::setAction(char* action)
{
    m_action = action;
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
        ecore_main_loop_quit();
        m_frame->loader()->stopAllLoaders();
        //m_frame->loader()->changeLocation(m_frame->document()->securityOrigin(), m_frame->document()->completeURL(getAction()), "", false, false);
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
