// CSetDlg.cpp: 实现文件
//

#include "pch.h"
#include "CBejeweled.h"
#include "CSetDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "CMusicDlg.h"
#include "CTheme.h"


// CSetDlg 对话框

IMPLEMENT_DYNAMIC(CSetDlg, CDialogEx)

CSetDlg::CSetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CSETDLG_DIALOG, pParent)
{

}

CSetDlg::~CSetDlg()
{
}

void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CSETDLG_TAB, CSetDlg_Tab);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_CSETDLG_TAB, &CSetDlg::OnTcnSelchangeCsetdlgTab)
	ON_BN_CLICKED(IDC_BUTTON1, &CSetDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSetDlg 消息处理程序
BOOL CSetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//以下代码用于在CSetDlg设置中将tab控件的界面联系在一起
	CSetDlg_Tab.InsertItem(0, _T("音效设置"));
	CSetDlg_Tab.InsertItem(1, _T("背景设置"));
	//创建两个对话框
	music.Create(IDD_CMUSICDLG_DIALOG, &CSetDlg_Tab);
	theme.Create(IDD_CThEMEDLG_DIALOG, &CSetDlg_Tab);
	//设定在Tab中 的显示位置
	CRect rc;
	CSetDlg_Tab.GetClientRect(&rc);
	CRect rcTabItem;
	CSetDlg_Tab.GetItemRect(0, rcTabItem);
	rc.top += rcTabItem.Height() + 4;
	rc.left += 4;
	rc.bottom -= 4;

	music.MoveWindow(&rc);
	theme.MoveWindow(&rc);

	//默认标签选中
	music.ShowWindow(SW_SHOW);
	theme.ShowWindow(SW_HIDE);
	CSetDlg_Tab.SetCurFocus(0);

	return TRUE;
}

void CSetDlg::OnTcnSelchangeCsetdlgTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码

	switch (CSetDlg_Tab.GetCurSel())
	{
	case 0:
		music.ShowWindow(SW_SHOW);
		theme.ShowWindow(SW_HIDE);
		music.SetFocus();
		break;
	case 1:
		theme.ShowWindow(SW_SHOW);
		music.ShowWindow(SW_HIDE);
		theme.SetFocus();
		break;
	default:
		break;
	}
	*pResult = 0;
}


void CSetDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	DestroyWindow();
}
