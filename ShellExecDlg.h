// ShellExecDlg.h : header file
//

#if !defined(AFX_SHELLEXECDLG_H__EA9E5018_1989_11D1_9269_000000000000__INCLUDED_)
#define AFX_SHELLEXECDLG_H__EA9E5018_1989_11D1_9269_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CShellExecDlg dialog

class CShellExecDlg : public CDialog
{
// Construction
public:
	CShellExecDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CShellExecDlg)
	enum { IDD = IDD_SHELLEXEC_DIALOG };
	CString	m_strOperation;
	CString	m_strFileName;
	CString	m_strParams;
	int		m_nCmdShow;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShellExecDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	HICON m_hSmallIcon;

	// Generated message map functions
	//{{AFX_MSG(CShellExecDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	// 0 is ShellExecute, 1 is ShellExecuteEx
	int m_API;
public:
	// The registry key name for the SEE_MASK_CLASSKEY value
	CString m_strClassKeyName;
private:
	CString m_strDirectory;
public:
	afx_msg void OnBnClickedPickFile();
	afx_msg void OnBnClickedPickDir();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHELLEXECDLG_H__EA9E5018_1989_11D1_9269_000000000000__INCLUDED_)
