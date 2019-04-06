#pragma once
#include "ado.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "Producer.h"
#include "Transfer.h"
#include "Drugstore.h"
// CInfoSearch 对话框

class CInfoSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CInfoSearch)

public:
	CString HID;
	CDrugstore *m_d;
	CProducer *m_p;
	CTransfer *m_t;
	CADODatabase * pDB;
	CADORecordset* pRs;
	int type;//类型 1-公司  2-药品  3-流通记录
	int degree;//身份 0-药监局 1-生产商 2-中转站 3-药店
	CInfoSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInfoSearch();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INFOSEARCH_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox com;
	CListCtrl m_listPerson;
	afx_msg void OnDestroy();
	BOOL RefreshList(CADORecordset& recordset);
	afx_msg void OnBnClickedDel();
	CString m_type;
	CString m_key;
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedChange();
};
