#pragma once
#include "Login.h"

// CDrugstore �Ի���

class CDrugstore : public CDialogEx
{
	DECLARE_DYNAMIC(CDrugstore)

public:
	CLogin * m_main;
	CDrugstore(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDrugstore();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRUGSTORE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};