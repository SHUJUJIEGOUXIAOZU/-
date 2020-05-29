// ChioceDlg.cpp: 实现文件
//

#include "pch.h"
#include "CBejeweled.h"
#include "ChioceDlg.h"

#include "afxdialogex.h"


// ChioceDlg 对话框

IMPLEMENT_DYNAMIC(ChioceDlg, CDialogEx)

ChioceDlg::ChioceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MENU_DIALOG, pParent)
{

}

ChioceDlg::~ChioceDlg()
{
}

void ChioceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChioceDlg, CDialogEx)
	ON_BN_CLICKED(MENU_BUTTON1, &ChioceDlg::OnBnClickedButton1)
	ON_BN_CLICKED(MENU_BUTTON2, &ChioceDlg::OnBnClickedButton2)
	ON_BN_CLICKED(MENU_BUTTON3, &ChioceDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// ChioceDlg 消息处理程序


void ChioceDlg::OnBnClickedButton1()//困难
{
	// TODO: 在此添加控件通知处理程序代码
	Ch = 3;
	EndDialog(IDCANCEL);
}


void ChioceDlg::OnBnClickedButton2()//中级
{
	// TODO: 在此添加控件通知处理程序代码
	Ch=2;
	EndDialog(IDCANCEL);
}


void ChioceDlg::OnBnClickedButton3()//简单
{
	// TODO: 在此添加控件通知处理程序代码
    Ch=1;
	EndDialog(IDCANCEL);
}
