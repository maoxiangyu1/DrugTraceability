// DrugRegister.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "DrugRegister.h"
#include "afxdialogex.h"


// CDrugRegister �Ի���

IMPLEMENT_DYNAMIC(CDrugRegister, CDialogEx)

CDrugRegister::CDrugRegister(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DURGREGISTER_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CDrugRegister::~CDrugRegister()
{
}

void CDrugRegister::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ������������
	// ��������ĸ����������롣

	CDialogEx::OnFinalRelease();
}

void CDrugRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDrugRegister, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDrugRegister, CDialogEx)
END_DISPATCH_MAP()

// ע��: �������� IID_IDrugRegister ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {CDEFBA67-E47D-4CBD-8042-E712C4AB4DE1}
static const IID IID_IDrugRegister =
{ 0xCDEFBA67, 0xE47D, 0x4CBD, { 0x80, 0x42, 0xE7, 0x12, 0xC4, 0xAB, 0x4D, 0xE1 } };

BEGIN_INTERFACE_MAP(CDrugRegister, CDialogEx)
	INTERFACE_PART(CDrugRegister, IID_IDrugRegister, Dispatch)
END_INTERFACE_MAP()


// CDrugRegister ��Ϣ��������