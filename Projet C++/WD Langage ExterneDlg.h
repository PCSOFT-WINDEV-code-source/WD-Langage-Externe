// WD7 Langage ExterneDlg.h : header file
//

#if !defined(AFX_WD7LANGAGEEXTERNEDLG_H__8B97C280_3AAC_49B7_8C74_5C002CBF3A2F__INCLUDED_)
#define AFX_WD7LANGAGEEXTERNEDLG_H__8B97C280_3AAC_49B7_8C74_5C002CBF3A2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWD7LangageExterneDlg dialog

class CWD7LangageExterneDlg : public CDialog
{
// Construction
public:
	CWD7LangageExterneDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWD7LangageExterneDlg)
	enum { IDD = IDD_WD7LANGAGEEXTERNE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWD7LangageExterneDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWD7LangageExterneDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WD7LANGAGEEXTERNEDLG_H__8B97C280_3AAC_49B7_8C74_5C002CBF3A2F__INCLUDED_)
