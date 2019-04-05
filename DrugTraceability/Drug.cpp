// Drug.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Drug.h"
#include "afxdialogex.h"


// CDrug 对话框

IMPLEMENT_DYNAMIC(CDrug, CDialogEx)

CDrug::CDrug(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DRUG_DIALOG, pParent)
	, m_did(_T(""))
	, m_Dname(_T(""))
	, m_Ip(0)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CDrug::~CDrug()
{
}

void CDrug::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CDrug::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbox);
	DDX_CBString(pDX, IDC_COMBO1, m_did);
	DDX_Text(pDX, IDC_EDIT2, m_Dname);
	//  DDX_Text(pDX, IDC_EDIT3, m_lp);
	//  DDV_MinMaxLong(pDX, m_lp, 0, 2147483647);
	DDX_Text(pDX, IDC_EDIT3, m_Ip);
	DDV_MinMaxLong(pDX, m_Ip, 0, 2147483647);
}


BEGIN_MESSAGE_MAP(CDrug, CDialogEx)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CDrug::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDrug::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDrug, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IDrug 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {86424CE4-7048-4377-BA73-43386C4DF16F}
static const IID IID_IDrug =
{ 0x86424CE4, 0x7048, 0x4377, { 0xBA, 0x73, 0x43, 0x38, 0x6C, 0x4D, 0xF1, 0x6F } };

BEGIN_INTERFACE_MAP(CDrug, CDialogEx)
	INTERFACE_PART(CDrug, IID_IDrug, Dispatch)
END_INTERFACE_MAP()


// CDrug 消息处理程序


void CDrug::OnDestroy()
{
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


BOOL CDrug::OnInitDialog()
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
		this->EndDialog(0);
		return TRUE;
	}
	icdev = Open_USB();
	if ((int)icdev <= 0)
	{
		MessageBox("读卡器连接失败！");
		this->EndDialog(0);
		return TRUE;
	}
	rf_beep(icdev, 20);
	if (type == 1)
	{
		SetWindowText("药品生产");
		SetDlgItemTextA(IDC_STATIC3, "生产件数：");
	}
	if (type == 2)
	{
		SetWindowText("药品中转");
		SetDlgItemTextA(IDOK, "读卡");
		m_cbox.EnableWindow(FALSE);
		SetDlgItemTextA(IDC_STATIC3, "中转件数：");
	}
	if (type == 3)
	{
		SetWindowText("药品出售");
		SetDlgItemTextA(IDOK, "读卡");
		m_cbox.EnableWindow(FALSE);
		SetDlgItemTextA(IDC_STATIC3, "出售件数：");
	}
	strsql.Format("SELECT * FROM Drug;");
	pRs->Open(_bstr_t(strsql), 1);
	if (!pRs->GetRecordCount())
	{
		return TRUE;
	}

	pRs->MoveFirst();
	CString DID;
	int indexofList = 0;
	while (!(pRs->IsEOF()))
	{
		pRs->GetFieldValue("DID", DID);
		m_cbox.AddString(DID);
		pRs->MoveNext();
	}
	pRs->MoveFirst();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CDrug::OnCbnSelchangeCombo1()
{
	UpdateData(true);
	CString strsql;
	strsql.Format("SELECT * FROM Drug where DID='%s'", m_did);
	pRs->Open(_bstr_t(strsql), 1);
	if (!pRs->GetRecordCount())
	{
		AfxMessageBox("无法获取药品信息！");
		return;
	}
	pRs->MoveFirst();
	pRs->GetFieldValue("DName", m_Dname);
	UpdateData(false);
	return;
	// TODO: 在此添加控件通知处理程序代码
}

