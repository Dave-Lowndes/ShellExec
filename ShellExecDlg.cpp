// ShellExecDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShellExec.h"
#include "ShellExecDlg.h"
#include "PInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShellExecDlg dialog

CShellExecDlg::CShellExecDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShellExecDlg::IDD, pParent)
	, m_API(0)
	, m_strClassKeyName(_T(""))
	, m_strDirectory(_T(""))
{
	//{{AFX_DATA_INIT(CShellExecDlg)
	m_strOperation = _T("");
	m_strFileName = _T("");
	m_strParams = _T("");
	m_nCmdShow = SW_NORMAL;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hSmallIcon = (HICON) LoadImage( AfxGetResourceHandle(), MAKEINTRESOURCE( IDR_MAINFRAME ), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR );
}

void CShellExecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShellExecDlg)
	DDX_Text(pDX, IDC_OPERATION, m_strOperation);
	DDX_Text(pDX, IDC_FILENAME, m_strFileName);
	DDX_Text(pDX, IDC_PARAMS, m_strParams);
	DDX_CBIndex(pDX, IDC_SWC, m_nCmdShow);
	//}}AFX_DATA_MAP
	DDX_Radio(pDX, IDC_SE, m_API);
	DDX_Text(pDX, IDC_CLASSKEYNAME, m_strClassKeyName);
	DDX_Text(pDX, IDC_DIRECTORY, m_strDirectory);
}

BEGIN_MESSAGE_MAP(CShellExecDlg, CDialog)
	//{{AFX_MSG_MAP(CShellExecDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_PICK_FILE, &CShellExecDlg::OnBnClickedPickFile)
	ON_BN_CLICKED(IDC_PICK_DIR, &CShellExecDlg::OnBnClickedPickDir)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShellExecDlg message handlers

