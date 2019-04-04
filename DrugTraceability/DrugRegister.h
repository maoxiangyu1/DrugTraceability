#pragma once
#include "ado.h"
// CDrugRegister 对话框

class CDrugRegister : public CDialogEx
{
	DECLARE_DYNAMIC(CDrugRegister)

public:
	CADODatabase * pDB;
	CDrugRegister(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDrugRegister();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTERDURG_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	virtual BOOL OnInitDialog();
//	CString DID;
	CString DName;
	CString Component;
	CString Effect;
	int Deadline;
	CString Info;
	afx_msg void OnBnClickedOk();
	afx_msg void OnDestroy();
	CString DID;
};
