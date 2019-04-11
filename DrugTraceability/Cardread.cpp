// Cardread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Cardread.h"
#include "afxdialogex.h"
#include "mwrf32.h"

// CCardread �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ������������
	// ��������ĸ����������롣

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

// ע��: �������� IID_ICardread ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {905F04F9-59DE-4B51-B416-8BF8FAA53E13}
static const IID IID_ICardread =
{ 0x905F04F9, 0x59DE, 0x4B51, { 0xB4, 0x16, 0x8B, 0xF8, 0xFA, 0xA5, 0x3E, 0x13 } };

BEGIN_INTERFACE_MAP(CCardread, CDialogEx)
	INTERFACE_PART(CCardread, IID_ICardread, Dispatch)
END_INTERFACE_MAP()


// CCardread ��Ϣ��������


void CCardread::OnBnClickedOk2() //����
{
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
	CString step, temp;
	CString strsql;
	unsigned char Info[16];
	unsigned char DID[15];
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
		st = rf_authentication_key(icdev, 0, (i+1)*4, key);   st = rf_read(icdev, (i + 1) * 4, c[i].HID); //��˾���
		st = rf_authentication_key(icdev, 0, (i + 1) * 4 + 1, key);   st = rf_read(icdev, (i + 1) * 4 + 1, c[i].Time); //ʱ��
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
		Buffer = Buffer + "====��" + temp + "վ====\r\n��˾��ţ�" + (CString)hid[i] + "\r\n��˾���ƣ�" + F_name[i] + "\r\n����ʱ�䣺" + (CString)time[i] + "\r\n\r\n";
		UpdateData(FALSE);
	}
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
}


void CCardread::OnBnClickedOk() //У��
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	if (m_did == "")
	{
		AfxMessageBox("���ȶ�����");
		return;
	}
	BYTE MD5[15][16];
	BYTE CHECK[15][16];
	BYTE buffer[15][32];
	CString check[15];
	for (int z = 0; z < 15; z++)
	{
		check[z] = "��ȷ";
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
				check[i] = "����";
				break;
			}
		}
		temp.Format("%02d", i + 1);
		Buffer = Buffer + "====��" + temp + "վ====                                                   " + check[i] + "\r\n��˾��ţ�" + (CString)hid[i] + "\r\n��˾���ƣ�" + F_name[i] + "\r\n����ʱ�䣺" + (CString)time[i] + "\r\n\r\n";
		UpdateData(FALSE);
	}
	//CDialogEx::OnOK();
}


BOOL CCardread::OnInitDialog()
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
		OnCancel();
		return TRUE;
	}
	icdev = Open_USB();
	if ((int)icdev <= 0)
	{
		MessageBox("����������ʧ�ܣ�");
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
				  // �쳣: OCX ����ҳӦ���� FALSE
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
	// TODO: �ڴ˴�������Ϣ�����������
}