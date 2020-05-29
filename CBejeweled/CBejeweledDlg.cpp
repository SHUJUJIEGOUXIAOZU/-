
// CBejeweledDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CBejeweled.h"
#include "CBejeweledDlg.h"
#include "afxdialogex.h"
#include"CGameDlg.h"
#include"CNameDlg.h"
#include"CHelpDlg.h"
#include"CFileDlg.h"
#include"CABout.h"
#include <MMSystem.h>
#pragma comment (lib,"Winmm.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CBejeweledDlg 对话框



CBejeweledDlg::CBejeweledDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CBEJEWELED_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBejeweledDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBejeweledDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(CBEJEWELEDDLG_BUTTON1, &CBejeweledDlg::OnBnClickedButton1)
	ON_BN_CLICKED(CBEJEWELEDDLG_BUTTON2, &CBejeweledDlg::OnBnClickedButton2)
	ON_BN_CLICKED(CBEJEWELEDDLG_BUTTON3, &CBejeweledDlg::OnBnClickedButton3)
	ON_BN_CLICKED(CBEJEWELEDDLG_BUTTON4, &CBejeweledDlg::OnBnClickedButton4)
	ON_BN_CLICKED(CBEJEWELEDDLG_BUTTON5, &CBejeweledDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CBejeweledDlg 消息处理程序

BOOL CBejeweledDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBejeweledDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBejeweledDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	
	}
	else
	{
		CDialogEx::OnPaint();
	}
	//刘璇：设置背景
	CDC *cDC = this->GetDC();   //获得当前窗口的DC   
	GetClientRect(&m_client);   //获得窗口的尺寸
	CDC m_bgcDC; m_bgcDC.CreateCompatibleDC(NULL);
	CBitmap m_bgBitmap; m_bgBitmap.LoadBitmap(IDB_BITMAP2);
	m_bgcDC.SelectObject(&m_bgBitmap);
	cDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_bgcDC, 0, 0, SRCCOPY);
	ReleaseDC(cDC);           //释放DC   
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBejeweledDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBejeweledDlg::OnBnClickedButton1()//刘璇：开始游戏响应按钮，显示出游戏界面
{
	// TODO: 在此添加控件通知处理程序代码
	CGameDlg  *CGame = new CGameDlg;//实例化游戏界面
	CGame->Create(IDD_CGAMEDLG_DIALOG, this);//新建
	CGame->ShowWindow(SW_SHOW);//显示新建界面
	this->ShowWindow(SW_HIDE);//隐藏主界面

}


void CBejeweledDlg::OnBnClickedButton2()//姓名
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);//隐藏主界面
	CNameDlg  CName;// = new CGameDlg;//实例化游戏界面
	CName.DoModal();//显示模态对话框,模拟的好处是点击开始后原界面消失，关闭此界面后出现
	this->ShowWindow(SW_SHOW);//显示主界面
}


void CBejeweledDlg::OnBnClickedButton3()//排行榜
{
	// TODO: 在此添加控件通知处理程序代码
}


void CBejeweledDlg::OnBnClickedButton4()//帮助
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);//隐藏主界面
	CHelpDlg  CHelp;// = new CGameDlg;//实例化游戏界面
	CHelp.DoModal();//显示模态对话框,模拟的好处是点击开始后原界面消失，关闭此界面后出现
	this->ShowWindow(SW_SHOW);//显示主界面
}


void CBejeweledDlg::OnBnClickedButton5()//关于
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);//隐藏主界面
	CABout  CAbout;// = new CGameDlg;//实例化游戏界面
	CAbout.DoModal();//显示模态对话框,模拟的好处是点击开始后原界面消失，关闭此界面后出现
	this->ShowWindow(SW_SHOW);//显示主界面
}
