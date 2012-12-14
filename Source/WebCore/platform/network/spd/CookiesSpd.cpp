#include "config.h"

static string cookies_file;

bool cookie_test(string file)
{
    if( access(file.c_str(),R_OK|W_OK) != 0)
    {
        fprintf(stderr,"[warn]:     cookie(%s)不存在或没有读写权限\n",file.c_str());
        return -1;
    }
}

bool setCookies(string file)
{
    if(cookie_test(file))
    {
		cookies_file = file;
        return true;
    }	
    return false;
}


string getCookies()
{
	return cookies_file;
}
