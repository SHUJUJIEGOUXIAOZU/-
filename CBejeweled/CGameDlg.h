#pragma once


// CGameDlg 对话框
#include"CGameLogic.h"
class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();
	CRect m_client1;//
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CGAMEDLG_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	HICON m_hIcon;
    void Init();//初始化图片
	CDC m_dcMask;//掩码
	CDC m_dcElem;//图片
	CDC m_dcMem; //内存DC
	CDC m_dcBg;  //背景内存dc
	CGameLogic m_GameLogic;
	CDC m_dcRemove;//消除
	CDC m_dcCache;
	bool m_bFirstElem=true;//是否为第一个图片
	PICELEM m_picElemFirst;//第一个图片
	PICELEM m_picElemSecond;//第二个图片
	CFont m_Font;//字体
	bool m_bPlaying;//游戏是否进行
   #define MOVE_PIXEL 10 //每次移动像素为10
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void DrawGameArea();
	CRect m_rtGame;
	void ChangeCartoon();	//交换动画
	void DrawTip(PICELEM picElem);//画提示
	afx_msg void OnBnClickedButton4();
	afx_msg void InitWnd();
	afx_msg void OnPaint();
	CRect GetElemRect(PICELEM picElem);
	void GetElemLUxy(PICELEM picElem, int & nX, int & nY);
	void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void Restart();//重新开始
}; 
