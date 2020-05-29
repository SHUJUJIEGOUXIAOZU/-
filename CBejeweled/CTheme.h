#pragma once


// CTheme 对话框

class CTheme : public CDialogEx
{
	DECLARE_DYNAMIC(CTheme)

public:
	CTheme(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTheme();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CThEMEDLG_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	CButton Theme_RADIO1;
	CButton Theme_RADIO2;
	CButton Theme_RADIO3;
	CButton Theme_RADIO4;
	CButton Theme_RADIO5;
	CButton Theme_BUTTON1;
	CButton Theme_BUTTON2;
	CEdit Theme_EDIT1;
	CEdit Theme_EDIT2;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
};
