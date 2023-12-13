#pragma once


// CPInfoDlg dialog

class CPInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CPInfoDlg)

public:
	CPInfoDlg(HANDLE hProcess, CWnd* pParent = NULL);
	virtual ~CPInfoDlg();

// Dialog Data
	enum { IDD = IDD_PINFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	// The process handle of the spawned process
	HANDLE m_hProcess;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
