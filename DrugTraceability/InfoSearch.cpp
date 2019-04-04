// InfoSearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "InfoSearch.h"
#include "afxdialogex.h"


// CInfoSearch �Ի���

IMPLEMENT_DYNAMIC(CInfoSearch, CDialogEx)

CInfoSearch::CInfoSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INFOSEARCH_DIALOG, pParent)
	, m_type(_T(""))
	, m_key(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CInfoSearch::~CInfoSearch()
{
}

void CInfoSearch::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ������������
	// ��������ĸ����������롣

	CDialogEx::OnFinalRelease();
}

void CInfoSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, com);
	DDX_Control(pDX, IDC_LIST1, m_listPerson);
	DDX_CBString(pDX, IDC_COMBO1, m_type);
	DDX_Text(pDX, IDC_EDIT2, m_key);
}


BEGIN_MESSAGE_MAP(CInfoSearch, CDialogEx)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDDEL, &CInfoSearch::OnBnClickedDel)
	ON_BN_CLICKED(IDSEARCH, &CInfoSearch::OnBnClickedSearch)
	ON_BN_CLICKED(IDCHANGE, &CInfoSearch::OnBnClickedChange)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CInfoSearch, CDialogEx)
END_DISPATCH_MAP()

// ע��: �������� IID_IInfoSearch ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {4814F9AB-6A8B-47FA-98E8-C5D6350CAB88}
static const IID IID_IInfoSearch =
{ 0x4814F9AB, 0x6A8B, 0x47FA, { 0x98, 0xE8, 0xC5, 0xD6, 0x35, 0xC, 0xAB, 0x88 } };

BEGIN_INTERFACE_MAP(CInfoSearch, CDialogEx)
	INTERFACE_PART(CInfoSearch, IID_IInfoSearch, Dispatch)
END_INTERFACE_MAP()


// CInfoSearch ��Ϣ��������


BOOL CInfoSearch::OnInitDialog()
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
	m_listPerson.ModifyStyle(0L, LVS_REPORT);
	m_listPerson.ModifyStyle(LVS_SHOWSELALWAYS, 0L);
	m_listPerson.ModifyStyle(0L, LVS_SHOWSELALWAYS);    //������ʾ��ѡ����
	m_listPerson.SetExtendedStyle(LVS_EX_FULLROWSELECT | //��������ѡ��
		LVS_EX_HEADERDRAGDROP |  //���������϶�
		LVS_EX_GRIDLINES |     //����������
		LVS_EX_ONECLICKACTIVATE |     //����ѡ����
		LVS_EX_FLATSB);    //��ƽ�����ʾ������
	if (type == 1)
	{
		//====
		SetWindowText("��˾��ѯ");
		com.AddString("��˾���");
		com.AddString("��˾����");
		com.AddString("��˾��ַ");
		com.AddString("��˾������");
		com.AddString("��˾����");
		com.AddString("��˾����");
		com.AddString("��˾�绰");
		//===
		m_listPerson.InsertColumn(0, "��˾���", LVCFMT_LEFT, 130, 0);
		m_listPerson.InsertColumn(1, "��˾����", LVCFMT_LEFT, 130, 1);
		m_listPerson.InsertColumn(2, "��˾��ַ", LVCFMT_LEFT, 130, 2);
		m_listPerson.InsertColumn(3, "��˾������", LVCFMT_LEFT, 130, 3);
		m_listPerson.InsertColumn(4, "��˾���", LVCFMT_LEFT, 130, 4);
		m_listPerson.InsertColumn(5, "��˾���", LVCFMT_LEFT, 130, 5);
		m_listPerson.InsertColumn(6, "��˾�绰", LVCFMT_LEFT, 130, 6);
		m_listPerson.InsertColumn(7, "ע��ʱ��", LVCFMT_LEFT, 130, 7);
		m_listPerson.InsertColumn(8, "ע��ʱ��(��)", LVCFMT_LEFT, 130, 8);
		strsql.Format("SELECT * FROM Firm");
		pRs->Open(_bstr_t(strsql), 1);
		
	}
	if (type == 2)
	{
		//===
		SetWindowText("ҩƷ��ѯ");
		com.AddString("ҩƷ���");
		com.AddString("ҩƷ����");
		com.AddString("ҩƷ�ɷ�");
		com.AddString("ҩƷЧ��");
		com.AddString("ҩƷ����");
		//===
		m_listPerson.InsertColumn(0, "ҩƷ���", LVCFMT_LEFT, 130, 0);
		m_listPerson.InsertColumn(1, "ҩƷ����", LVCFMT_LEFT, 130, 1);
		m_listPerson.InsertColumn(2, "ҩƷ�ɷ�", LVCFMT_LEFT, 130, 2);
		m_listPerson.InsertColumn(3, "ҩƷЧ��", LVCFMT_LEFT, 130, 3);
		m_listPerson.InsertColumn(4, "ע��ʱ��", LVCFMT_LEFT, 130, 4);
		m_listPerson.InsertColumn(5, "ҩƷ���", LVCFMT_LEFT, 130, 5);
		m_listPerson.InsertColumn(6, "��Чʱ��(��)", LVCFMT_LEFT, 130, 6);
		strsql.Format("SELECT * FROM Drug");
		pRs->Open(_bstr_t(strsql), 1);

	}
	if (!pRs->GetRecordCount())
	{
		m_listPerson.DeleteAllItems();
		return TRUE;
	}
	pRs->Open(_bstr_t(strsql), 1);
	RefreshList(*pRs);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CInfoSearch::OnDestroy()
{
	CDialogEx::OnDestroy();
	pRs->Close();
	pDB->Close();
	free(pRs);
	free(pDB);
	
	// TODO: �ڴ˴�������Ϣ�����������
}

