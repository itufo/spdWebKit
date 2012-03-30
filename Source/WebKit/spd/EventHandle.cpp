#include "config.h"
#include "spdWebKit.h"
#include "EventHandle.h"
#include "WebView.h"
#include "wtf/text/WTFString.h"
#include "wtf/text/CString.h"
#include "SEvent.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

namespace WTF{
   class String;
   class CString;
}

using namespace WebCore;

extern WebView* g_pView;
int EventHandle::ET_START = SEvent_type_new();
int EventHandle::ET_ALIVE = SEvent_type_new();
int EventHandle::ET_LOAD = SEvent_type_new();
int EventHandle::ET_DUMPHTML = SEvent_type_new();
int EventHandle::ET_QUIT = SEvent_type_new();
int EventHandle::ET_GETELEMENT = SEvent_type_new();
int EventHandle::ET_SETVALUE = SEvent_type_new();
int EventHandle::ET_CLICK = SEvent_type_new();

bool OnStart(void* param);
bool OnAlive(void* param);
bool OnLoad(void* param);
bool OnDumpHTML(void* param);
bool OnQuit(void* param);
bool OnGetElementById(void* param);
bool OnSetElementValue(void* param);
bool OnClick(void* param);

SPD_GLOBAL int EventHandle::init()
{
    if (!SEvent_init())
    {
        printf("ERROR: Cannot init SEvent!\n");
        exit(1);
    }

    return 0;
}

SPD_GLOBAL EventHandle::EventHandle()
    :m_buf(0)
{
    SEvent_handler_add(SE_TIMER, OnAlive);
    SEvent_handler_add(ET_START, OnStart);
    SEvent_handler_add(ET_ALIVE, OnAlive);
    SEvent_handler_add(ET_LOAD, OnLoad);
    SEvent_handler_add(ET_DUMPHTML,OnDumpHTML);
    SEvent_handler_add(ET_QUIT,OnQuit);
    SEvent_handler_add(ET_GETELEMENT, OnGetElementById);
    SEvent_handler_add(ET_SETVALUE,OnSetElementValue);
    SEvent_handler_add(ET_CLICK,OnClick);

}

SPD_GLOBAL int EventHandle::start()
{
    SEvent_add(ET_START, NULL);
    return 0;
}

SPD_GLOBAL int EventHandle::load(char* url)
//int EventHandle::load()
{
    printf("tid:%u handler_add(%d)\n",(unsigned int)pthread_self(),ET_LOAD);
    memset(m_url,0,512);
    sprintf(m_url,"%s",url);
    SEvent_add(ET_LOAD, m_url);
    return 0;
}

SPD_GLOBAL char* EventHandle::dumpHTML()
{
    printf("tid:%u handler_add(%d)\n",(unsigned int)pthread_self(),ET_DUMPHTML);
    if(m_buf)
    {
        free(m_buf);
        m_buf = NULL;
    }
    SEvent_add(ET_DUMPHTML, &m_buf);
    sleep(1);
    return m_buf;
}

SPD_GLOBAL int EventHandle::quit()
{
    SEvent_add(EventHandle::ET_QUIT, NULL);
    return 0;
}

SPD_GLOBAL int EventHandle::getElementById(char* id)
{
    SEvent_add(EventHandle::ET_GETELEMENT, id);
    return 0;
}

SPD_GLOBAL int EventHandle::setElementValue(char* value)
{
    SEvent_add(EventHandle::ET_SETVALUE, value);
    return 0;
}

SPD_GLOBAL int EventHandle::click()
{
    SEvent_add(EventHandle::ET_CLICK, NULL);
    return 0;
}

void *cmd(void *arg)
{
   EventHandle* pHandle = (EventHandle*)arg;
   while(1)
   {
       char cmd[512] = {0};
       printf("start/load/get/set/click/dump/quit?\n");
       gets(cmd);
       if(strcmp(cmd,"start")==0)
       {
           pHandle->start();
       }
       else if(strcmp(cmd,"load")==0)
       {
           printf("url:");
           memset(cmd,0,512);
           gets(cmd);
           pHandle->load(cmd);
       }
       else if(strcmp(cmd,"get")==0)
       {
           printf("id:");
           memset(cmd,0,512);
           gets(cmd);
           pHandle->getElementById(cmd);
       }
       else if(strcmp(cmd,"set")==0)
       {
           printf("value:");
           memset(cmd,0,512);
           gets(cmd);
           pHandle->setElementValue(cmd);
       }
       else if(strcmp(cmd,"click")==0)
       {
           pHandle->click();
       }
       else if(strcmp(cmd,"dump")==0)
       {
           pHandle->dumpHTML();
           sleep(1);
           printf("%s\n",pHandle->m_buf);
       }
       else if(strcmp(cmd,"quit")==0)
       {
           pHandle->quit();
       }
       else{
           continue;
       }

   }
   return NULL;
}

bool OnAlive(void* param)
{
    printf("alive()\n");
    sleep(1);
    //SEvent_add(EventHandle::ET_ALIVE, NULL);
    double interval = 100;
    SEvent_add(SE_TIMER, &interval);
    return true;
}

SPD_GLOBAL void EventHandle::event_loop(client_cb func)
{
    if(func == NULL)
        func = cmd;
   
    int err;
    pthread_t ntid;
    err=pthread_create(&ntid, NULL, func, this);

    printf("tid:%u SEvent_loop_begin()\n",(unsigned int)pthread_self());

    SEvent_loop_begin();
    SEvent_shutdown();
}

bool OnStart(void* param)
{
   printf("tid:%u OnStart()\n",(unsigned int)pthread_self());

   WebView::initialize(NULL);
   g_pView = new WebView();
   if(g_pView == NULL)
   {
       printf("new WebView() fail\n");
   }

   return true;
}

bool OnLoad(void* param)
{
    printf("tid:%u OnLoad()\n",(unsigned int)pthread_self());
    char* url = (char*)param;
    printf("load:%s\n",url);

    g_pView->stop();
    String strUrl = url;
    g_pView->load(strUrl);

    return true;
}

bool OnDumpHTML(void* param)
{
    printf("tid:%u OnDumpLoad()\n",(unsigned int)pthread_self());
    char** buf = (char**)param;
    CString html = g_pView->innerText().utf8(false);
    int len = html.length();
    *buf = (char*)malloc(len+1);
    memset(*buf,0,len+1);
    strncpy(*buf,html.data(),len);
    //printf("%s\n\n\n\n",g_pView->innerText().utf8(false).data());
    return true;
}

bool OnQuit(void* param)
{
    exit(0);
}


bool OnGetElementById(void* param)
{
    char* id = (char*)param;
    g_pView->setCurrentElementById(id);
    return true;
}

bool OnSetElementValue(void* param)
{
    char* value = (char*)param;
    g_pView->setCurrentElementValue(value);
    return true;
}

bool OnClick(void* param)
{
    return true;
}
