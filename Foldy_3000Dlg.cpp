
// Foldy_3000Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Foldy_3000.h"
#include "Foldy_3000Dlg.h"
#include "afxdialogex.h"

#include <fstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <filesystem>




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
ON_NOTIFY(NM_CLICK, IDC_MFCSHELLTREE1, &CFoldy3000Dlg::OnNMClickMfcshelltree1)
ON_EN_CHANGE(IDC_MFCEDITBROWSE3, &CFoldy3000Dlg::OnEnChangeMfceditbrowse3)
ON_BN_CLICKED(IDC_BUTTON1, &CFoldy3000Dlg::OnBnClickedButton1)
ON_EN_CHANGE(IDC_EDIT1, &CFoldy3000Dlg::OnEnChangeEdit1)
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
void CFoldy3000Dlg::GetCheckedItems(const CTreeCtrl& tree, CArray<HTREEITEM>* checkedItems, HTREEITEM startItem)
{
	if (startItem == NULL)
		startItem = tree.GetRootItem();

	for (HTREEITEM item = startItem; item != NULL; item = tree.GetNextItem(item, TVGN_NEXT))
	{
		UINT state = (tree.GetItemState(item, TVIS_STATEIMAGEMASK) >> 12) & 15;

		// je li chekirano
		if (state == 2) {	
			checkedItems->Add(item);
		}
		
		// pretrazuje djecu
		HTREEITEM child = tree.GetNextItem(item, TVGN_CHILD);

		if (child != NULL)
			GetCheckedItems(tree, checkedItems, child);
	}
}


void CFoldy3000Dlg::OnNMClickMfcshelltree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
	//postavlja fileove odabranog foldera u shell list
	shell_tree.SetRelatedList(&shell_list);
}


//pretrazuje chekirane foldere i fileove usporedjuje sa search_stringom i sprema ih u all_paths niz
void CFoldy3000Dlg::SearchTrough() {

	//temp var za path filea koji smo chekirali
	CString strPath;
	
	//chekira foldere
	for (int i = 0; i < checkedItems.GetCount(); i++) {
		CString text = shell_tree.GetItemText(checkedItems[i]);
		shell_tree.GetItemPath(strPath, checkedItems[i]);

		//ako mozda neki od oznacenih foldera sadrzi keyword
		if (text.Find(search_string)!=std::string::npos){
			all_Paths.Add(strPath);
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
		if (finder.GetFileName().Find(search_string) != std::string::npos)
			all_files_paths.Add(finder.GetFilePath());

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
void CFoldy3000Dlg::CopyFilesToFolder() {

	std::wstring path_to_copy(path_to.GetString());
	if (all_Paths.IsEmpty() && all_files_paths.IsEmpty())
		SetDlgItemText(IDC_STATIC_SUCCESS, L"Copying failed!");
	else {
    	for (int i = 0; i < all_Paths.GetCount(); i++) {
    		std::wstring path_in(all_Paths[i].GetString());
    		SHCopy(path_in, path_to_copy);
    		//all_Paths.RemoveAt(i);
    	}
    	for (int i = 0; i < all_files_paths.GetCount(); i++) {
    		std::wstring all_files_path_temp(all_files_paths[i].GetString());
    		SHCopy(all_files_path_temp, path_to_copy);
    	}
    	all_Paths.RemoveAll();
    	all_files_paths.RemoveAll();
    	checkedItems.RemoveAll();
    	SetDlgItemText(IDC_EDIT1, L"");
		SetDlgItemText(IDC_STATIC_SUCCESS, L"SUCCESS!!");
	}
}


void CFoldy3000Dlg::OnEnChangeMfceditbrowse3()
{
	//kopira tekst EDIT BROWSE kontrole, oliti, potreban path za postojeci folder
	GetDlgItemTextW(IDC_MFCEDITBROWSE3,path_to);
}


// COPY button
void CFoldy3000Dlg::OnBnClickedButton1()
{	
	checkedItems.RemoveAll();
	GetCheckedItems(shell_tree, &checkedItems);

	if (checkedItems.IsEmpty()) {
		SetDlgItemText(IDC_STATIC_TREE, L"No folders checked!");	}
	else if (path_to.IsEmpty()) {
		SetDlgItemText(IDC_STATIC_FOLDER, L"Choose a folder!");	}
	else if (search_string.IsEmpty())
		SetDlgItemText(IDC_STATIC_KEYWORD, L"Need a search string!");
	else{
		SetDlgItemText(IDC_STATIC_TREE, L"");
		SetDlgItemText(IDC_STATIC_FOLDER, L""); 
		SetDlgItemText(IDC_STATIC_KEYWORD, L"");
		SearchTrough();
		CopyFilesToFolder();
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
	SHFileOperation(&s);
}

//sprema promjenu teksta u varijablu search_string
void CFoldy3000Dlg::OnEnChangeEdit1()
{
	GetDlgItemText(IDC_EDIT1,search_string);
}


