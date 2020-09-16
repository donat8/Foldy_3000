
// Foldy_3000Dlg.h : header file
//

#pragma once
#include <numeric>
#include <afxShellListCtrl.h>
#include <string>
#include <memory>
#include <vector>


// CFoldy3000Dlg dialog
class CFoldy3000Dlg : public CDialogEx
{
// Construction
public:
	CFoldy3000Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FOLDY_3000_DIALOG };

#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CMFCShellTreeCtrl shell_tree;
	CMFCShellListCtrl shell_list;

	std::vector<HTREEITEM> GetCheckedItems(const CTreeCtrl& tree, std::vector<HTREEITEM>& checkedItems, HTREEITEM startItem=NULL);

	void SearchTrough(std::vector<HTREEITEM>& checkedItems);
	void Get_All_File_Paths(LPCTSTR pstr);

	void CopyFilesToFolder(std::wstring path_to);

	//void CopyFilesToFolder(std::vector<std::wstring> paths_in, std::wstring path_to);

	afx_msg

	CString search_string;
	std::vector<std::wstring> paths_in;

	//copy btn
	afx_msg void OnBnClickedButton1();
	bool CreateAFolder(CString path_to);
	bool SHCopy(std::wstring& to);
	//bool SHCopy(std::wstring& from, std::wstring& to);

	//error strings
	CString KeywordError;
	CString FolderError;
	CString CheckingError;
	CString CopyFailed;
	CString CopySuccess;
	CString FolderCreated;
	CString FolderIsntCreated;
	
	
	
};
