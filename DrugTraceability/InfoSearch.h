#pragma once
#include "ado.h"
#include "afxwin.h"
#include "afxcmn.h"
// CInfoSearch �Ի���

class CInfoSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CInfoSearch)

public:
	CADODatabase * pDB;
	CADORecordset* pRs;
	int type;//���� 1-��˾  2-ҩƷ
	CInfoSearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInfoSearch();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INFOSEARCH_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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