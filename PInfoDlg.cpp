// PInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShellExec.h"
#include "PInfoDlg.h"


// CPInfoDlg dialog

IMPLEMENT_DYNAMIC(CPInfoDlg, CDialog)
CPInfoDlg::CPInfoDlg(HANDLE hProcess, CWnd* pParent /*=NULL*/)
	: CDialog(CPInfoDlg::IDD, pParent), m_hProcess( hProcess )
{
}

CPInfoDlg::~CPInfoDlg()
{
}

void CPInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DWORD_PTR dwVal = reinterpret_cast<DWORD_PTR>( m_hProcess );
	DDX_Text(pDX, IDC_HPROCESS, dwVal );
}


BEGIN_MESSAGE_MAP(CPInfoDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CPInfoDlg message handlers

void CPInfoDlg::OnBnClickedOk()
{
	DWORD ExitCode;

	if ( GetExitCodeProcess( m_hProcess, &ExitCode ) )
	{
		if ( ExitCode == STILL_ACTIVE )
		{
			SetDlgItemText( IDC_GECP_VALUE, _T("Still Active") );
		}
		else
		{
			TCHAR szValue[sizeof("0x12341234")];
			szValue[0] = '0';
			szValue[1] = 'x';

#if _MSC_VER < 1400
			_itot( ExitCode, &szValue[2], 16 );
#else
			_itot_s( ExitCode, &szValue[2], _countof(szValue), 16 );
#endif
			SetDlgItemText( IDC_GECP_VALUE, szValue );
		}
	}
	else
	{
		SetDlgItemText( IDC_GECP_VALUE, _T("Failed!") );
	}
}

BOOL CPInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	/* Do an initial update of the information */
	OnBnClickedOk();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