BOOL CInfoSearch::RefreshList(CADORecordset& recordset)
{
	if (type == 1)
	{
		m_listPerson.DeleteAllItems();

		if (!recordset.IsOpen())
			return FALSE;

		recordset.MoveFirst();
		CString FID, FName, FLeader, Faddress, FTel, FInfo, FRegTime, FType, deadline;
		int indexofList = 0;
		while (!(recordset.IsEOF()))
		{
			recordset.GetFieldValue("FID", FID);
			recordset.GetFieldValue("FName", FName);
			recordset.GetFieldValue("FAddress", Faddress);
			recordset.GetFieldValue("FLeader", FLeader);
			recordset.GetFieldValue("FType", FType);
			recordset.GetFieldValue("FInfo", FInfo);
			recordset.GetFieldValue("FTel", FTel);			
			recordset.GetFieldValue("FRegisterTime", FRegTime);
			recordset.GetFieldValue("FDeadline", deadline);


			m_listPerson.InsertItem(indexofList, FID);
			m_listPerson.SetItemText(indexofList, 1, FName);
			m_listPerson.SetItemText(indexofList, 2, Faddress);
			m_listPerson.SetItemText(indexofList, 3, FLeader);
			m_listPerson.SetItemText(indexofList, 4, FType);
			m_listPerson.SetItemText(indexofList, 5, FInfo);
			m_listPerson.SetItemText(indexofList, 6, FTel);
			m_listPerson.SetItemText(indexofList, 7, FRegTime);
			m_listPerson.SetItemText(indexofList, 8, deadline);
			indexofList += 1;
			recordset.MoveNext();
		}
		recordset.MoveFirst();

		return TRUE;
	}
	if (type == 2)
	{
		m_listPerson.DeleteAllItems();

		if (!recordset.IsOpen())
			return FALSE;

		recordset.MoveFirst();
		CString DID, DName, DComponent, DEffect, DRegisterTime, DInfo,DDeadline;
		int indexofList = 0;
		while (!(recordset.IsEOF()))
		{
			recordset.GetFieldValue("DID", DID);
			recordset.GetFieldValue("DName", DName);
			recordset.GetFieldValue("DComponent", DComponent);
			recordset.GetFieldValue("DEffect", DEffect);
			recordset.GetFieldValue("DRegisterTime", DRegisterTime);
			recordset.GetFieldValue("DInfo", DInfo);
			recordset.GetFieldValue("DDeadline", DDeadline);


			m_listPerson.InsertItem(indexofList, DID);
			m_listPerson.SetItemText(indexofList, 1, DName);
			m_listPerson.SetItemText(indexofList, 2, DComponent);
			m_listPerson.SetItemText(indexofList, 3, DEffect);
			m_listPerson.SetItemText(indexofList, 4, DRegisterTime);
			m_listPerson.SetItemText(indexofList, 5, DInfo);
			m_listPerson.SetItemText(indexofList, 6, DDeadline);

			indexofList += 1;
			recordset.MoveNext();
		}
		recordset.MoveFirst();

		return TRUE;
	}
	
}

