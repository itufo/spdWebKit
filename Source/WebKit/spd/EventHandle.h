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

    void event_loop(client_cb func);


public:
    static int ET_ALIVE;
    static int ET_START;
    static int ET_LOAD;
    static int ET_DUMPHTML;
    static int ET_QUIT;

private:
    char m_url[512];
    char* m_buf;

};



#endif /* EVENTHANDLE_H_ */
