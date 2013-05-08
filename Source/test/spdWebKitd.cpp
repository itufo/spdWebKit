#include <spdWebKit/EventHandle.h>
#include <spider3/spd.h>

using namespace std;

int connfd = -1;
spdHttp* p_http = NULL;

void* spdWebKitd_local(void* p_connfd);

//网络服务
int spdWebKitd_server(int port)
{
    int threads = 10;
    //临时变量
    int i, j, rc;

    int sock_listen; //监听套接字
    int sock_cli; //客户端连接
    int listen_index;

    socklen_t addrlen; //地址信息长度
    struct sockaddr_in addr4; //IPv4地址结构

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serveraddr;
    bzero(&serveraddr, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);

    //设置SO_REUSEADDR选项(服务器快速重起)
    unsigned int optval = 0x1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, 4);

    //设置SO_LINGER选项(防范CLOSE_WAIT挂住所有套接字)
    struct linger optval1;
    optval1.l_onoff = 1;
    optval1.l_linger = 60;
    setsockopt(listenfd, SOL_SOCKET, SO_LINGER, &optval1,
            sizeof(struct linger));

    if (0 > bind(listenfd, (sockaddr *) &serveraddr, sizeof(serveraddr)))
    {
        close(listenfd);
        fprintf(stderr, "bind to %d fail\n", port);
        return (-1);
    }
    else
    {
        cout << "bind to " << port << endl;
    }
    if (0 > listen(listenfd, LINK_MAX))
    {
        close(listenfd);
        fprintf(stderr, "listen to %d fail\n", port);
        return (-1);
    }
    else
    {
        cout << "listening... " << endl;
    }

    //服务循环
    for (;;)
    {
        struct sockaddr_in clientaddr;
        bzero(&clientaddr, sizeof(clientaddr));

        socklen_t clilen = sizeof(struct sockaddr);
        connfd = -1;
        connfd = accept(listenfd, (struct sockaddr *) &clientaddr, &clilen);
        if (connfd < 0)
        {
            perror("connfd<0");
            continue;
        }
        char *str = inet_ntoa(clientaddr.sin_addr);
        printf("accapt a connection from %s at port %d FD(%d)\n", str,
                clientaddr.sin_port, connfd);

        spdProcess::fork(spdWebKitd_local, NULL);
        spdProcess::waitchild();

        //释放连接
        printf("释放连接\n");
        if (-1 == shutdown(connfd, SHUT_RDWR))
        {
            int a = EBADF;
            fprintf(stderr, "FAIL FD(%d),errno(%d) %s\n", sock_cli, errno,
                    strerror(errno));
        }
        close(connfd);
        connfd = -1;

    } //end of for(;;)
    return 0;
}

//本地进程
void* spdWebKitd_load(void* param)
{
    if (p_http == NULL)
        exit(0);

    const char* p_QueryString = p_http->getQueryString();

    cout << "QueryString:" << p_QueryString << endl;
    spdCgiAux* p_CgiAux = spdCgiAux_new(p_QueryString);
    char* p_url = NULL;
    spdCgiAux_query_value(p_CgiAux, "url", &p_url);

    EventHandle* pHandle = (EventHandle*) param;
    pHandle->start();
    sleep(1);

    pHandle->load(p_url);
    //for(int i=0;i<10;i++)
    //{
    //    pHandle->status();
    //    sleep(1);
    //}
    //sleep(10);

    char* html = pHandle->dumpHTML();

    p_http->sendResponse(html);

    exit(0);
    return NULL;
}

void* spdWebKitd_local(void*)
{
    if (p_http)
    {
        delete p_http;
        p_http = NULL;
    }
    p_http = new spdHttp();
    //接收请求
    p_http->setSocket(connfd);
    p_http->recvRequest();

    char* api = p_http->getApiName();
    if (api != NULL && strcmp(api, "/webkit") == 0)
    {
        EventHandle::init();
        EventHandle* pHandle = new EventHandle();

        pHandle->event_loop(spdWebKitd_load);
    }

    return NULL;
}

void cmd_help()
{
    cout << "Usage: spdWebKitd --port [port]" << endl;
    return;
}

int main(int argc, char* argv[])
{
    spdProcess::init();
    if (argc < 2)
    {
        cmd_help();
        exit(1);
    }

    int port = -1;
    int i = 0;
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--port") == 0 && i < argc - 1)
        {
            port = atoi(argv[i + 1]);
        }
    }

    if (port <= 0)
    {
        cmd_help();
        exit(1);
    }

    spdWebKitd_server(port);

    return 0;
}
