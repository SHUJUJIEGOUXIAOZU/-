// CMusicDlg.cpp: 实现文件
//

#include "pch.h"
#include "CBejeweled.h"
#include "CMusicDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "string"
#include <MMSystem.h>
#pragma comment (lib,"Winmm.lib")

// CMusicDlg 对话框

IMPLEMENT_DYNAMIC(CMusicDlg, CDialogEx)

CMusicDlg::CMusicDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CMUSICDLG_DIALOG, pParent)
{

}

CMusicDlg::~CMusicDlg()
{
}

void CMusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, Music_CHECK1);
	DDX_Control(pDX, IDC_CHECK2, Music_CHECK2);
	DDX_Control(pDX, IDC_RADIO1, Music_RADIO1);
	DDX_Control(pDX, IDC_RADIO2, Music_RADIO2);
	DDX_Control(pDX, IDC_RADIO3, Music_RADIO3);
	DDX_Control(pDX, IDC_BUTTON1, Music_Button1);
	DDX_Control(pDX, IDC_EDIT1, Music_Edit1);
}


BEGIN_MESSAGE_MAP(CMusicDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CMusicDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CMusicDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_RADIO1, &CMusicDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMusicDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CMusicDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_BUTTON1, &CMusicDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMusicDlg 消息处理程序
BOOL CMusicDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//自定义背景选项暂不可见
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);

	//默认选择
	Music_CHECK1.SetCheck(1);
	Music_CHECK2.SetCheck(1);
	Music_RADIO1.SetCheck(1);

	return TRUE;
}

void CMusicDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (Music_CHECK1.GetCheck() == 1)
	{
		PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
		GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
	}
	else
	{
		PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
		GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
	}

}

void CMusicDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (Music_CHECK2.GetCheck() == 1)
	{
		PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	}

}

void CMusicDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);

	if (Music_RADIO1.GetCheck() == 1)
	{
		PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
		PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	}
}

void CMusicDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);

	if (Music_RADIO2.GetCheck() == 1)
	{
		PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
		PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	}
}


void CMusicDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
}


void CMusicDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog open_img(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("音频文件(*.mav)|*.mav|所有文件(*.*)|*.*||"), NULL);//指定要打开的文件类型
	if (open_img.DoModal() == IDOK)
	{
		CString img_select;
		img_select = open_img.GetPathName();
		SetDlgItemText(IDC_EDIT1, img_select);//img_select为选择的文件的路径，IDC_EDIT1为edit控件名称
	}

	CString path = NULL;
	Music_Edit1.GetWindowText(path);

	if (Music_RADIO3.GetCheck() == 1)
	{
		PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
		PlaySound(path, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
}
