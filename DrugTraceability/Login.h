#pragma once
#include "Welcome.h"
#include "Dongle_API.h"

// CLogin 对话框

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CString FType;
	int size;
	BYTE sizebyte[4];
	BYTE buffer[4076];
	BYTE pHashMD5[16];
	Firm firm;
	CString HID;
	DONGLE_HANDLE hDongle;
	DONGLE_INFO *pDongleInfo;
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString Info;
	afx_msg void OnDestroy();
};
