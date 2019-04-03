#pragma once
#include "Login.h"

// CAdmin 对话框

class CAdmin : public CDialogEx
{
	DECLARE_DYNAMIC(CAdmin)

public:
	CLogin * m_main;
	CAdmin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAdmin();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRegsiterfirm();
	afx_msg void OnBnClickedRegsiterdrug();
	afx_msg void OnBnClickedSearchfirm();
	afx_msg void OnBnClickedSearchdrug();
	afx_msg void OnBnClickedCancel();
};
