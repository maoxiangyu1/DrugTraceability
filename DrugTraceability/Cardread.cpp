// Cardread.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Cardread.h"
#include "afxdialogex.h"
#include "mwrf32.h"

// CCardread 对话框

IMPLEMENT_DYNAMIC(CCardread, CDialogEx)

CCardread::CCardread(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ICREAD_DIALOG, pParent)
	, Buffer(_T(""))
	, m_did(_T(""))
	, Dname(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CCardread::~CCardread()
{
}

void CCardread::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CCardread::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Buffer);
	DDX_Text(pDX, IDC_EDIT2, m_did);
	DDX_Text(pDX, IDC_EDIT3, Dname);
}


BEGIN_MESSAGE_MAP(CCardread, CDialogEx)
	ON_BN_CLICKED(IDOK2, &CCardread::OnBnClickedOk2)
	ON_BN_CLICKED(IDOK, &CCardread::OnBnClickedOk)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCardread, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ICardread 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {905F04F9-59DE-4B51-B416-8BF8FAA53E13}
static const IID IID_ICardread =
{ 0x905F04F9, 0x59DE, 0x4B51, { 0xB4, 0x16, 0x8B, 0xF8, 0xFA, 0xA5, 0x3E, 0x13 } };

BEGIN_INTERFACE_MAP(CCardread, CDialogEx)
	INTERFACE_PART(CCardread, IID_ICardread, Dispatch)
END_INTERFACE_MAP()


// CCardread 消息处理程序


void CCardread::OnBnClickedOk2() //读卡
{
	unsigned char key[] = { 0xff,0xff,0xff,0xff,0xff,0xff };
	/*CString t2= "FFFFFFFFFFFF";
	key = (unsigned char)(LPCTSTR)t2;*/

	UpdateData(TRUE);
	//===
	/*if (m_Ip == 0)
	{
	AfxMessageBox("请填写完整信息！");
	return;
	}*/
	//GetDlgItem(IDC_STATIC23)->SetWindowText("开始连接ic卡");
	//===
	int st;
	unsigned __int16 TagType = 0;
	unsigned long snr = 0;
	unsigned char _size = 0;
	CString step, temp;
	CString strsql;
	unsigned char Info[16];
	unsigned char DID[15];
	st = rf_request(icdev, 1, &TagType);
	if (st)
	{
		AfxMessageBox("未找到IC卡!");
		return;
	}

	st = rf_anticoll(icdev, 0, &snr);
	if (st)
	{
		AfxMessageBox("IC卡片验证出错!");
		return;
	}

	st = rf_select(icdev, snr, &_size);
	if (st)
	{
		AfxMessageBox("检测卡片容量出错!");
		return;
	}
	st = rf_authentication_key(icdev, 0, 1, key);
	st = rf_read(icdev, 1, Info);
	memcpy(DID, Info, 14);
	DID[14] = '\0';
	m_did = DID;
	UpdateData(FALSE);
	strsql.Format("SELECT * FROM Drug where DID='%s'", m_did);
	pRs->Open(_bstr_t(strsql), 1);
	pRs->MoveFirst();
	pRs->GetFieldValue("DName", Dname);
	UpdateData(FALSE);
	step.Format("%c", Info[14]);
	if (Info[15] != '\0')
	{
		step.Format("%c%c", Info[14], Info[15]);
	}
	Step = (_ttoi(step));
	Buffer = "\r\n";
	for (int i = 0; i < Step; i++)
	{
		st = rf_authentication_key(icdev, 0, (i+1)*4, key);   st = rf_read(icdev, (i + 1) * 4, c[i].HID); //公司编号
		st = rf_authentication_key(icdev, 0, (i + 1) * 4 + 1, key);   st = rf_read(icdev, (i + 1) * 4 + 1, c[i].Time); //时间
		st = rf_authentication_key(icdev, 0, (i + 1) * 4 + 2, key);   st = rf_read(icdev, (i + 1) * 4 + 2, pHashMD5[i]); //MD5
		memcpy(hid[i], c[i].HID, 16);
		hid[i][16] = '\0';
		memcpy(time[i], c[i].Time, 16);
		hid[i][16] = '\0';
		strsql.Format("SELECT * FROM Firm where FID='%s'", (CString)hid[i]);
		pRs->Open(_bstr_t(strsql), 1);
		pRs->MoveFirst();
		pRs->GetFieldValue("FName", F_name[i]);
		temp.Format("%02d", i + 1);
		Buffer = Buffer + "====第" + temp + "站====\r\n公司编号：" + (CString)hid[i] + "\r\n公司名称：" + F_name[i] + "\r\n物流时间：" + (CString)time[i] + "\r\n\r\n";
		UpdateData(FALSE);
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CCardread::OnBnClickedOk() //校验
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_did == "")
	{
		AfxMessageBox("请先读卡！");
		return;
	}
	BYTE MD5[15][16];
	BYTE CHECK[15][16];
	BYTE buffer[15][32];
	CString check[15];
	for (int z = 0; z < 15; z++)
	{
		check[z] = "正确";
	}
	CString temp;
	int st;
	memcpy(buffer, c, sizeof(c));
	memcpy(CHECK, pHashMD5, sizeof(MD5));
	Buffer = "\r\n";
	for (int i = 0; i < Step; i++)
	{
		st = Dongle_HASH(hDongle, FLAG_HASH_MD5, buffer[i], 32, MD5[i]);
		for (int j = 0; j < 16; j++)
		{
			if (CHECK[i][j] != MD5[i][j])
			{
				check[i] = "错误";
				break;
			}
		}
		temp.Format("%02d", i + 1);
		Buffer = Buffer + "====第" + temp + "站====                                                   " + check[i] + "\r\n公司编号：" + (CString)hid[i] + "\r\n公司名称：" + F_name[i] + "\r\n物流时间：" + (CString)time[i] + "\r\n\r\n";
		UpdateData(FALSE);
	}
	//CDialogEx::OnOK();
}


BOOL CCardread::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO:  在此添加额外的初始化
	CString s;
	CString strsql;
	s = "File Name=linkDB.udl";
	pDB = new CADODatabase;
	pRs = new CADORecordset(pDB);
	if (!pDB->Open(s))
	{
		AfxMessageBox("数据库链接失败！单击退出！");
		OnCancel();
		return TRUE;
	}
	icdev = Open_USB();
	if ((int)icdev <= 0)
	{
		MessageBox("读卡器连接失败！");
		icdev = NULL;
		OnCancel();
		return TRUE;
	}
	rf_beep(icdev, 20);
	switch (type)
	{
	case 0:
		hDongle = m_a->m_main->hDongle;
		break;
	case 1:
		hDongle = m_p->m_main->hDongle;
		break;
	case 2:
		hDongle = m_t->m_main->hDongle;
		break;
	case 3:
		hDongle = m_d->m_main->hDongle;
		break;
	default:
		hDongle = NULL;
		break;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CCardread::OnDestroy()
{
	CDialogEx::OnDestroy();
	CDialogEx::OnDestroy();
	if (icdev != NULL)
	{
		Close_USB(icdev);
	}
	pRs->Close();
	pDB->Close();
	free(pRs);
	free(pDB);
	// TODO: 在此处添加消息处理程序代码
}
