#pragma once
#include"Admin.h"

// CDrugSearch �Ի���

class CDrugSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDrugSearch)

public:
	CAdmin *m_admin;
	CDrugSearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDrugSearch();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRUGSEARCH_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};