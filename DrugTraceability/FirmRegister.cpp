// FirmRegister.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "FirmRegister.h"
#include "afxdialogex.h"


// CFirmRegister 对话框

IMPLEMENT_DYNAMIC(CFirmRegister, CDialogEx)

CFirmRegister::CFirmRegister(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REGISTERFIRM_DIALOG, pParent)
	, Name(_T(""))
	, LeaderName(_T(""))
	, Address(_T(""))
	, Tel(_T(""))
	, Deadline(0)
	, Type(_T(""))
	, Info(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CFirmRegister::~CFirmRegister()
{
}

void CFirmRegister::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CFirmRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Name);
	DDX_Text(pDX, IDC_EDIT2, LeaderName);
	DDX_Text(pDX, IDC_EDIT3, Address);
	DDX_Text(pDX, IDC_EDIT4, Tel);
	DDV_MaxChars(pDX, Tel, 11);
	//  DDX_Text(pDX, IDC_EDIT5, Deadline);
	DDX_CBString(pDX, IDC_COMBO5, Type);
	DDX_Text(pDX, IDC_EDIT5, Deadline);
	DDV_MinMaxInt(pDX, Deadline, 0, 50);
	DDX_Text(pDX, IDC_EDIT6, Info);
}


BEGIN_MESSAGE_MAP(CFirmRegister, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFirmRegister::OnBnClickedOk)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFirmRegister, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IFirmRegister 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {1C190B01-3EE2-426F-B5B5-25C0DD39271C}
static const IID IID_IFirmRegister =
{ 0x1C190B01, 0x3EE2, 0x426F, { 0xB5, 0xB5, 0x25, 0xC0, 0xDD, 0x39, 0x27, 0x1C } };

BEGIN_INTERFACE_MAP(CFirmRegister, CDialogEx)
	INTERFACE_PART(CFirmRegister, IID_IFirmRegister, Dispatch)
END_INTERFACE_MAP()


// CFirmRegister 消息处理程序


void CFirmRegister::OnBnClickedOk()//注册
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (Name == "" || LeaderName == "" || Address == "" || Tel == "" || Info == "" || Type == ""||Deadline==0)
	{
		AfxMessageBox("公司信息不完整！");
		return;
	}
	CString s;
	DONGLE_HANDLE hDongle;
	int dwRet[6] = { 0 }, nCount;
	Firm firm;
	CString HID;
	char AdminPin[] = "FFFFFFFFFFFFFFFF";
	if (Dongle_Enum(NULL, &nCount) != DONGLE_SUCCESS || nCount != 2)
	{	
		AfxMessageBox("连接待写入设备失败！");
		return;
	}	
	dwRet[0] = Dongle_Open(&hDongle, 1);
	if (hDongle == m_admin->m_main->hDongle)
	{
		dwRet[0] = Dongle_Open(&hDongle, 0);
	}
	int p = 255;
	if (Dongle_VerifyPIN(hDongle, FLAG_ADMINPIN, AdminPin, &p) != DONGLE_SUCCESS)
	{
		AfxMessageBox("待写入设备无法识别！");
		return;
	}
	pDongleInfo = (DONGLE_INFO *)malloc(nCount * sizeof(DONGLE_INFO));
	dwRet[0] = Dongle_Enum(pDongleInfo, &nCount);
	if (Type == "生产商")
	{
		firm.FirmType = 2;
		dwRet[5] = Dongle_SetUserID(hDongle, 0x11111111);
	}
	if (Type == "中转站")
	{
		firm.FirmType = 3;
		dwRet[5] = Dongle_SetUserID(hDongle, 0x22222222);
	}
	if (Type == "药店")
	{
		firm.FirmType = 4;
		dwRet[5] = Dongle_SetUserID(hDongle, 0x33333333);
	}
	strcpy(firm.Address, Address);
	firm.Deadline = Deadline;
	strcpy(firm.Info, Info);
	strcpy(firm.LeaderName, LeaderName);
	strcpy(firm.Name, Name);
	strcpy(firm.Tel, Tel);
	CTime t=GetCurrentTime();
	s = t.Format("%Y-%m-%d");
	strcpy(firm.StartTime, s);
	
	for (int i = 0; i < 8; i++)
	{
		s.Format("%02X", pDongleInfo[1].m_HID[i]);
		HID = HID + s;
	}
	if (HID == m_admin->m_main->HID)
	{
		HID = "";
		for (int i = 0; i < 8; i++)
		{
			s.Format("%02X", pDongleInfo[0].m_HID[i]);
			HID = HID + s;
		}
	}
	strcpy(firm.FirmID, HID);
	GetDlgItem(IDC_STATIC23)->SetWindowText("开始写入身份信息！请勿拔出USB身份！");
	int size;
	BYTE sizebyte[4];
	BYTE buffer[4076];
	BYTE pHashMD5[16];
	size = sizeof(firm);
	memcpy(sizebyte, &size, 4);
	memcpy(buffer, &firm, sizeof(firm));
	dwRet[1] = Dongle_WriteData(hDongle, 0, sizebyte, 4);
	dwRet[2] = Dongle_WriteData(hDongle, 4, buffer, 4076);
	dwRet[3] = Dongle_HASH(hDongle, FLAG_HASH_MD5, buffer, 4076, pHashMD5);
	dwRet[4] = Dongle_WriteData(hDongle, 4080, pHashMD5, 16);
	for (int j = 0; j < 6; j++)
	{
		if (dwRet[j] != 0)
		{
			AfxMessageBox("写入身份信息出错，请重新写入！");
			GetDlgItem(IDC_STATIC23)->SetWindowText("写入身份信息出错，请重新写入！");
			return;
		}
	}

	GetDlgItem(IDC_STATIC23)->SetWindowText("开始写入数据库信息！");
	
	CString sql;
	sql.Format("insert into Firm values('%s','%s','%s','%s','%s','%s','%s',%d,%d);"
		, firm.FirmID, Name, Address, LeaderName, Info, firm.Tel,firm.StartTime, firm.Deadline, firm.FirmType);
	if (pDB->Execute(sql) != TRUE)
	{
		AfxMessageBox("公司注册失败！");
		return;
	}
	AfxMessageBox("公司注册成功！");
	CDialogEx::OnOK();
}


BOOL CFirmRegister::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO:  在此添加额外的初始化
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


void CFirmRegister::OnDestroy()
{
	CDialogEx::OnDestroy();
	pDB->Close();
	free(pDB);
	free(pDongleInfo);
	// TODO: 在此处添加消息处理程序代码
}
