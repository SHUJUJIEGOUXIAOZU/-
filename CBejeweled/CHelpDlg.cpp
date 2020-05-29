// CHelpDlg.cpp: 实现文件
//

#include "pch.h"
#include "CBejeweled.h"
#include "CHelpDlg.h"
#include "afxdialogex.h"
#include"Resource.h"

// CHelpDlg 对话框

IMPLEMENT_DYNAMIC(CHelpDlg, CDialogEx)

CHelpDlg::CHelpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHelpDlg_DIALOG, pParent)
{

}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CHelpDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CHelpDlg 消息处理程序


void CHelpDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
