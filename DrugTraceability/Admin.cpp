// Admin.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Admin.h"
#include "afxdialogex.h"


// CAdmin 对话框

IMPLEMENT_DYNAMIC(CAdmin, CDialogEx)

CAdmin::CAdmin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADMIN_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CAdmin::~CAdmin()
{
}

void CAdmin::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CAdmin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAdmin, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAdmin, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IAdmin 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {2776E4F6-5C7B-45F7-8AFD-34FFCB6137EC}
static const IID IID_IAdmin =
{ 0x2776E4F6, 0x5C7B, 0x45F7, { 0x8A, 0xFD, 0x34, 0xFF, 0xCB, 0x61, 0x37, 0xEC } };

BEGIN_INTERFACE_MAP(CAdmin, CDialogEx)
	INTERFACE_PART(CAdmin, IID_IAdmin, Dispatch)
END_INTERFACE_MAP()


// CAdmin 消息处理程序
