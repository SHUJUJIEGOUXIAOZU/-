// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "CBejeweled.h"
#include "CGameDlg.h"
#include"CMenuDlg.h"
#include "afxdialogex.h"
#include"Resource.h"
#include"CGameLogic.h"
#include"ChioceDlg.h"
// CGameDlg 对话框

#define GAME_X 100
#define GAME_Y 100
#define	WIDTH 880 //屏幕宽
#define HEIGHT 700 //屏幕高
#define PIC_WIDTH 50 //图片元素宽
#define PIC_HEIGHT 50 //图片元素高
IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CGAMEDLG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_rtGame.top = GAME_Y;
	m_rtGame.left = GAME_X;
	m_rtGame.bottom = m_rtGame.top + PIC_HEIGHT * GAME_ROW;
	m_rtGame.right = m_rtGame.left + PIC_WIDTH * GAME_COL;

}


CGameDlg::~CGameDlg()
{
	m_dcBg.DeleteDC();
	m_dcMem.DeleteDC();
	m_dcElem.DeleteDC();
	m_dcMask.DeleteDC();

}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}
void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, WIDTH, HEIGHT, &m_dcMem, 0, 0, SRCCOPY);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(CGAMEDLG_BUTTON1, &CGameDlg::OnBnClickedButton1)
	ON_BN_CLICKED(CGAMEDLG_BUTTON2, &CGameDlg::OnBnClickedButton2)
	ON_BN_CLICKED(CGAMEDLG_BUTTON3, &CGameDlg::OnBnClickedButton3)
	ON_BN_CLICKED(CGAMEDLG_BUTTON4, &CGameDlg::OnBnClickedButton4)
END_MESSAGE_MAP()

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	this->ModifyStyleEx(0, WS_EX_APPWINDOW);//显示任务栏
	Init();
	InitWnd();
	m_GameLogic.BuildMap();
	DrawGameArea();
	// TODO:  在此添加额外的初始化
	SetTimer(1, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void CGameDlg::InitWnd()
{
	SetWindowPos(NULL, 0, 0, WIDTH, HEIGHT, SWP_NOMOVE);
	CClientDC dc(this);
	CBitmap bmpBg;
	bmpBg.LoadBitmapW(IDB_BITMAP3);
	m_dcBg.CreateCompatibleDC(&dc);
	m_dcBg.SelectObject(bmpBg);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, WIDTH, HEIGHT);
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMem.SelectObject(bmpMem);
	m_dcMem.BitBlt(0, 0, WIDTH, HEIGHT, &m_dcBg, 0, 0, SRCCOPY);
}
void CGameDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//if (!m_bPlaying)
		//return CDialogEx::OnLButtonDown(nFlags, point);
	//判断点击坐标是否超出游戏矩形区域
	if (!m_rtGame.PtInRect(point))
	{
		return CDialogEx::OnLButtonDown(nFlags, point);
	}
	//由点击的坐标计算行列
	int nRow = (point.y - GAME_Y) / PIC_HEIGHT;
	int nCol = (point.x - GAME_X) / PIC_WIDTH;
	//获取图片元素
	PICELEM picElem = m_GameLogic.GetPicElem(nRow, nCol);
	if (m_bFirstElem)
		m_picElemFirst = picElem;
	
	else{
		m_picElemSecond = picElem;
		if (m_GameLogic.IsNeighbour(m_picElemFirst.nRow, m_picElemFirst.nCol, m_picElemSecond.nRow, m_picElemSecond.nCol))
		{
			m_GameLogic.ExChange(m_picElemFirst.nRow, m_picElemFirst.nCol, m_picElemSecond.nRow, m_picElemSecond.nCol);
			ChangeCartoon();
			if (m_GameLogic.ActionBefore(m_picElemFirst.nRow, m_picElemFirst.nCol, m_picElemSecond.nRow, m_picElemSecond.nCol))
			{
				while (m_GameLogic.ActionDo()) {
					m_GameLogic.ReFlash();
					DrawGameArea(); 
			}
			}
			else
			{
				//交换回来
				ChangeCartoon();
				m_GameLogic.ExChange(m_picElemFirst.nRow, m_picElemFirst.nCol, m_picElemSecond.nRow, m_picElemSecond.nCol);
			}

		}
	}
	m_bFirstElem = !m_bFirstElem;
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CGameDlg::DrawTip(PICELEM picElem) {
		CClientDC dc(this);
		CBrush brush(RGB(233, 43, 43));
		CRect rtTipFrame = GetElemRect(picElem);
		dc.FrameRect(rtTipFrame, &brush);
}

