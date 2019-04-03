#pragma once
#include "Admin.h"

// CFirmRegister �Ի���

class CFirmRegister : public CDialogEx
{
	DECLARE_DYNAMIC(CFirmRegister)

public:
	CAdmin *m_admin;
	CFirmRegister(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFirmRegister();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTERFIRM_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	MYSQL *Mysql;
	DONGLE_INFO *pDongleInfo;
	CString Name;
	CString LeaderName;
	CString Address;
	CString Tel;
	CString Type;
	int Deadline;
	CString Info;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
};