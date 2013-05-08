/*
 * EventHandle.h
 *
 *  Created on: 2012-3-27
 *      Author: jack
 */

#ifndef EVENTHANDLE_H_
#define EVENTHANDLE_H_

typedef void* (*client_cb)(void *data);

class EventHandle {

public:
    static int init();

    EventHandle();
    
    int start();

    //int load();
    int load(char* url);

    char* dumpHTML();

    int quit();

    int getElementById(char* id);

    int setElementValue(char* value);

    int click();

    int type(char* text);

    int script(char* javascript);

    int cookie(const char* cookiefile);

    void event_loop(client_cb func);

public:
    static int ET_ALIVE;
    static int ET_START;
    static int ET_LOAD;
    static int ET_DUMPHTML;
    static int ET_QUIT;
    static int ET_GETELEMENT;
    static int ET_SETVALUE;
    static int ET_CLICK;
    static int ET_TYPE;
    static int ET_SCRIPT;
    static int ET_COOKIE;
    static int ET_STATUS;

private:
    char m_url[512];
    char* m_buf;

};



#endif /* EVENTHANDLE_H_ */
