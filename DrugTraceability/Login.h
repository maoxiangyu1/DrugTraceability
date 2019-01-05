#pragma once
#include "Welcome.h"

// CLogin 对话框

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CWelcome *m_main;
	CLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogin();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	virtual BOOL OnInitDialog();
};
