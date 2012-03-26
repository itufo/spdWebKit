#include "config.h"
#include "spdWebView.h"
#include "spdWebKit.h"
#include "WebView.h"

#include "ChromeClientSpd.h"
#include "ContextMenuClientSpd.h"
#include "DragClientSpd.h"
#include "EditorClientSpd.h"
#include "FocusController.h"
#include "Frame.h"
#include "FrameLoader.h"
#include "FrameLoaderClientSpd.h"
#include "FrameView.h"
#include "GraphicsContext.h"
#include "InitializeThreading.h"
#include "InspectorClientSpd.h"
#include "IntSize.h"
#include "MainThread.h"
#include "NotImplemented.h"
#include "Page.h"
#include "VirtualUser.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace WebCore;

struct _spdWebView{
     WebView* m_view;
     VirtualUser* m_user;
};

SPD_GLOBAL spdWebView* spdWebView_new()
{
    spdWebView* me = (spdWebView*)malloc(sizeof(spdWebView));
    memset(me,0,sizeof(spdWebView));
    
    WebView::initialize(&(me->m_view));
    me->m_view = new WebView(); 
    me->m_user = new VirtualUser(me->m_view->frame());
    return me;
}


SPD_GLOBAL int spdWebView_load(spdWebView* me, const char* url)
{
    String strUrl = url;
    me->m_view->load(strUrl);
    printf("%s\n\n\n\n",me->m_user->getHTML().utf8(false).data());
    while(1)
    {
        if(me->m_user->getAction().length()<1)
        {
            sleep(1);
            continue;
        }
        me->m_user->getAction().show();
        String str = me->m_user->getAction();
        me->m_user->clearAction();
        me->m_view->load(str);
        printf("%s\n\n\n\n",me->m_view->innerText().utf8(false).data());
    }
    return 0;
}

