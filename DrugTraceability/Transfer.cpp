// Transfer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Transfer.h"
#include "afxdialogex.h"


// CTransfer �Ի���

IMPLEMENT_DYNAMIC(CTransfer, CDialogEx)

CTransfer::CTransfer(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TRANSFER_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CTransfer::~CTransfer()
{
}

void CTransfer::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ������������
	// ��������ĸ����������롣

	CDialogEx::OnFinalRelease();
}

void CTransfer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTransfer, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTransfer, CDialogEx)
END_DISPATCH_MAP()

// ע��: �������� IID_ITransfer ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {DF73781C-A3E1-43AA-A03E-AC67773F6476}
static const IID IID_ITransfer =
{ 0xDF73781C, 0xA3E1, 0x43AA, { 0xA0, 0x3E, 0xAC, 0x67, 0x77, 0x3F, 0x64, 0x76 } };

BEGIN_INTERFACE_MAP(CTransfer, CDialogEx)
	INTERFACE_PART(CTransfer, IID_ITransfer, Dispatch)
END_INTERFACE_MAP()


// CTransfer ��Ϣ��������