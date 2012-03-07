/*
 * DocumentLoaderSpd.cpp
 *
 *  Created on: 2012-3-7
 *      Author: jack
 */
#include "DocumentLoaderSpd.h"
#include "DocumentLoader.h"

#ifdef _CPLUSPLUS
extern "C" {
#endif
namespace WebCore{
struct _DocumentLoaderSpd{

};

DocumentLoaderSpd* DocumentLoader_new(const char* url)
{
    String res = url;
    ResourceRequest req(res);
    SubstituteData data;
    DocumentLoader* loader = DocumentLoader::create(req,data);
    loader->finishedLoading();
    return NULL;
}

void DocumentLoader_delete()
{

}



}
#ifdef _CPLUSPLUS
}
#endif
