// CTheme.cpp: 实现文件
//

#include "pch.h"
#include "CBejeweled.h"
#include "CTheme.h"
#include "afxdialogex.h"


// CTheme 对话框

IMPLEMENT_DYNAMIC(CTheme, CDialogEx)

CTheme::CTheme(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CThEMEDLG_DIALOG, pParent)
{

}

CTheme::~CTheme()
{
}

void CTheme::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, Theme_RADIO1);
	DDX_Control(pDX, IDC_RADIO2, Theme_RADIO2);
	DDX_Control(pDX, IDC_RADIO3, Theme_RADIO3);
	DDX_Control(pDX, IDC_RADIO4, Theme_RADIO4);
	DDX_Control(pDX, IDC_RADIO5, Theme_RADIO5);
	DDX_Control(pDX, IDC_BUTTON1, Theme_BUTTON1);
	DDX_Control(pDX, IDC_BUTTON3, Theme_BUTTON2);
	DDX_Control(pDX, IDC_EDIT1, Theme_EDIT1);
	DDX_Control(pDX, IDC_EDIT2, Theme_EDIT1);
}


BEGIN_MESSAGE_MAP(CTheme, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTheme::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CTheme::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_RADIO2, &CTheme::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &CTheme::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CTheme 消息处理程序
BOOL CTheme::OnInitDialog()
{
	CDialog::OnInitDialog();

	//默认选项
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);

	Theme_RADIO1.SetCheck(1);
	Theme_RADIO3.SetCheck(1);

	return TRUE;
}


void CTheme::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog open_img(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("图片文件(*.jpg)|*.jpg|所有文件(*.*)|*.*||"), NULL);//指定要打开的文件类型
	if (open_img.DoModal() == IDOK)
	{
		CString img_select;
		img_select = open_img.GetPathName();
		SetDlgItemText(IDC_EDIT1, img_select);//img_select为选择的文件的路径，IDC_EDIT1为edit控件名称
	}
}


void CTheme::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog open_img(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("图片文件(*.jpg)|*.jpg|所有文件(*.*)|*.*||"), NULL);//指定要打开的文件类型
	if (open_img.DoModal() == IDOK)
	{
		CString img_select;
		img_select = open_img.GetPathName();
		SetDlgItemText(IDC_EDIT1, img_select);//img_select为选择的文件的路径，IDC_EDIT1为edit控件名称
	}
}

void CTheme::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (Theme_RADIO2.GetCheck() == 1)
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	}
}

void CTheme::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (Theme_RADIO1.GetCheck() == 1)
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	}
}
