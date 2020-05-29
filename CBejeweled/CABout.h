#pragma once


// CABout 对话框

class CABout : public CDialogEx
{
	DECLARE_DYNAMIC(CABout)

public:
	CABout(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CABout();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CABOUTDLG_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
