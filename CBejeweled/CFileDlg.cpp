// CFileDlg.cpp: 实现文件
//

#include "pch.h"
#include "CBejeweled.h"
#include "CFileDlg.h"
#include "afxdialogex.h"


// CFileDlg 对话框

IMPLEMENT_DYNAMIC(CFileDlg, CDialogEx)

CFileDlg::CFileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CFILEDLG_DIALOG, pParent)
{

}

CFileDlg::~CFileDlg()
{
}

void CFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFileDlg, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CFileDlg::OnLvnItemchangedList2)
END_MESSAGE_MAP()


// CFileDlg 消息处理程序


void CFileDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
