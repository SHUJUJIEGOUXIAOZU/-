// CABout.cpp: 实现文件
//

#include "pch.h"
#include "CBejeweled.h"
#include "CABout.h"
#include "afxdialogex.h"


// CABout 对话框

IMPLEMENT_DYNAMIC(CABout, CDialogEx)

CABout::CABout(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CABOUTDLG_DIALOG, pParent)
{

}

CABout::~CABout()
{
}

void CABout::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CABout, CDialogEx)
END_MESSAGE_MAP()


// CABout 消息处理程序
