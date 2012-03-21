/*
 * VirtualUser.h
 *
 *  Created on: 2012-3-21
 *      Author: jack
 */

#ifndef VIRTUALUSER_H_
#define VIRTUALUSER_H_

#include "WebView.h"
#include "wtf/text/WTFString.h"
#include "Timer.h"

namespace WTF{
    class String;
}
enum Option {OP_NULL,OP_LOAD,OP_DUMP};

class VirtualUser{
public:
    VirtualUser(WebView* view);

    static void init();
    void load(String& url);
    WebCore::Timer<VirtualUser>& timer();
    void startTimer();
    void userTimerFired( WebCore::Timer<VirtualUser>* );
    String getHTML();
    void exec();
    void setOption(char* op);
private:

    WebCore::Timer<VirtualUser> m_userTimer;
    WebView* m_view;
    Option m_option;
};


#endif /* VIRTUALUSER_H_ */
