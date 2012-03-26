/*
 * VirtualUser.h
 *
 *  Created on: 2012-3-21
 *      Author: jack
 */

#ifndef VIRTUALUSER_H_
#define VIRTUALUSER_H_

#include "Frame.h"
#include "wtf/text/WTFString.h"
#include "Timer.h"

namespace WTF{
    class String;
}
namespace WebCore{

enum Option {OP_NULL,OP_LOAD,OP_DUMP};

class VirtualUser{
public:
    VirtualUser(Frame* frame);

    static void init();
    void load(String& url);
    WebCore::Timer<VirtualUser>& timer();
    void startTimer();
    void userTimerFired( WebCore::Timer<VirtualUser>* );
    String getHTML();
    int exec();
    void setOption(char* op);
    void clearAction();
    String getAction();
private:

    WebCore::Timer<VirtualUser> m_userTimer;
    Frame* m_frame;
    Option m_option;
    String m_action;
};

} // namespace WebCore
#endif /* VIRTUALUSER_H_ */
