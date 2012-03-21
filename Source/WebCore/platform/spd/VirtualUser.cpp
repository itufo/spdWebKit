/*
 * VirtualUser.cpp
 *
 *  Created on: 2012-3-21
 *      Author: jack
 */
#include "config.h"
#include "Threading.h"
#include "markup.h"
#include "VirtualUser.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

namespace WebCore
{

VirtualUser* pUser = NULL;

void server_loop(void* data)
{
    VirtualUser* user = (VirtualUser*) data;
    while (1)
    {
        printf("Option>\n");
        char op[32] = {0};
        gets(op);
        user->setOption(op);
        printf("%s\n", op);
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

void VirtualUser::setOption(char* op)
{
    if(op == NULL)
        return;
    if(strcmp(op,"OP_DUMP")==0)
    {
        m_option = OP_DUMP;
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

void VirtualUser::exec()
{
    switch (m_option)
    {
    case OP_NULL:
        return;
    case OP_LOAD:
        return;
    case OP_DUMP:
        m_option = OP_NULL;
        printf("%s\n",getHTML().utf8(false).data());
        return;
    default:
        return;
    }
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