void CDrug::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
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
	unsigned char buffer1[16];
	unsigned char buffer2[44];
	unsigned char buffer3[16];
	BYTE pHashMD5[16];
	CString step = "1";
	Currency c;
	CString sql ,info;
	//unsigned long sn;
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
	/*
		st = rf_authentication_key(icdev, 0, m_BlockNr, key);
		if (st)
		{
			GetDlgItem(IDC_STATIC23)->SetWindowText("验证IC扇区密码错误!");
			return;
		}
	*/
	/*for (int i = 0; i < 16; i = i + 1)
	{
		st = rf_authentication_key(icdev, 0, i, key);
		if (st)
		{
			GetDlgItem(IDC_STATIC23)->SetWindowText("验证IC扇区密码错误!");
			return;
		}
	}*/
	if (type == 1)
	{
		if (m_Ip == 0|| m_Dname == "")
		{
			AfxMessageBox("请填写完整信息！");
			//return;
		}	
		info = m_did + step;
		memcpy(c.info, info, 16);
		memcpy(c.HID, m_p->m_main->HID,16);
		CTime t = CTime::GetCurrentTime();
		CString s = t.Format("%Y-%m-%d");
		memcpy(c.Time, s,11);
		memcpy(buffer2, &c, 44);
		Dongle_HASH(m_p->m_main->hDongle, FLAG_HASH_MD5, buffer2, 44, pHashMD5);
		memcpy(buffer3, pHashMD5,16);
		if (rf_authentication_key(icdev, 0, 1, key)     || rf_write(icdev, 1, c.info)        || //步骤+药品编号
			rf_authentication_key(icdev, 0, 1*4, key)   || rf_write(icdev, 1 * 4, c.HID)      || //HID
			rf_authentication_key(icdev, 0, 1*4+1, key) || rf_write(icdev, 1 * 4 + 1, c.Time) || //时间
			rf_authentication_key(icdev, 0, 1*4+2, key) || rf_write(icdev, 1 * 4 + 2, buffer3)   //MD5
			)
		{
			AfxMessageBox("写入IC信息失败！");
			return;
		}
		GetDlgItem(IDC_STATIC23)->SetWindowText("开始写入数据库信息！");
		sql.Format("insert into Currency values('%s','%s','%d','%s')", m_p->m_main->HID, m_did, m_Ip, s);
		if (pDB->Execute(sql) == TRUE)
		{
			AfxMessageBox("数据库写入成功！");
			GetDlgItem(IDC_STATIC23)->SetWindowText("数据库写入成功！");
			CDialogEx::OnOK();
		}
		else
		{
			AfxMessageBox("数据库写入失败！");
			GetDlgItem(IDC_STATIC23)->SetWindowText("数据库写入失败！");
			return;
		}
	}
	if (type == 2)
	{
		CString bn;
		GetDlgItemText(IDOK, bn);
		if (bn == "读卡")
		{
			st = rf_authentication_key(icdev, 0, 1, key);
			st = rf_read(icdev, 1, c.info);
			memcpy(buffer1, c.info, 14);
			buffer1[14] = '\0';
			m_did = "";
			m_did = buffer1;
			step.Format("%c", c.info[14]);
			step.Format("%d", (_ttoi(step) + 1));
			info = m_did + step;
			if (buffer1[15] != '\0')
			{
				step.Format("%c%c", c.info[14], c.info[15]);
				step.Format("%d", (_ttoi(step) + 1));
				info = m_did + step;
			}
			memcpy(c.info, info, 16);
			SetDlgItemTextA(IDOK, "确定");
			UpdateData(FALSE);
			OnCbnSelchangeCombo1();
			return;
		}
		if (m_Ip == 0)
		{
			AfxMessageBox("请填写完整信息！");
			return;
		}
		st = rf_authentication_key(icdev, 0, 1, key);
		st = rf_read(icdev, 1, c.info);
		memcpy(buffer1, c.info, 14);
		buffer1[14] = '\0';
		m_did = "";
		m_did = buffer1;
		step.Format("%c", c.info[14]);
		step.Format("%d", (_ttoi(step) + 1));
		info = m_did + step;
		if (buffer1[15] != '\0')
		{
			step.Format("%c%c", c.info[14], c.info[15]);
			step.Format("%d", (_ttoi(step) + 1));
			info = m_did + step;
		}
		memcpy(c.info, info, 16);
		SetDlgItemTextA(IDOK, "确定");
		UpdateData(FALSE);
		OnCbnSelchangeCombo1();
		memcpy(buffer1,info, 16);
		memcpy(c.HID, m_t->m_main->HID, 16);
		CTime t = CTime::GetCurrentTime();
		CString s = t.Format("%Y-%m-%d");
		memcpy(c.Time, s, 11);
		memcpy(buffer2, &c, 44);
		Dongle_HASH(m_t->m_main->hDongle, FLAG_HASH_MD5, buffer2, 44, pHashMD5);
		memcpy(buffer3, pHashMD5, 16);
		if (
			rf_authentication_key(icdev, 0, 1, key) || rf_write(icdev, 1, buffer1) || //步骤+药品编号
			rf_authentication_key(icdev, 0, (_ttoi(step)) * 4, key) || rf_write(icdev, (_ttoi(step)) * 4, c.HID) || //HID
			rf_authentication_key(icdev, 0, (_ttoi(step)) * 4 + 1, key) || rf_write(icdev, (_ttoi(step)) * 4 + 1, c.Time) || //时间
			rf_authentication_key(icdev, 0, (_ttoi(step)) * 4 + 2, key) || rf_write(icdev, (_ttoi(step)) * 4 + 2, buffer3)   //MD5
			)
		{
			AfxMessageBox("写入IC信息失败！");
			return;
		}
		GetDlgItem(IDC_STATIC23)->SetWindowText("开始写入数据库信息！");
		sql.Format("insert into Currency values('%s','%s','%d','%s')", m_t->m_main->HID, m_did, m_Ip, s);
		if (pDB->Execute(sql) == TRUE)
		{
			AfxMessageBox("数据库写入成功！");
			GetDlgItem(IDC_STATIC23)->SetWindowText("数据库写入成功！");
			CDialogEx::OnOK();
		}
		else
		{
			AfxMessageBox("数据库写入失败！");
			GetDlgItem(IDC_STATIC23)->SetWindowText("数据库写入失败！");
			return;
		}
	}
	if (type == 3)
	{
		CString bn;
		GetDlgItemText(IDOK, bn);
		if (bn == "读卡")
		{
			st = rf_authentication_key(icdev, 0, 1, key);
			st = rf_read(icdev, 1, c.info);
			memcpy(buffer1, c.info, 14);
			buffer1[14] = '\0';
			m_did = "";
			m_did = buffer1;
			step.Format("%c", c.info[14]);
			step.Format("%d", (_ttoi(step) + 1));
			info = m_did + step;
			if (buffer1[15] != '\0')
			{
				step.Format("%c%c", c.info[14], c.info[15]);
				step.Format("%d", (_ttoi(step) + 1));
				info = m_did + step;
			}
			memcpy(c.info, info, 16);
			SetDlgItemTextA(IDOK, "确定");
			UpdateData(FALSE);
			OnCbnSelchangeCombo1();
			return;
		}
		if (m_Ip == 0)
		{
			AfxMessageBox("请填写完整信息！");
			return;
		}
		st = rf_authentication_key(icdev, 0, 1, key);
		st = rf_read(icdev, 1, c.info);
		memcpy(buffer1, c.info, 14);
		buffer1[14] = '\0';
		m_did = "";
		m_did = buffer1;
		step.Format("%c", c.info[14]);
		step.Format("%d", (_ttoi(step) + 1));
		info = m_did + step;
		if (buffer1[15] != '\0')
		{
			step.Format("%c%c", c.info[14], c.info[15]);
			step.Format("%d", (_ttoi(step) + 1));
			info = m_did + step;
		}
		memcpy(c.info, info, 16);
		SetDlgItemTextA(IDOK, "确定");
		OnCbnSelchangeCombo1();
		memcpy(buffer1, info, 16);
		memcpy(c.HID, m_d->m_main->HID, 16);
		CTime t = CTime::GetCurrentTime();
		CString s = t.Format("%Y-%m-%d");
		memcpy(c.Time, s, 11);
		memcpy(buffer2, &c, 44);
		Dongle_HASH(m_d->m_main->hDongle, FLAG_HASH_MD5, buffer2, 44, pHashMD5);
		memcpy(buffer3, pHashMD5, 16);
		if (
			rf_authentication_key(icdev, 0, 1, key) || rf_write(icdev, 1, buffer1) || //步骤+药品编号
			rf_authentication_key(icdev, 0, (_ttoi(step)) * 4, key) || rf_write(icdev, (_ttoi(step)) * 4, c.HID) || //HID
			rf_authentication_key(icdev, 0, (_ttoi(step)) * 4 + 1, key) || rf_write(icdev, (_ttoi(step)) * 4 + 1, c.Time) || //时间
			rf_authentication_key(icdev, 0, (_ttoi(step)) * 4 + 2, key) || rf_write(icdev, (_ttoi(step)) * 4 + 2, buffer3)   //MD5
			)
		{
			AfxMessageBox("写入IC信息失败！");
			return;
		}
		GetDlgItem(IDC_STATIC23)->SetWindowText("开始写入数据库信息！");
		sql.Format("insert into Currency values('%s','%s','%d','%s')", m_d->m_main->HID, m_did, m_Ip, s);
		if (pDB->Execute(sql) == TRUE)
		{
			AfxMessageBox("数据库写入成功！");
			GetDlgItem(IDC_STATIC23)->SetWindowText("数据库写入成功！");
			CDialogEx::OnOK();
		}
		else
		{
			AfxMessageBox("数据库写入失败！");
			GetDlgItem(IDC_STATIC23)->SetWindowText("数据库写入失败！");
			return;
		}
	}
	
}



