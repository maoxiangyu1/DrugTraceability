// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Admin.h"
#include "Producer.h"
#include "Transfer.h"
#include "Drugstore.h"
// CLogin 对话框

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
{

	EnableAutomation();

}

CLogin::~CLogin()
{
}

void CLogin::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLogin::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLogin::OnBnClickedButton2)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLogin, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ILogin 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {A44C3932-9783-44BB-B2DB-EEA2202C6DF7}
static const IID IID_ILogin =
{ 0xA44C3932, 0x9783, 0x44BB, { 0xB2, 0xDB, 0xEE, 0xA2, 0x20, 0x2C, 0x6D, 0xF7 } };

BEGIN_INTERFACE_MAP(CLogin, CDialogEx)
	INTERFACE_PART(CLogin, IID_ILogin, Dispatch)
END_INTERFACE_MAP()


// CLogin 消息处理程序


BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	CString s;
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	//===========
	hDongle = NULL;
	int nCount;
	int dwRet = Dongle_Enum(NULL, &nCount);//枚举锁的数量
	if (dwRet != DONGLE_SUCCESS && nCount != 1)
	{
		GetDlgItem(IDC_STATICW)->SetWindowTextA("请插入USB身份校验！");
		GetDlgItem(IDC_BUTTON1)->SetWindowTextA("重试");
		return TRUE;
	} 

	//显示身份信息============
	pDongleInfo = (DONGLE_INFO *)malloc(sizeof(DONGLE_INFO));
	dwRet = Dongle_Enum(pDongleInfo, &nCount);//获取加密锁的相关信息
	if (pDongleInfo->m_UserID == 0xFFFFFFFF)    //药监局
	{
		GetDlgItem(IDC_BUTTON1)->SetWindowTextA("登入");
		return TRUE;
	}
	if (pDongleInfo->m_UserID == 0x11111111)    //生产商
	{
		GetDlgItem(IDC_BUTTON1)->SetWindowTextA("登入");
		return TRUE;
	}
	if (pDongleInfo->m_UserID == 0x22222222)   //中转站
	{
		GetDlgItem(IDC_BUTTON1)->SetWindowTextA("登入");
		return TRUE;
	}
	if (pDongleInfo->m_UserID == 0x33333333)    //药店
	{
		GetDlgItem(IDC_BUTTON1)->SetWindowTextA("登入");
		return TRUE;
	}
	AfxMessageBox("无确定您的身份信息！");
	//=========
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CLogin::OnBnClickedButton2() //退出按钮
{
	OnCancel();
	// TODO: 在此添加控件通知处理程序代码
}

void CLogin::OnBnClickedButton1() //登录按钮
{
	CString s;
	GetDlgItemText(IDC_BUTTON1, s);
	if (s == "重试")
	{
		OnInitDialog();
		UpdateWindow();
		GetDlgItem(IDC_STATICW)->SetWindowTextA("未检测到USB！");
		return;
	}
	if (pDongleInfo->m_UserID == 0xFFFFFFFF) //药监局
	{
		CAdmin Dlg;
		Dlg.m_main = this;
		Dlg.DoModal();
		return;
	}
	if (pDongleInfo->m_UserID == 0x11111111) //生产商
	{
		CProducer Dlg;
		Dlg.m_main = this;
		Dlg.DoModal();
		return;
	}
	if (pDongleInfo->m_UserID == 0x22222222) //中转站
	{
		CTransfer Dlg;
		Dlg.m_main = this;
		Dlg.DoModal();
		return;
	}
	if (pDongleInfo->m_UserID == 0x33333333) //药店
	{
		CDrugstore Dlg;
		Dlg.m_main = this;
		Dlg.DoModal();
		return;
	}
	// TODO: 在此添加控件通知处理程序代码
}
 