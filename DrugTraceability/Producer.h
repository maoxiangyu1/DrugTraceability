#pragma once
#include "Login.h"

// CProducer 对话框

class CProducer : public CDialogEx
{
	DECLARE_DYNAMIC(CProducer)

public:
	CLogin * m_main;
	CProducer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProducer();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRODUCER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedDrugprod();
};