// 计算图片元素左上角坐标
void CGameDlg::GetElemLUxy(PICELEM picElem, int & nX, int & nY)
{
	nX = picElem.nCol*PIC_WIDTH + GAME_X;
	nY = picElem.nRow*PIC_HEIGHT + GAME_Y;
}

CRect CGameDlg::GetElemRect(PICELEM picElem)
{
	int nX = 0;
	int nY = 0;
	GetElemLUxy(picElem, nX, nY);
	return CRect(nX, nY, nX + PIC_WIDTH, nY + PIC_HEIGHT);
}

void CGameDlg::ChangeCartoon()
{
	int nFlag = 0;//定义一个标志
	PICELEM elemLU = m_picElemFirst;//定义左上图片
	PICELEM elemRD = m_picElemSecond;//定义右下图片元素
	if (m_picElemFirst.nRow == m_picElemSecond.nRow)//行相等横向交换
	{
		nFlag = 1;
		if (m_picElemFirst.nCol > m_picElemSecond.nCol)
		{
			elemRD = m_picElemFirst;
			elemLU = m_picElemSecond;
		}
	}
	if (m_picElemFirst.nCol == m_picElemSecond.nCol)//列相当，纵向交换
	{
		nFlag = 2;
		if (m_picElemFirst.nRow > m_picElemSecond.nRow)
		{
			elemRD = m_picElemFirst;
			elemLU = m_picElemSecond;
		}
	}
	//获取左上宝石的目的坐标
	int nLUWndX = 0;
	int nLUWndY = 0;
	GetElemLUxy(elemLU, nLUWndX, nLUWndY);
	//获取左上宝石的源坐标
	int nLUPicX = 0;
	int nLUPicY = elemLU.nPicNum*PIC_HEIGHT;
	//获取右下宝石的目的坐标
	int nRDWndX = 0;
	int nRDWndY = 0;
	GetElemLUxy(elemRD, nRDWndX, nRDWndY);
	//获取右下宝石的源坐标
	int nRDPicX = 0;
	int nRDPicY = elemRD.nPicNum*PIC_HEIGHT;

	int nNum = 0;//偏移次数
	while (nNum < 5)
	{
		nNum++;
		if (nFlag == 1)//横向
		{
			m_dcMem.BitBlt(nLUWndX, nLUWndY, PIC_WIDTH * 2, PIC_HEIGHT, &m_dcBg, nLUWndX, nLUWndY, SRCCOPY);

			m_dcMem.BitBlt((nLUWndX + nNum * MOVE_PIXEL), nLUWndY, PIC_WIDTH, PIC_HEIGHT, &m_dcMask, nLUPicX, nLUPicY, SRCPAINT);
			m_dcMem.BitBlt((nLUWndX + nNum * MOVE_PIXEL), nLUWndY, PIC_WIDTH, PIC_HEIGHT, &m_dcElem, nLUPicX, nLUPicY, SRCAND);

			m_dcMem.BitBlt((nRDWndX - nNum * MOVE_PIXEL), nRDWndY, PIC_WIDTH, PIC_HEIGHT, &m_dcMask, nRDPicX, nRDPicY, SRCPAINT);
			m_dcMem.BitBlt((nRDWndX - nNum * MOVE_PIXEL), nRDWndY, PIC_WIDTH, PIC_HEIGHT, &m_dcElem, nRDPicX, nRDPicY, SRCAND);
		}
		else
		{
			m_dcMem.BitBlt(nLUWndX, nLUWndY, PIC_WIDTH, PIC_HEIGHT * 2, &m_dcBg, nLUWndX, nLUWndY, SRCCOPY);

			m_dcMem.BitBlt(nLUWndX, (nLUWndY + nNum * MOVE_PIXEL), PIC_WIDTH, PIC_HEIGHT, &m_dcMask, nLUPicX, nLUPicY, SRCPAINT);
			m_dcMem.BitBlt(nLUWndX, (nLUWndY + nNum * MOVE_PIXEL), PIC_WIDTH, PIC_HEIGHT, &m_dcElem, nLUPicX, nLUPicY, SRCAND);

			m_dcMem.BitBlt(nRDWndX, (nRDWndY - nNum * MOVE_PIXEL), PIC_WIDTH, PIC_HEIGHT, &m_dcMask, nRDPicX, nRDPicY, SRCPAINT);
			m_dcMem.BitBlt(nRDWndX, (nRDWndY - nNum * MOVE_PIXEL), PIC_WIDTH, PIC_HEIGHT, &m_dcElem, nRDPicX, nRDPicY, SRCAND);
		}
		CRect rect = GetElemRect(elemLU) + GetElemRect(elemRD);
		InvalidateRect(&rect, false);
		UpdateWindow();
		Sleep(50);
	}
}


