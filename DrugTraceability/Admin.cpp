// Admin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Admin.h"
#include "afxdialogex.h"


// CAdmin �Ի���

IMPLEMENT_DYNAMIC(CAdmin, CDialogEx)

CAdmin::CAdmin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADMIN_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CAdmin::~CAdmin()
{
}

void CAdmin::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ������������
	// ��������ĸ����������롣

	CDialogEx::OnFinalRelease();
}

void CAdmin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAdmin, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAdmin, CDialogEx)
END_DISPATCH_MAP()

// ע��: �������� IID_IAdmin ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {2776E4F6-5C7B-45F7-8AFD-34FFCB6137EC}
static const IID IID_IAdmin =
{ 0x2776E4F6, 0x5C7B, 0x45F7, { 0x8A, 0xFD, 0x34, 0xFF, 0xCB, 0x61, 0x37, 0xEC } };

BEGIN_INTERFACE_MAP(CAdmin, CDialogEx)
	INTERFACE_PART(CAdmin, IID_IAdmin, Dispatch)
END_INTERFACE_MAP()


// CAdmin ��Ϣ��������