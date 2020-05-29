// CNameDlg.cpp: 实现文件
//

#include "pch.h"
#include "CBejeweled.h"
#include "CNameDlg.h"
#include "afxdialogex.h"


// CNameDlg 对话框

IMPLEMENT_DYNAMIC(CNameDlg, CDialogEx)

CNameDlg::CNameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CNAMEDLG_DIALOG, pParent)
{

}

CNameDlg::~CNameDlg()
{
}

void CNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNameDlg, CDialogEx)
END_MESSAGE_MAP()


// CNameDlg 消息处理程序
