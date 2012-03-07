/*
 * DocumentLoaderSpd.h
 *
 *  Created on: 2012-3-7
 *      Author: jack
 */

#ifndef DOCUMENTLOADERSPD_H_
#define DOCUMENTLOADERSPD_H_

#ifdef _CPLUSPLUS
extern "C" {
#endif

typedef struct _DocumentLoaderSpd DocumentLoaderSpd;

DocumentLoaderSpd* DocumentLoader_new(const char* url);

void DocumentLoader_delete();


#ifdef _CPLUSPLUS
}
#endif

#endif /* DOCUMENTLOADERSPD_H_ */
