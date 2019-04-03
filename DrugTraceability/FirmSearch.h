#pragma once
#include "Admin.h"

// CFirmSearch 对话框

class CFirmSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CFirmSearch)

public:
	CAdmin *m_admin;
	CFirmSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFirmSearch();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIRMSEARCK_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
