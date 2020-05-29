#pragma once


// CMusicDlg 对话框

class CMusicDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMusicDlg)

public:
	CMusicDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMusicDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMUSICDLG_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg
		BOOL OnInitDialog();
	CButton Music_CHECK1;
	CButton Music_CHECK2;
	CButton Music_RADIO1;
	CButton Music_RADIO2;
	CButton Music_RADIO3;
	CButton Music_Button1;
	CEdit Music_Edit1;

	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedRadio1();

	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedButton1();
};
