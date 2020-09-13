
// Foldy_3000Dlg.h : header file
//

#pragma once
#include <afxShellListCtrl.h>
#include <string>
#include <iostream>


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
	void GetCheckedItems(const CTreeCtrl& tree, CArray<HTREEITEM>* checkedItems, HTREEITEM startItem = NULL);
	CArray<HTREEITEM> checkedItems;

	afx_msg

	void OnNMClickMfcshelltree1(NMHDR* pNMHDR, LRESULT* pResult);

	TCHAR buffer[256];

	void SearchTrough();
	void Get_All_File_Paths(LPCTSTR pstr);
	void CopyFilesToFolder();

	CString search_string;
	CString path_to;

	CArray<CString> all_Paths;
	CArray<CString> all_files_paths;

	afx_msg void OnEnChangeMfceditbrowse3();
	CMFCEditBrowseCtrl copy_to;
	afx_msg void OnBnClickedButton1();
	bool SHCopy(std::wstring& from, std::wstring& to);
	
	
	afx_msg void OnEnChangeEdit1();
	
};
