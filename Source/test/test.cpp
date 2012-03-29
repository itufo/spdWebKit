#include <stdio.h>
#include <spdWebKit/EventHandle.h>
#include <unistd.h>
#include <stdlib.h>

void* client_work(void* param)
{
    EventHandle* pHandle = (EventHandle*)param;
    pHandle->start();
    pHandle->load("http://localhost/test2.html");
    sleep(4);
    char* html  = pHandle->dumpHTML();
    printf("%s\n\n",html);
    exit(0);
}

int main(int argc, char* argv[])
{
        EventHandle::init();
        EventHandle* pHandle = new EventHandle();
        pHandle->event_loop(client_work);
        return 0;
}
