// Drugstore.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Drugstore.h"
#include "afxdialogex.h"


// CDrugstore 对话框

IMPLEMENT_DYNAMIC(CDrugstore, CDialogEx)

CDrugstore::CDrugstore(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DRUGSTORE_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CDrugstore::~CDrugstore()
{
}

void CDrugstore::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CDrugstore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDrugstore, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDrugstore, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IDrugstore 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {A446F9FB-2699-4887-97B4-71C93C938839}
static const IID IID_IDrugstore =
{ 0xA446F9FB, 0x2699, 0x4887, { 0x97, 0xB4, 0x71, 0xC9, 0x3C, 0x93, 0x88, 0x39 } };

BEGIN_INTERFACE_MAP(CDrugstore, CDialogEx)
	INTERFACE_PART(CDrugstore, IID_IDrugstore, Dispatch)
END_INTERFACE_MAP()


// CDrugstore 消息处理程序
