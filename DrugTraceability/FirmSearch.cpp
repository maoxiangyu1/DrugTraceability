// FirmSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "FirmSearch.h"
#include "afxdialogex.h"


// CFirmSearch 对话框

IMPLEMENT_DYNAMIC(CFirmSearch, CDialogEx)

CFirmSearch::CFirmSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FIRMSEARCK_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CFirmSearch::~CFirmSearch()
{
}

void CFirmSearch::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CFirmSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFirmSearch, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFirmSearch, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IFirmSearch 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {B17212ED-2B9E-40FD-9580-259929E8E823}
static const IID IID_IFirmSearch =
{ 0xB17212ED, 0x2B9E, 0x40FD, { 0x95, 0x80, 0x25, 0x99, 0x29, 0xE8, 0xE8, 0x23 } };

BEGIN_INTERFACE_MAP(CFirmSearch, CDialogEx)
	INTERFACE_PART(CFirmSearch, IID_IFirmSearch, Dispatch)
END_INTERFACE_MAP()


// CFirmSearch 消息处理程序
