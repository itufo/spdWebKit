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
    String str(url);
    me->m_view->load(str);
    String text = me->m_view->innerText();
    text.show();
    return 0;
}
