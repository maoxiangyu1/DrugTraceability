#pragma once
#include "Admin.h"
#include "ado.h"
// CFirmRegister 对话框

class CFirmRegister : public CDialogEx
{
	DECLARE_DYNAMIC(CFirmRegister)

public:
	CADODatabase * pDB;
	CAdmin *m_admin;
	CFirmRegister(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFirmRegister();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTERFIRM_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
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
