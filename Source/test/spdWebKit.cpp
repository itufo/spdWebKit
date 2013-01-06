#include <stdio.h>
#include <spdWebKit/EventHandle.h>
#include <iostream>
#include <cstring>
#include <vector>
#include<fstream>
#include<iostream>
#include<string>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

string cookie;
string jsfile;
string script;
string file;
string url;

bool readjs()
{
	ifstream ifFile(jsfile.c_str());
	if( !ifFile )
	{
       cout<<1<<endl;
		return -1;
	}
	ifFile.seekg(0, ios::end); 
	int iFileSize = ifFile.tellg();
	ifFile.seekg( 0, ios::beg );
	char *pBuffer = new char[iFileSize+1];
	if ( pBuffer == NULL )
	{
       cout<<2<<endl;
       return -1;
	}
    cout<<iFileSize<<endl;
	memset(pBuffer, 0, iFileSize+1);
	ifFile.read( pBuffer, iFileSize);
    script = pBuffer;
    free(pBuffer);
	return true;
}

void* client_work(void* param)
{
    EventHandle* pHandle = (EventHandle*)param;
    pHandle->start();
    sleep(1);

    if(!cookie.empty())
    	pHandle->cookie(cookie.c_str());

    pHandle->load((char*)url.c_str());
    sleep(10);
    cout<<script<<endl;
    pHandle->script((char*)script.c_str());
    sleep(5);
    char* html  = pHandle->dumpHTML();
    if(file.empty())
    {
    	printf("%s\n\n",html);
    }
	else{
    	ofstream outFile(file.c_str());
    	outFile << html;
    	outFile.close();
    }
    exit(0);
}

int main(int argc, char* argv[])
{
    if(argc<2)
    {
        printf(" Usage: spdWebKit -c [cookie] -s [extend.js] -o [save_to_file] -u [url] \n");
        return -1;
    }

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-c") == 0 && i < argc - 1)
        {
            cookie = argv[i + 1];
        }
        else if (strcmp(argv[i], "-s") == 0 && i < argc - 1)
        {
			jsfile = argv[i+1];
            readjs();
        }
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1)
        {
            file = argv[i+1];
        }
        else if (strcmp(argv[i], "-u") == 0 && i < argc - 1)
        {
            url = argv[i+1];
        }
    }

    if(url.empty())
    {
        printf(" Usage: spdlogin -c [cookie] -s [login.js] -o [save_to_file] -u [url] \n");
        return -1;
    }

    EventHandle::init();
    EventHandle* pHandle = new EventHandle();
    pHandle->event_loop(client_work);
        //pHandle->event_loop(NULL);
    return 0;
}
