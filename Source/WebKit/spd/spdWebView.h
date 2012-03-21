#ifndef spdWebView_h
#define spdWebView_h

typedef struct _spdWebView spdWebView;

spdWebView* spdWebView_new();

int spdWebView_load(spdWebView* me, const char* url);

#endif