BOOL CShellExecDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hSmallIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
//	CheckDlgButton( IDC_SEE_MASK_INVOKEIDLIST, BST_CHECKED );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShellExecDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CShellExecDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CShellExecDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CShellExecDlg::OnOK() 
{
	/* Get the member variables */
	UpdateData();

	LPCTSTR pOp = m_strOperation.IsEmpty() ? NULL : static_cast<LPCTSTR>( m_strOperation );
	LPCTSTR pParams = m_strParams.IsEmpty() ? NULL : static_cast<LPCTSTR>( m_strParams );
	LPCTSTR pDirectory = m_strDirectory.IsEmpty() ? NULL : static_cast<LPCTSTR>( m_strDirectory );

	/* ShellExecute or ShellExecuteEx ? */
	if ( m_API == 0 )
	{
		HINSTANCE hInst = ShellExecute( m_hWnd, pOp, m_strFileName, pParams, pDirectory, m_nCmdShow );

		if ( (HINSTANCE) 32 >= hInst )
		{
			/* Failed - report why */
			LPTSTR lpMessageBuffer;

			FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			  NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //The user default language
			  (LPTSTR) &lpMessageBuffer, 0, NULL );

			//... now display this string
			AfxMessageBox( lpMessageBuffer );

			// Free the buffer allocated by the system
			LocalFree( lpMessageBuffer );
		}
	}
	else
	{
		/* Get the combination of check boxes */
		DWORD Mask = 0;
		{
// I'd named the UI controls the same as the SEE_MASK_ flags, so I can use a macro to generate the table
#define IDCIT(x) IDC_##x, x
			struct
			{
				int id;
				DWORD fMask;
			} static const Flags [] = 
			{
				IDCIT(SEE_MASK_CLASSKEY)
				, IDCIT(SEE_MASK_CLASSNAME)
				, IDCIT(SEE_MASK_CONNECTNETDRV)
				, IDCIT(SEE_MASK_DOENVSUBST)
				, IDCIT(SEE_MASK_FLAG_DDEWAIT)
				, IDCIT(SEE_MASK_FLAG_LOG_USAGE)
				, IDCIT(SEE_MASK_FLAG_NO_UI)
				, IDCIT(SEE_MASK_HMONITOR)
				, IDCIT(SEE_MASK_HOTKEY)
				, IDCIT(SEE_MASK_ICON)
				, IDCIT(SEE_MASK_IDLIST)
				, IDCIT(SEE_MASK_INVOKEIDLIST)
				, IDCIT(SEE_MASK_NOCLOSEPROCESS)
				, IDCIT(SEE_MASK_NO_CONSOLE)
				, IDCIT(SEE_MASK_UNICODE)
			};

			for ( const auto & item : Flags )
			{
				if ( IsDlgButtonChecked( item.id ) == BST_CHECKED )
				{
					Mask |= item.fMask;
				}
			}
		}

		SHELLEXECUTEINFO sei = {0};

		if ( Mask & SEE_MASK_HMONITOR )
		{
			sei.hMonitor = MonitorFromWindow( GetSafeHwnd(), MONITOR_DEFAULTTONEAREST );
		}

		sei.hwnd = m_hWnd;
		sei.cbSize = sizeof(sei);
		sei.lpFile = m_strFileName;
		sei.lpVerb = pOp;
		// This flag is needed to invoke the "properties" verb, as there's no association in the registry
		sei.fMask  = Mask;	//SEE_MASK_INVOKEIDLIST /*| SEE_MASK_FLAG_DDEWAIT | SEE_MASK_NOCLOSEPROCESS*/;

		// To override the application that opens the file, use the class name.
		// For example, to use WordPad to open a .xls file, use the class name "textfile".
		if ( ( Mask & SEE_MASK_CLASSKEY ) == SEE_MASK_CLASSKEY )
		{
			if ( ERROR_SUCCESS == RegOpenKeyEx( HKEY_CLASSES_ROOT, m_strClassKeyName, 0, KEY_READ, &sei.hkeyClass ) )
			{
			}
		}
		else if ( Mask & SEE_MASK_CLASSNAME )
		{
			sei.lpClass = m_strClassKeyName;
		}

		sei.lpParameters = pParams;
		sei.lpDirectory = pDirectory;
		sei.nShow = m_nCmdShow;

		/* MS recommend initialising COM before using ShellExecuteEx */
		HRESULT hr = CoInitializeEx( NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE );

		const BOOL bExecOK = ShellExecuteEx(&sei);

		CoUninitialize();

		if ( !bExecOK )
		{
			/* Failed - report why */
			LPTSTR lpMessageBuffer;

			FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			  NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //The user default language
			  (LPTSTR) &lpMessageBuffer, 0, NULL );

			//... now display this string
			AfxMessageBox( lpMessageBuffer );

			// Free the buffer allocated by the system
			LocalFree( lpMessageBuffer );
		}

		if ( sei.hkeyClass )
		{
			RegCloseKey( sei.hkeyClass );
		}

		/* If we succeeded and ran the program */
		if ( bExecOK )
		{
			/* Did we ask for the process handle */
			if ( Mask & SEE_MASK_NOCLOSEPROCESS )
			{
				/* Is there a valid process handle? */
				if ( sei.hProcess != NULL )
				{
					/* We've got a process handle, so display the information in the dialog */
					CPInfoDlg PIDlg( sei.hProcess );
					PIDlg.DoModal();

					/* Close the process handle */
					CloseHandle( sei.hProcess );
				}
				else
				{
					AfxMessageBox( _T("No process handle returned.") );
				}
			}
		}
#if 0
		else
		{

			for ( int i = 0; i < 10; i++ )
			{
				Sleep( 1000 );
				/* Find the window for the process */
				HWND hWnd = ::FindWindow( NULL, "VidRes" );

				if ( hWnd != NULL )
				{
//					::SetForegroundWindow( hWnd );
					::ShowWindow( hWnd, SW_SHOWNOACTIVATE );
					MessageBeep( MB_OK );
					break;
				}
			}
		}
#endif
	}
}

void CShellExecDlg::OnBnClickedPickFile()
{
	CFileDialog dlg( TRUE );

	if ( dlg.DoModal() == IDOK )
	{
		SetDlgItemText( IDC_FILENAME, dlg.GetPathName() );
	}
}

void CShellExecDlg::OnBnClickedPickDir()
{
	/* Show the folder browser and let the user select the base folder they want to print from */
	BROWSEINFO bi = {0};

	bi.hwndOwner = m_hWnd;

	LPITEMIDLIST pidl = SHBrowseForFolder( &bi );

	if ( pidl != NULL )
	{
		TCHAR szDir[_MAX_PATH];

		if ( SHGetPathFromIDList( pidl, szDir ) )
		{
			SetDlgItemText( IDC_DIRECTORY, szDir );
		}

		CoTaskMemFree( pidl );
	}
}