void CInfoSearch::OnBnClickedDel()
{
	if (type == 1)
	{
		POSITION pos = m_listPerson.GetFirstSelectedItemPosition();
		int nItem = m_listPerson.GetNextSelectedItem(pos);
		CString s = m_listPerson.GetItemText(nItem, 0);
		if (s == "")
		{
			AfxMessageBox("��ѡ����Ҫɾ������Ϣ��");
			return;
		}
		CString S;
		S.Format("delete Firm where FID='%s'", s);
		if (pDB->Execute(S) == TRUE)
		{
			m_listPerson.DeleteItem(nItem);
			AfxMessageBox("ɾ����˾��Ϣ�ɹ���");
			return;
		}
		else
		{
			AfxMessageBox("ɾ����˾��Ϣʧ�ܣ�");
			return;
		}
	}
	if (type == 2)
	{
		POSITION pos = m_listPerson.GetFirstSelectedItemPosition();
		int nItem = m_listPerson.GetNextSelectedItem(pos);
		CString s = m_listPerson.GetItemText(nItem, 0);
		if (s == "")
		{
			AfxMessageBox("��ѡ����Ҫɾ������Ϣ��");
			return;
		}
		CString S;
		S.Format("delete Drug where DID='%s'", s);
		if (pDB->Execute(S) == TRUE)
		{
			m_listPerson.DeleteItem(nItem);
			AfxMessageBox("ɾ��ҩƷ��Ϣ�ɹ���");
			return;
		}
		else
		{
			AfxMessageBox("ɾ��ҩƷ��Ϣʧ�ܣ�");
			return;
		}
	}
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
}


void CInfoSearch::OnBnClickedSearch()
{
	UpdateData(TRUE);
	CString strsql;
	if (type == 1)
	{
		if (m_key == "")
		{
			strsql.Format("SELECT * FROM Firm");
			pRs->Open(_bstr_t(strsql), 1);
			if (!pRs->GetRecordCount())
			{
				m_listPerson.DeleteAllItems();
				return;
			}
			pRs->Open(_bstr_t(strsql), 1);
			RefreshList(*(pRs));
			return;
		}
		if (m_type == "")
		{
			AfxMessageBox("��ѡ���ѯ���ͣ�");
			return;
		}
		if (m_type == "��˾���")
		{
			strsql = "select * from Firm where FID like '%" + m_key + "%'";
		}
		if (m_type == "��˾����")
		{
			strsql = "select * from Firm where FName like '%" + m_key + "%'";
		}
		if (m_type == "��˾��ַ")
		{
			strsql = "select * from Firm where FAddress like '%" + m_key + "%'";
		}
		if (m_type == "��˾������")
		{
			strsql = "select * from Firm where FLeader like '%" + m_key + "%'";
		}
		if (m_type == "��˾����")
		{
			strsql = "select * from Firm where FType like '%" + m_key + "%'";
		}
		if (m_type == "��˾����")
		{
			strsql = "select * from Firm where FInfo like '%" + m_key + "%'";
		}
		if (m_type == "��˾�绰")
		{
			strsql = "select * from Firm where FTel like '%" + m_key + "%'";
		}
	}
	if (type == 2)
	{
		if (m_key == "")
		{
			strsql.Format("SELECT * FROM Drug");
			pRs->Open(_bstr_t(strsql), 1);
			if (!pRs->GetRecordCount())
			{
				m_listPerson.DeleteAllItems();
				return;
			}
			pRs->Open(_bstr_t(strsql), 1);
			RefreshList(*(pRs));
			return;
		}
		if (m_type == "")
		{
			AfxMessageBox("��ѡ���ѯ���ͣ�");
			return;
		}
		if (m_type == "ҩƷ���")
		{
			strsql = "select * from Drug where DID like '%" + m_key + "%'";
		}
		if (m_type == "ҩƷ����")
		{
			strsql = "select * from Drug where DName like '%" + m_key + "%'";
		}
		if (m_type == "ҩƷ�ɷ�")
		{
			strsql = "select * from Drug where DComponent like '%" + m_key + "%'";
		}
		if (m_type == "ҩƷЧ��")
		{
			strsql = "select * from Drug where DEffect like '%" + m_key + "%'";
		}
		if (m_type == "ҩƷ����")
		{
			strsql = "select * from Drug where DInfo like '%" + m_key + "%'";
		}
	}

	pRs->Open(_bstr_t(strsql), 1);
	if (!pRs->GetRecordCount())
	{
		m_listPerson.DeleteAllItems();
		return;
	}
	pRs->Open(_bstr_t(strsql), 1);
	RefreshList(*(pRs));
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
}


void CInfoSearch::OnBnClickedChange()
{
	AfxMessageBox("ˢ�³ɹ���");
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
}