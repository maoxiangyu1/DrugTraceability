// FirmSearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "FirmSearch.h"
#include "afxdialogex.h"


// CFirmSearch �Ի���

IMPLEMENT_DYNAMIC(CFirmSearch, CDialogEx)

CFirmSearch::CFirmSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FIRMSEARCK_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CFirmSearch::~CFirmSearch()
{
}

void CFirmSearch::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ������������
	// ��������ĸ����������롣

	CDialogEx::OnFinalRelease();
}

void CFirmSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFirmSearch, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFirmSearch, CDialogEx)
END_DISPATCH_MAP()

// ע��: �������� IID_IFirmSearch ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {B17212ED-2B9E-40FD-9580-259929E8E823}
static const IID IID_IFirmSearch =
{ 0xB17212ED, 0x2B9E, 0x40FD, { 0x95, 0x80, 0x25, 0x99, 0x29, 0xE8, 0xE8, 0x23 } };

BEGIN_INTERFACE_MAP(CFirmSearch, CDialogEx)
	INTERFACE_PART(CFirmSearch, IID_IFirmSearch, Dispatch)
END_INTERFACE_MAP()


// CFirmSearch ��Ϣ��������