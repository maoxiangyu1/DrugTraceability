// Producer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Producer.h"
#include "afxdialogex.h"


// CProducer �Ի���

IMPLEMENT_DYNAMIC(CProducer, CDialogEx)

CProducer::CProducer(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PRODUCER_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CProducer::~CProducer()
{
}

void CProducer::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ������������
	// ��������ĸ����������롣

	CDialogEx::OnFinalRelease();
}

void CProducer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProducer, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProducer, CDialogEx)
END_DISPATCH_MAP()

// ע��: �������� IID_IProducer ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {6E49755E-9B9A-4E2D-842A-8A38773E1791}
static const IID IID_IProducer =
{ 0x6E49755E, 0x9B9A, 0x4E2D, { 0x84, 0x2A, 0x8A, 0x38, 0x77, 0x3E, 0x17, 0x91 } };

BEGIN_INTERFACE_MAP(CProducer, CDialogEx)
	INTERFACE_PART(CProducer, IID_IProducer, Dispatch)
END_INTERFACE_MAP()


// CProducer ��Ϣ��������