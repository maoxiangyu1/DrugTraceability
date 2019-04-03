#pragma once
#include"Admin.h"

// CDrugSearch 对话框

class CDrugSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDrugSearch)

public:
	CAdmin *m_admin;
	CDrugSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDrugSearch();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRUGSEARCH_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
