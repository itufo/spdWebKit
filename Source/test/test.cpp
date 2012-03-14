#include <stdio.h>
//#include <spdWebKit/DocumentLoaderSpd.h>
#include <spdWebKit/spdWebView.h>

int main(int argc, char* argv[])
{
	printf("Hello world!\n");
	//spdDocumentLoader_new("http://www.baidu.com/");
	spdWebView* view = spdWebView_new();
        spdWebView_load(view,argc<2?"http://www.baidu.com/":argv[1]);
        return 0;
}
