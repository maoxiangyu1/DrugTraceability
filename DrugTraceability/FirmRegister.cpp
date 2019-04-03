// FirmRegister.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "FirmRegister.h"
#include "afxdialogex.h"


// CFirmRegister �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ������������
	// ��������ĸ����������롣

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

// ע��: �������� IID_IFirmRegister ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {1C190B01-3EE2-426F-B5B5-25C0DD39271C}
static const IID IID_IFirmRegister =
{ 0x1C190B01, 0x3EE2, 0x426F, { 0xB5, 0xB5, 0x25, 0xC0, 0xDD, 0x39, 0x27, 0x1C } };

BEGIN_INTERFACE_MAP(CFirmRegister, CDialogEx)
	INTERFACE_PART(CFirmRegister, IID_IFirmRegister, Dispatch)
END_INTERFACE_MAP()


// CFirmRegister ��Ϣ��������


void CFirmRegister::OnBnClickedOk()//ע��
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	UpdateData(true);
	if (Name == "" || LeaderName == "" || Address == "" || Tel == "" || Info == "" || Type == ""||Deadline==0)
	{
		AfxMessageBox("��˾��Ϣ��������");
		//return;
	}
	CString s;
	DONGLE_HANDLE hDongle;
	int dwRet[6] = { 0 }, nCount;
	Firm firm;
	CString HID;
	char AdminPin[] = "FFFFFFFFFFFFFFFF";
	if (Dongle_Enum(NULL, &nCount) != DONGLE_SUCCESS || nCount != 2)
	{	
		AfxMessageBox("���Ӵ�д���豸ʧ�ܣ�");
		return;
	}	
	dwRet[0] = Dongle_Open(&hDongle, 0);
	if (hDongle == m_admin->m_main->hDongle)
	{
		dwRet[0] = Dongle_Open(&hDongle, 1);
	}
	int p = 255;
	if (Dongle_VerifyPIN(hDongle, FLAG_ADMINPIN, AdminPin, &p) != DONGLE_SUCCESS)
	{
		AfxMessageBox("��д���豸�޷�ʶ��");
	}
	pDongleInfo = (DONGLE_INFO *)malloc(nCount * sizeof(DONGLE_INFO));
	dwRet[0] = Dongle_Enum(pDongleInfo, &nCount);
	if (Type == "������")
	{
		firm.FirmType = 2;
		dwRet[5] = Dongle_SetUserID(hDongle, 0x11111111);
	}
	if (Type == "��תվ")
	{
		firm.FirmType = 3;
		dwRet[5] = Dongle_SetUserID(hDongle, 0x22222222);
	}
	if (Type == "ҩ��")
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
		s.Format("%02X", pDongleInfo[0].m_HID[i]);
		HID = HID + s;
	}
	if (HID == m_admin->m_main->HID)
	{
		HID = "";
		for (int i = 0; i < 8; i++)
		{
			s.Format("%02X", pDongleInfo[1].m_HID[i]);
			HID = HID + s;
		}
	}
	strcpy(firm.FirmID, HID);
	GetDlgItem(IDC_STATIC23)->SetWindowText("��ʼд��������Ϣ������γ�USB���ݣ�");
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
			AfxMessageBox("д��������Ϣ������������д�룡");
			GetDlgItem(IDC_STATIC23)->SetWindowText("д��������Ϣ������������д�룡");
			return;
		}
	}

	GetDlgItem(IDC_STATIC23)->SetWindowText("��ʼд�����ݿ���Ϣ��");
	
	CString sql;
	sql.Format("insert into Firm values('%s','%s','%s','%s','%s','%s','%s',%d,%d);"
		, firm.FirmID, Name, Address, LeaderName, Info, firm.Tel,firm.StartTime, firm.Deadline, firm.FirmType);
	if (TRUE != mysql_query(Mysql, sql))
	{

		GetDlgItem(IDC_STATIC23)->SetWindowText("д�����ݿ���Ϣʧ�ܣ�");
		AfxMessageBox("��˾ע��ʧ�ܣ�");
		return;
	}
	
	AfxMessageBox("��˾ע��ɹ���");
	//CDialogEx::OnOK();
}


BOOL CFirmRegister::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO:  �ڴ����Ӷ���ĳ�ʼ��
	Mysql = new MYSQL;
	mysql_init(Mysql);
	if (mysql_real_connect(Mysql, NULL, "root", "213011", "drugtraceability", 0, NULL, 0) == NULL)
	{
		AfxMessageBox("���ݿ�����ʧ�ܣ�");
		OnCancel();
	}
	mysql_options(Mysql, MYSQL_SET_CHARSET_NAME, "UTF-8");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CFirmRegister::OnDestroy()
{
	CDialogEx::OnDestroy();
	mysql_close(Mysql);
	free(pDongleInfo);
	delete(Mysql);
	// TODO: �ڴ˴�������Ϣ�����������
}