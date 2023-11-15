// WD7 Langage Externe.h : main header file for the WD7 LANGAGE EXTERNE application
//

#if !defined(AFX_WD7LANGAGEEXTERNE_H__BF67601D_F74F_4360_B1A0_6769FFFC0212__INCLUDED_)
#define AFX_WD7LANGAGEEXTERNE_H__BF67601D_F74F_4360_B1A0_6769FFFC0212__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWD7LangageExterneApp:
// See WD7 Langage Externe.cpp for the implementation of this class
//
class CHFContext;

class CWD7LangageExterneApp : public CWinApp
{
protected :
	CHFContext	*	m_pclHF;				// Gestion du contexte Hyper File

public:
	CWD7LangageExterneApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWD7LangageExterneApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	void ArretAppli(LPCTSTR pszMsg=NULL);

	//{{AFX_MSG(CWD7LangageExterneApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WD7LANGAGEEXTERNE_H__BF67601D_F74F_4360_B1A0_6769FFFC0212__INCLUDED_)
