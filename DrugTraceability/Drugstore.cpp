// Drugstore.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Drugstore.h"
#include "afxdialogex.h"


// CDrugstore �Ի���

IMPLEMENT_DYNAMIC(CDrugstore, CDialogEx)

CDrugstore::CDrugstore(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DRUGSTORE_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CDrugstore::~CDrugstore()
{
}

void CDrugstore::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ������������
	// ��������ĸ����������롣

	CDialogEx::OnFinalRelease();
}

void CDrugstore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDrugstore, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDrugstore, CDialogEx)
END_DISPATCH_MAP()

// ע��: �������� IID_IDrugstore ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {A446F9FB-2699-4887-97B4-71C93C938839}
static const IID IID_IDrugstore =
{ 0xA446F9FB, 0x2699, 0x4887, { 0x97, 0xB4, 0x71, 0xC9, 0x3C, 0x93, 0x88, 0x39 } };

BEGIN_INTERFACE_MAP(CDrugstore, CDialogEx)
	INTERFACE_PART(CDrugstore, IID_IDrugstore, Dispatch)
END_INTERFACE_MAP()


// CDrugstore ��Ϣ��������