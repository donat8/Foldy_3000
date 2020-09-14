
// Foldy_3000Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Foldy_3000.h"
#include "Foldy_3000Dlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFoldy3000Dlg dialog



CFoldy3000Dlg::CFoldy3000Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FOLDY_3000_DIALOG, pParent)
	, search_string(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFoldy3000Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCSHELLTREE1, shell_tree);
	DDX_Control(pDX, IDC_MFCSHELLLIST3, shell_list);

}

BEGIN_MESSAGE_MAP(CFoldy3000Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON1, &CFoldy3000Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CFoldy3000Dlg message handlers

BOOL CFoldy3000Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog	
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	SetIcon(hIcon, FALSE);     // Set small icon
	SetIcon(hIcon, TRUE);    // Set big icon
	//postavlja fileove odabranog foldera u shell list
	shell_tree.SetRelatedList(&shell_list);
	
	KeywordError.LoadStringW(KEYWORD_ERROR);
	FolderError.LoadStringW(FOLDER_ERROR);
	CheckingError.LoadStringW(CHECKING_ERROR);
	CopyFailed.LoadStringW(COPY_FAILED);
	CopySuccess.LoadStringW(COPY_SUCCESS);

	// TODO: Add extra initialization here


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFoldy3000Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFoldy3000Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFoldy3000Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//dobavlja sve foldere koji su oznaceni sa kvacicom
std::vector<HTREEITEM> CFoldy3000Dlg::GetCheckedItems(const CTreeCtrl& tree, std::vector<HTREEITEM>& checkedItems, HTREEITEM startItem)
{
	if (startItem == NULL)
		startItem = tree.GetRootItem();

	for (HTREEITEM item = startItem; item != NULL; item = tree.GetNextItem(item, TVGN_NEXT))
	{
		UINT state = (tree.GetItemState(item, TVIS_STATEIMAGEMASK) >> 12) & 15;

		// je li chekirano
		if (state == 2) {
			checkedItems.push_back(item);
		}
		// pretrazuje djecu
		HTREEITEM child = tree.GetNextItem(item, TVGN_CHILD);

		if (child != NULL)
			GetCheckedItems(tree, checkedItems, child);
	}
	return checkedItems;
}

//pretrazuje chekirane foldere i fileove usporedjuje sa search_stringom i sprema ih u all_paths niz
void CFoldy3000Dlg::SearchTrough(std::vector<HTREEITEM>& checkedItems) {

	//temp var za path filea koji smo chekirali
	CString strPath;

	
	//chekira foldere
	for (int i = 0; i < checkedItems.size(); i++) {
		CString text = shell_tree.GetItemText(checkedItems[i]);
		shell_tree.GetItemPath(strPath, checkedItems[i]);

		//ako mozda neki od oznacenih foldera sadrzi keyword
		if (text.Find(search_string)!=std::string::npos){
			std::wstring foundFolderByString(strPath);
			paths_in.push_back(foundFolderByString);
		}
		//chekira fileove
		Get_All_File_Paths(strPath);
	}	

}

//dobavlja sve fileove iz oznacenih foldera koji odgovaraju search_stringu
void CFoldy3000Dlg::Get_All_File_Paths(LPCTSTR pstr)
{
	CFileFind finder;

	// potrebno za naznacavanje koji tip datoteke trazimo
	CString strWildcard(pstr);
	strWildcard += _T("\\*.*");
	
	// start
	BOOL bWorking = finder.FindFile(strWildcard);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		//GetFileName da se moze pretrazivati sa ekstenzijom
		if (finder.GetFileName().Find(search_string) != std::string::npos){
			std::wstring FilePaths(finder.GetFilePath());
			paths_in.push_back(FilePaths);
		}
		//preskace se . i .. zbog beskonacne rekurzije
		if (finder.IsDots())
			continue;

		//ako je folder, rekrurzivno pretrazi
		if (finder.IsDirectory())
		{
			CString str = finder.GetFilePath();
			Get_All_File_Paths(str);
		}
	}
	finder.Close();
}

//kopiranje u novi zadani folder
void CFoldy3000Dlg::CopyFilesToFolder(std::vector<std::wstring> paths_in, std::wstring path_to) {

	if (paths_in.empty())
		SetDlgItemText(IDC_STATIC_SUCCESS, CopyFailed);
	else {
    	for (int i = 0; i < paths_in.size(); i++) {
    		if(SHCopy(paths_in[i], path_to)==false)
				SetDlgItemText(IDC_STATIC_SUCCESS, CopyFailed);
    	}
    	SetDlgItemText(IDC_EDIT1, L"");
		SetDlgItemText(IDC_STATIC_SUCCESS, CopySuccess);
	}
}

// COPY button
void CFoldy3000Dlg::OnBnClickedButton1()
{	
	//sprema path_to
	CString path_to;
	GetDlgItemTextW(IDC_MFCEDITBROWSE3, path_to);
	std::wstring path_to_w(path_to.GetString());

	//sprema keyword
	GetDlgItemText(IDC_EDIT1, search_string);

	//trazi chekirane iteme
	std::vector<HTREEITEM> checkedItems;
	checkedItems= GetCheckedItems(shell_tree, checkedItems);

	if (checkedItems.empty()) {
		SetDlgItemText(IDC_STATIC_TREE, CheckingError);	}
	else if (path_to_w.empty()) {
		SetDlgItemText(IDC_STATIC_FOLDER, FolderError);	}
	else if (search_string.IsEmpty())
		SetDlgItemText(IDC_STATIC_KEYWORD, KeywordError);
	else{
		SetDlgItemText(IDC_STATIC_TREE, L"");
		SetDlgItemText(IDC_STATIC_FOLDER, L""); 
		SetDlgItemText(IDC_STATIC_KEYWORD, L"");
		SearchTrough(checkedItems);
		CopyFilesToFolder(paths_in, path_to_w);
		paths_in.clear();
	}
}

bool CFoldy3000Dlg::SHCopy(std::wstring& from, std::wstring& to)
{
	//ako zelimo fileove i foldere iz trazenog foldera ali bez kopiranja njega
	//if (all_Paths.GetCount() > 0)
	//	from += L"\\*";
	
	WCHAR sf[MAX_PATH + 1];
	WCHAR tf[MAX_PATH + 1];

	wcscpy_s(sf, MAX_PATH, from.c_str());
	wcscpy_s(tf, MAX_PATH, to.c_str());
	
	sf[lstrlenW(sf) + 1] = 0;
	tf[lstrlenW(tf) + 1] = 0;

	SHFILEOPSTRUCT s = { 0 };
	s.wFunc = FO_COPY;
	s.fFlags = FOF_NOCONFIRMMKDIR;
	s.pTo = tf;
	s.pFrom = sf;
	if (SHFileOperation(&s) == 0)
		return true;
	else
		return false;
	return false;
}