void CGameDlg::Restart()
{
	m_GameLogic.BuildMap();
	DrawGameArea();
	//初始化数据
}


void CGameDlg::DrawGameArea()
{
	//将m_dcMem游戏区域还原为背景图片
	m_dcMem.BitBlt(GAME_X, GAME_Y, PIC_WIDTH*GAME_COL, PIC_HEIGHT*GAME_ROW, &m_dcBg, GAME_X, GAME_Y, SRCCOPY);
	int nPicNum = -1;
	int nWndX = 0;
	int nWndY = 0;
	int nPicX = 0;
	int nPicY = 0;
	for (int i = 0; i < GAME_ROW; i++)
	{
		for (int j = 0; j < GAME_COL; j++)
		{
			nPicNum = m_GameLogic.GetPicNum(i, j);
			nWndX = GAME_X + PIC_WIDTH * j;
			nWndY = GAME_Y + PIC_HEIGHT * i;
			nPicY = nPicNum * PIC_HEIGHT;
			nPicX = 0;

			//背景与掩码相或
			m_dcMem.BitBlt(nWndX, nWndY, PIC_WIDTH, PIC_HEIGHT, &m_dcMask, nPicX, nPicY, SRCPAINT);
			//再与图片元素想与
			m_dcMem.BitBlt(nWndX, nWndY, PIC_WIDTH, PIC_HEIGHT, &m_dcElem, nPicX, nPicY, SRCAND);
		}
	}
	InvalidateRect(&m_rtGame, FALSE);
}

void CGameDlg::Init() {
	CClientDC dc(this);
	CBitmap bmpElem;
	bmpElem.LoadBitmap(IDB_BAOSHI);
	m_dcElem.CreateCompatibleDC(&dc);
	m_dcElem.SelectObject(bmpElem);
	CBitmap bmpMask;
	bmpMask.LoadBitmap(IDB_MASK);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(bmpMask);

	CBitmap bmpCache;
	bmpCache.CreateCompatibleBitmap(&dc, 256, 256);
	m_dcCache.CreateCompatibleDC(&dc);
	m_dcCache.SelectObject(bmpCache);
}


void CGameDlg::OnBnClickedButton1()//按钮1，菜单
{
	/*CMenuDlg * CMenu = new CMenuDlg;
	CMenu->Create(IDD_CMENUDLG_DIALOG, AfxGetMainWnd());
	CMenu->ShowWindow(SW_SHOW);
	this->DestroyWindow();//删除界面*/
	this->ShowWindow(SW_HIDE);//隐藏主界面
	CMenuDlg  CMenu;// = new CGameDlg;//实例化游戏界面
	int s=CMenu.DoModal();//显示模态对话框,模拟的好处是点击开始后原界面消失，关闭此界面后出现
	this->ShowWindow(SW_SHOW);//显示主界面
	if (s == 3) {
		Restart();
	}

}


void CGameDlg::OnBnClickedButton2()//按钮2，暂停
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(CGAMEDLG_BUTTON2)->GetWindowText(str);//获取按键的名字
	if (str == "暂停") {
		GetDlgItem(CGAMEDLG_BUTTON2)->SetWindowText(L"继续");
		GetDlgItem(IDC_STATIC)->ShowWindow(SW_SHOW);
	}
	else if (str == "继续") {
		GetDlgItem(CGAMEDLG_BUTTON2)->SetWindowText(L"暂停");
		GetDlgItem(IDC_STATIC)->ShowWindow(SW_HIDE);
	}
}


void CGameDlg::OnBnClickedButton3()//按钮3，提示
{
	// TODO: 在此添加控件通知处理程序代码
	m_GameLogic.Tip();
	DrawTip(m_GameLogic.m_aTip[0]);
	DrawTip(m_GameLogic.m_aTip[1]);
}



void CGameDlg::OnBnClickedButton4()//，休闲模式，选择难度
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);//隐藏主界面
	ChioceDlg  Chioce;// = new CGameDlg;//实例化游戏界面
	Chioce.DoModal();//显示模态对话框,模拟的好处是点击开始后原界面消失，关闭此界面后出现
	this->ShowWindow(SW_SHOW);//显示主界面
	if (Chioce.Ch == 1) {//简单
		;
	}
	else if (Chioce.Ch == 2) {//中级
		/*GAME_ROW = 9; //游戏行数
		GAME_COL = 9;//游戏列数
		ELEM_NUM = 4; //花色数量*/

	}
	else if (Chioce.Ch == 3) {//困难
       /*GAME_ROW = 10; //游戏行数
		GAME_COL = 10;//游戏列数
		ELEM_NUM = 5; //花色数量*/
	}
}
