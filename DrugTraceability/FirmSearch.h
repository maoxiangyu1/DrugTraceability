#pragma once
#include "Admin.h"

// CFirmSearch �Ի���

class CFirmSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CFirmSearch)

public:
	CAdmin *m_admin;
	CFirmSearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFirmSearch();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIRMSEARCK_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};