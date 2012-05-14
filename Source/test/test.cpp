#include <stdio.h>
#include <spdWebKit/EventHandle.h>
#include <unistd.h>
#include <stdlib.h>

void* client_work(void* param)
{
    EventHandle* pHandle = (EventHandle*)param;
    pHandle->start();
    pHandle->load("http://localhost/test3.html");
    sleep(1);
    pHandle->getElementById("test");
    sleep(1);
    pHandle->setElementValue("Hello World!");
    sleep(1);
    char* html  = pHandle->dumpHTML();
    printf("%s\n\n",html);
    exit(0);
}

int main(int argc, char* argv[])
{
        EventHandle::init();
        EventHandle* pHandle = new EventHandle();
        //pHandle->event_loop(client_work);
        pHandle->event_loop(NULL);
        return 0;
}
