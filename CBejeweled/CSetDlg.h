#pragma once
#include "CMusicDlg.h"
#include "CTheme.h"

// CSetDlg 对话框

class CSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetDlg)

public:
	CSetDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSetDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CSETDLG_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl CSetDlg_Tab;
	CMusicDlg music;
	CTheme theme;
	afx_msg void OnTcnSelchangeCsetdlgTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton1();
};
