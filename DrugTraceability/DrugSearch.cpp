// DrugSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "DrugSearch.h"
#include "afxdialogex.h"


// CDrugSearch 对话框

IMPLEMENT_DYNAMIC(CDrugSearch, CDialogEx)

CDrugSearch::CDrugSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DRUGSEARCH_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CDrugSearch::~CDrugSearch()
{
}

void CDrugSearch::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CDrugSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDrugSearch, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDrugSearch, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IDrugSearch 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {528AD457-9CDB-44C0-8763-58B907BE6EA0}
static const IID IID_IDrugSearch =
{ 0x528AD457, 0x9CDB, 0x44C0, { 0x87, 0x63, 0x58, 0xB9, 0x7, 0xBE, 0x6E, 0xA0 } };

BEGIN_INTERFACE_MAP(CDrugSearch, CDialogEx)
	INTERFACE_PART(CDrugSearch, IID_IDrugSearch, Dispatch)
END_INTERFACE_MAP()


// CDrugSearch 消息处理程序
