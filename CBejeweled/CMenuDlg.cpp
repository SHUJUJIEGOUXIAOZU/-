// CMenuDlg.cpp: 实现文件
//

#include "pch.h"
#include "CBejeweled.h"
#include "CMenuDlg.h"
#include "CSetDlg.h"
#include "afxdialogex.h"
#include"CBejeweledDlg.h"
#include"CGameDlg.h"
// CMenuDlg 对话框

IMPLEMENT_DYNAMIC(CMenuDlg, CDialogEx)

CMenuDlg::CMenuDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CMENUDLG_DIALOG, pParent)
{

}

CMenuDlg::~CMenuDlg()
{
}

void CMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMenuDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMenuDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMenuDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMenuDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMenuDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMenuDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMenuDlg 消息处理程序

void CMenuDlg::OnBnClickedButton1()//返回主菜单
{
	// TODO: 在此添加控件通知处理程序代码
	CBejeweledDlg * CBeieweled = new CBejeweledDlg;
	CBeieweled->Create(IDD_CBEJEWELED_DIALOG, AfxGetMainWnd());
	CBeieweled->ShowWindow(SW_SHOW);
	this->ShowWindow(SW_HIDE);
}


void CMenuDlg::OnBnClickedButton2()//返回游戏
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(IDCANCEL);
}


void CMenuDlg::OnBnClickedButton3()//重新开始
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(3);
}


void CMenuDlg::OnBnClickedButton4()//设置游戏
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);//隐藏主界面
	CSetDlg* CSet= new CSetDlg;
	CSet->Create(IDD_CSETDLG_DIALOG, this);
	CSet->ShowWindow(SW_SHOW);
	this->ShowWindow(SW_SHOW);//显示主界面
}


void CMenuDlg::OnBnClickedButton5()//退出游戏
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}
