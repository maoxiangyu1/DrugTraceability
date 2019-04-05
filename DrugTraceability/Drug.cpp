// Drug.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Drug.h"
#include "afxdialogex.h"


// CDrug �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ������������
	// ��������ĸ����������롣

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

// ע��: �������� IID_IDrug ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {86424CE4-7048-4377-BA73-43386C4DF16F}
static const IID IID_IDrug =
{ 0x86424CE4, 0x7048, 0x4377, { 0xBA, 0x73, 0x43, 0x38, 0x6C, 0x4D, 0xF1, 0x6F } };

BEGIN_INTERFACE_MAP(CDrug, CDialogEx)
	INTERFACE_PART(CDrug, IID_IDrug, Dispatch)
END_INTERFACE_MAP()


// CDrug ��Ϣ��������


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
	// TODO: �ڴ˴�������Ϣ�����������
}


BOOL CDrug::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO:  �ڴ����Ӷ���ĳ�ʼ��
	CString s;
	CString strsql;
	s = "File Name=linkDB.udl";
	pDB = new CADODatabase;
	pRs = new CADORecordset(pDB);
	if (!pDB->Open(s))
	{
		AfxMessageBox("���ݿ�����ʧ�ܣ������˳���");
		this->EndDialog(0);
		return TRUE;
	}
	icdev = Open_USB();
	if ((int)icdev <= 0)
	{
		MessageBox("����������ʧ�ܣ�");
		this->EndDialog(0);
		return TRUE;
	}
	rf_beep(icdev, 20);
	if (type == 1)
	{
		SetWindowText("ҩƷ����");
		SetDlgItemTextA(IDC_STATIC3, "����������");
	}
	if (type == 2)
	{
		SetWindowText("ҩƷ��ת");
		SetDlgItemTextA(IDOK, "����");
		m_cbox.EnableWindow(FALSE);
		SetDlgItemTextA(IDC_STATIC3, "��ת������");
	}
	if (type == 3)
	{
		SetWindowText("ҩƷ����");
		SetDlgItemTextA(IDOK, "����");
		m_cbox.EnableWindow(FALSE);
		SetDlgItemTextA(IDC_STATIC3, "���ۼ�����");
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
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CDrug::OnCbnSelchangeCombo1()
{
	UpdateData(true);
	CString strsql;
	strsql.Format("SELECT * FROM Drug where DID='%s'", m_did);
	pRs->Open(_bstr_t(strsql), 1);
	if (!pRs->GetRecordCount())
	{
		AfxMessageBox("�޷���ȡҩƷ��Ϣ��");
		return;
	}
	pRs->MoveFirst();
	pRs->GetFieldValue("DName", m_Dname);
	UpdateData(false);
	return;
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
}

void CDrug::OnBnClickedOk()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	unsigned char key[] = { 0xff,0xff,0xff,0xff,0xff,0xff };
	/*CString t2= "FFFFFFFFFFFF";
	key = (unsigned char)(LPCTSTR)t2;*/
	
	UpdateData(TRUE);	
	//===
	/*if (m_Ip == 0)
	{
		AfxMessageBox("����д������Ϣ��");
		return;
	}*/
	//GetDlgItem(IDC_STATIC23)->SetWindowText("��ʼ����ic��");
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
		AfxMessageBox("δ�ҵ�IC��!");
		return;
	}

	st = rf_anticoll(icdev, 0, &snr);
	if (st)
	{
		AfxMessageBox("IC��Ƭ��֤����!");
		return;
	}

	st = rf_select(icdev, snr, &_size);
	if (st)
	{
		AfxMessageBox("��⿨Ƭ��������!");
		return;
	}
	/*
		st = rf_authentication_key(icdev, 0, m_BlockNr, key);
		if (st)
		{
			GetDlgItem(IDC_STATIC23)->SetWindowText("��֤IC�����������!");
			return;
		}
	*/
	/*for (int i = 0; i < 16; i = i + 1)
	{
		st = rf_authentication_key(icdev, 0, i, key);
		if (st)
		{
			GetDlgItem(IDC_STATIC23)->SetWindowText("��֤IC�����������!");
			return;
		}
	}*/
	if (type == 1)
	{
		if (m_Ip == 0|| m_Dname == "")
		{
			AfxMessageBox("����д������Ϣ��");
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
		if (rf_authentication_key(icdev, 0, 1, key)     || rf_write(icdev, 1, c.info)        || //����+ҩƷ���
			rf_authentication_key(icdev, 0, 1*4, key)   || rf_write(icdev, 1 * 4, c.HID)      || //HID
			rf_authentication_key(icdev, 0, 1*4+1, key) || rf_write(icdev, 1 * 4 + 1, c.Time) || //ʱ��
			rf_authentication_key(icdev, 0, 1*4+2, key) || rf_write(icdev, 1 * 4 + 2, buffer3)   //MD5
			)
		{
			AfxMessageBox("д��IC��Ϣʧ�ܣ�");
			return;
		}
		GetDlgItem(IDC_STATIC23)->SetWindowText("��ʼд�����ݿ���Ϣ��");
		sql.Format("insert into Currency values('%s','%s','%d','%s')", m_p->m_main->HID, m_did, m_Ip, s);
		if (pDB->Execute(sql) == TRUE)
		{
			AfxMessageBox("���ݿ�д��ɹ���");
			GetDlgItem(IDC_STATIC23)->SetWindowText("���ݿ�д��ɹ���");
			CDialogEx::OnOK();
		}
		else
		{
			AfxMessageBox("���ݿ�д��ʧ�ܣ�");
			GetDlgItem(IDC_STATIC23)->SetWindowText("���ݿ�д��ʧ�ܣ�");
			return;
		}
	}
	if (type == 2)
	{
		CString bn;
		GetDlgItemText(IDOK, bn);
		if (bn == "����")
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
			SetDlgItemTextA(IDOK, "ȷ��");
			UpdateData(FALSE);
			OnCbnSelchangeCombo1();
			return;
		}
		if (m_Ip == 0)
		{
			AfxMessageBox("����д������Ϣ��");
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
		SetDlgItemTextA(IDOK, "ȷ��");
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
			rf_authentication_key(icdev, 0, 1, key) || rf_write(icdev, 1, buffer1) || //����+ҩƷ���
			rf_authentication_key(icdev, 0, (_ttoi(step)) * 4, key) || rf_write(icdev, (_ttoi(step)) * 4, c.HID) || //HID
			rf_authentication_key(icdev, 0, (_ttoi(step)) * 4 + 1, key) || rf_write(icdev, (_ttoi(step)) * 4 + 1, c.Time) || //ʱ��
			rf_authentication_key(icdev, 0, (_ttoi(step)) * 4 + 2, key) || rf_write(icdev, (_ttoi(step)) * 4 + 2, buffer3)   //MD5
			)
		{
			AfxMessageBox("д��IC��Ϣʧ�ܣ�");
			return;
		}
		GetDlgItem(IDC_STATIC23)->SetWindowText("��ʼд�����ݿ���Ϣ��");
		sql.Format("insert into Currency values('%s','%s','%d','%s')", m_t->m_main->HID, m_did, m_Ip, s);
		if (pDB->Execute(sql) == TRUE)
		{
			AfxMessageBox("���ݿ�д��ɹ���");
			GetDlgItem(IDC_STATIC23)->SetWindowText("���ݿ�д��ɹ���");
			CDialogEx::OnOK();
		}
		else
		{
			AfxMessageBox("���ݿ�д��ʧ�ܣ�");
			GetDlgItem(IDC_STATIC23)->SetWindowText("���ݿ�д��ʧ�ܣ�");
			return;
		}
	}
	if (type == 3)
	{
		CString bn;
		GetDlgItemText(IDOK, bn);
		if (bn == "����")
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
			SetDlgItemTextA(IDOK, "ȷ��");
			UpdateData(FALSE);
			OnCbnSelchangeCombo1();
			return;
		}
		if (m_Ip == 0)
		{
			AfxMessageBox("����д������Ϣ��");
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
		SetDlgItemTextA(IDOK, "ȷ��");
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
			rf_authentication_key(icdev, 0, 1, key) || rf_write(icdev, 1, buffer1) || //����+ҩƷ���
			rf_authentication_key(icdev, 0, (_ttoi(step)) * 4, key) || rf_write(icdev, (_ttoi(step)) * 4, c.HID) || //HID
			rf_authentication_key(icdev, 0, (_ttoi(step)) * 4 + 1, key) || rf_write(icdev, (_ttoi(step)) * 4 + 1, c.Time) || //ʱ��
			rf_authentication_key(icdev, 0, (_ttoi(step)) * 4 + 2, key) || rf_write(icdev, (_ttoi(step)) * 4 + 2, buffer3)   //MD5
			)
		{
			AfxMessageBox("д��IC��Ϣʧ�ܣ�");
			return;
		}
		GetDlgItem(IDC_STATIC23)->SetWindowText("��ʼд�����ݿ���Ϣ��");
		sql.Format("insert into Currency values('%s','%s','%d','%s')", m_d->m_main->HID, m_did, m_Ip, s);
		if (pDB->Execute(sql) == TRUE)
		{
			AfxMessageBox("���ݿ�д��ɹ���");
			GetDlgItem(IDC_STATIC23)->SetWindowText("���ݿ�д��ɹ���");
			CDialogEx::OnOK();
		}
		else
		{
			AfxMessageBox("���ݿ�д��ʧ�ܣ�");
			GetDlgItem(IDC_STATIC23)->SetWindowText("���ݿ�д��ʧ�ܣ�");
			return;
		}
	}
	
}


