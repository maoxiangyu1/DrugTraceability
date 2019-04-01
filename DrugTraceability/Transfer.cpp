// Transfer.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Transfer.h"
#include "afxdialogex.h"


// CTransfer 对话框

IMPLEMENT_DYNAMIC(CTransfer, CDialogEx)

CTransfer::CTransfer(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TRANSFER_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CTransfer::~CTransfer()
{
}

void CTransfer::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CTransfer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTransfer, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTransfer, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ITransfer 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {DF73781C-A3E1-43AA-A03E-AC67773F6476}
static const IID IID_ITransfer =
{ 0xDF73781C, 0xA3E1, 0x43AA, { 0xA0, 0x3E, 0xAC, 0x67, 0x77, 0x3F, 0x64, 0x76 } };

BEGIN_INTERFACE_MAP(CTransfer, CDialogEx)
	INTERFACE_PART(CTransfer, IID_ITransfer, Dispatch)
END_INTERFACE_MAP()


// CTransfer 消息处理程序
