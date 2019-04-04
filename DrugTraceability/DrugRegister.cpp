// DrugRegister.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "DrugRegister.h"
#include "afxdialogex.h"


// CDrugRegister 对话框

IMPLEMENT_DYNAMIC(CDrugRegister, CDialogEx)

CDrugRegister::CDrugRegister(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REGISTERDURG_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CDrugRegister::~CDrugRegister()
{
}

void CDrugRegister::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CDrugRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDrugRegister, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDrugRegister, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IDrugRegister 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {D569E1A0-D48F-48FE-B4CA-06961C8F9CAC}
static const IID IID_IDrugRegister =
{ 0xD569E1A0, 0xD48F, 0x48FE, { 0xB4, 0xCA, 0x6, 0x96, 0x1C, 0x8F, 0x9C, 0xAC } };

BEGIN_INTERFACE_MAP(CDrugRegister, CDialogEx)
	INTERFACE_PART(CDrugRegister, IID_IDrugRegister, Dispatch)
END_INTERFACE_MAP()


// CDrugRegister 消息处理程序
