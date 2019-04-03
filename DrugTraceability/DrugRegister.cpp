// DrugRegister.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "DrugRegister.h"
#include "afxdialogex.h"


// CDrugRegister 对话框

IMPLEMENT_DYNAMIC(CDrugRegister, CDialogEx)

CDrugRegister::CDrugRegister(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DURGREGISTER_DIALOG, pParent)
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

// {CDEFBA67-E47D-4CBD-8042-E712C4AB4DE1}
static const IID IID_IDrugRegister =
{ 0xCDEFBA67, 0xE47D, 0x4CBD, { 0x80, 0x42, 0xE7, 0x12, 0xC4, 0xAB, 0x4D, 0xE1 } };

BEGIN_INTERFACE_MAP(CDrugRegister, CDialogEx)
	INTERFACE_PART(CDrugRegister, IID_IDrugRegister, Dispatch)
END_INTERFACE_MAP()


// CDrugRegister 消息处理程序
