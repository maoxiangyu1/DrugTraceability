// Producer.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Producer.h"
#include "afxdialogex.h"


// CProducer 对话框

IMPLEMENT_DYNAMIC(CProducer, CDialogEx)

CProducer::CProducer(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PRODUCER_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CProducer::~CProducer()
{
}

void CProducer::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CProducer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProducer, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProducer, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IProducer 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {6E49755E-9B9A-4E2D-842A-8A38773E1791}
static const IID IID_IProducer =
{ 0x6E49755E, 0x9B9A, 0x4E2D, { 0x84, 0x2A, 0x8A, 0x38, 0x77, 0x3E, 0x17, 0x91 } };

BEGIN_INTERFACE_MAP(CProducer, CDialogEx)
	INTERFACE_PART(CProducer, IID_IProducer, Dispatch)
END_INTERFACE_MAP()


// CProducer 消息处理程序
