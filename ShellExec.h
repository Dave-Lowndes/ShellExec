// ShellExec.h : main header file for the SHELLEXEC application
//

#if !defined(AFX_SHELLEXEC_H__EA9E5016_1989_11D1_9269_000000000000__INCLUDED_)
#define AFX_SHELLEXEC_H__EA9E5016_1989_11D1_9269_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShellExecApp:
// See ShellExec.cpp for the implementation of this class
//

class CShellExecApp : public CWinApp
{
public:
	CShellExecApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShellExecApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShellExecApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHELLEXEC_H__EA9E5016_1989_11D1_9269_000000000000__INCLUDED_)
