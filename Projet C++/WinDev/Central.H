// Interface des contextes Hyper File utilisée par le langage externe
// Fichier destiné à être envoyé en clientèle


#ifndef __CENTRAL_H
#define __CENTRAL_H

	#include <tchar.h>
	#define XCHAR		TCHAR
	#define _X(txt)		__T(txt)
	#define PCXSTR		LPCTSTR
	#define PXSTR		LPTSTR
	#define XRC			_X("\r\n")			// retour à la ligne
	#define STRCPY		_tcscpy
	#define STRCMP		_tcscmp
	#define STRICMP		_tcsicmp
	#define STRLEN		_tcslen
	#define XUSIZE32	DWORD
	#define INT_32		long

	#if defined(__BORLANDC__)
		#define NOVTABLE
	#else
		#define NOVTABLE  __declspec(novtable)
	#endif
   #ifndef UINT_32
   	typedef unsigned long UINT_32;
   #endif
#ifdef __HFCONTEXT_H
#define WDFINHF	if (gclHF.piGetHFContext() != NULL){gclHF.piGetHFContext()->nExternalRelease();char ** pgclHF = (char **)((char *)&gclHF + sizeof(void*));*pgclHF = NULL;}
#define WDTerm	WDFINHF;WDTerm
#endif

#endif //#ifndef __CENTRAL_H

