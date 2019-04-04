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
	, DID(_T(""))
	, DName(_T(""))
	, Component(_T(""))
	, Effect(_T(""))
	, Deadline(0)
	, Info(_T(""))
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
	//  DDX_Text(pDX, IDC_EDIT1, DID);
	DDX_Text(pDX, IDC_EDIT2, DName);
	DDX_Text(pDX, IDC_EDIT3, Component);
	DDX_Text(pDX, IDC_EDIT5, Effect);
	DDX_Text(pDX, IDC_EDIT6, Deadline);
	DDV_MinMaxInt(pDX, Deadline, 0, 999);
	DDX_Text(pDX, IDC_EDIT7, Info);
	DDX_Text(pDX, IDC_EDIT1, DID);
	DDV_MaxChars(pDX, DID, 14);
}


BEGIN_MESSAGE_MAP(CDrugRegister, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDrugRegister::OnBnClickedOk)
	ON_WM_DESTROY()
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


BOOL CDrugRegister::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	CString s;
	s = "File Name=linkDB.udl";
	pDB = new CADODatabase;
	if (!pDB->Open(s))
	{
		AfxMessageBox("数据库链接失败！单击退出！");
		this->EndDialog(0);
		return TRUE;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDrugRegister::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (DID == "" || DName == "" || Component == "" || Effect == "" || Info == "" || Deadline == 0)
	{
		AfxMessageBox("药品信息不完整！");
		return;
	}
	CString sql,s;
	CTime t = GetCurrentTime();
	s = t.Format("%Y-%m-%d");
	sql.Format("insert into Drug values('%s','%s','%s','%s','%s','%s',%d);"
		, DID, DName, Component, Effect, s, Info, Deadline);
	if (pDB->Execute(sql) != TRUE)
	{
		AfxMessageBox("药品注册失败！");
		return;
	}
	AfxMessageBox("药品注册成功！");
	CDialogEx::OnOK();
}


void CDrugRegister::OnDestroy()
{
	CDialogEx::OnDestroy();
	CDialogEx::OnDestroy();
	pDB->Close();
	free(pDB);
	// TODO: 在此处添加消息处理程序代码
}
