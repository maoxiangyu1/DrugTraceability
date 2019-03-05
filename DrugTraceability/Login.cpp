// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Login.h"
#include "afxdialogex.h"


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
		return TRUE;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
