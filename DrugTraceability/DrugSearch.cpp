// DrugSearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "DrugSearch.h"
#include "afxdialogex.h"


// CDrugSearch �Ի���

IMPLEMENT_DYNAMIC(CDrugSearch, CDialogEx)

CDrugSearch::CDrugSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DRUGSEARCH_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CDrugSearch::~CDrugSearch()
{
}

void CDrugSearch::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ������������
	// ��������ĸ����������롣

	CDialogEx::OnFinalRelease();
}

void CDrugSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDrugSearch, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDrugSearch, CDialogEx)
END_DISPATCH_MAP()

// ע��: �������� IID_IDrugSearch ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {528AD457-9CDB-44C0-8763-58B907BE6EA0}
static const IID IID_IDrugSearch =
{ 0x528AD457, 0x9CDB, 0x44C0, { 0x87, 0x63, 0x58, 0xB9, 0x7, 0xBE, 0x6E, 0xA0 } };

BEGIN_INTERFACE_MAP(CDrugSearch, CDialogEx)
	INTERFACE_PART(CDrugSearch, IID_IDrugSearch, Dispatch)
END_INTERFACE_MAP()


// CDrugSearch ��Ϣ��������