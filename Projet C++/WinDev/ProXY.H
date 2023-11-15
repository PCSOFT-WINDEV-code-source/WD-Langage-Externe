// Interface des contextes Hyper File utilisée par le langage externe
// Fichier destiné à être envoyé en clientèle

#ifndef __PROXY_H
#define __PROXY_H

	#include "central.h"

	#define PROXY_DECLARE(proxy)											\
				typedef class I##proxy* PI##proxy;							\
				class NOVTABLE I##proxy { public:
	#define PROXY_DECLARE_V(proxy,version,compat_since)						\
				static const int proxy##_PROXY_VERSION=version;				\
				static const int proxy##_PROXY_COMPAT_SINCE=compat_since;	\
				typedef class I##proxy* PI##proxy;							\
				class NOVTABLE I##proxy : public IStdVersion { public:
	#define PROXY_METHOD(type,proxy,method,args)		virtual type __stdcall I##proxy::method args =0;
	#define PROXY_EMPTY_METHOD(proxy)					_PROXY_EMPTY_METHOD_BEG(proxy,__LINE__)
	#define _PROXY_EMPTY_METHOD_BEG(proxy,line)		virtual void I##proxy::_PROXY_EMPTY_METHOD_END(EmptySlot,line) () {}
	#define _PROXY_EMPTY_METHOD_END(method,line)		method##line
	#define PROXY_STDVERSION_METHODS(proxy)							\
				PROXY_METHOD(int,proxy,nGetVersion,())				\
				PROXY_METHOD(int,proxy,nGetCompatSince,())			\
				PROXY_METHOD(int,proxy,nGetDllNum,())				\
				virtual void I##proxy::StdVersion_EmptySlot_1() {}	\
				virtual void I##proxy::StdVersion_EmptySlot_2() {}	\
				virtual void I##proxy::StdVersion_EmptySlot_3() {}
	#define PROXY_END					};

	PROXY_DECLARE(StdVersion)
		PROXY_STDVERSION_METHODS(StdVersion)
	PROXY_END


#endif //#ifndef __PROXY_H

