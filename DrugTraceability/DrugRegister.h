#pragma once
#include "Admin.h"

// CDrugRegister �Ի���

class CDrugRegister : public CDialogEx
{
	DECLARE_DYNAMIC(CDrugRegister)

public:
	CAdmin *m_admin;
	CDrugRegister(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDrugRegister();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DURGREGISTER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};