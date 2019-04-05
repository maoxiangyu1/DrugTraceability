#pragma once
#include "ado.h"
#include "Drugstore.h"
#include "Producer.h"
#include "Transfer.h"
#include "afxwin.h"
#include "mwrf32.h"
// CDrug �Ի���

class CDrug : public CDialogEx
{
	DECLARE_DYNAMIC(CDrug)

public:
	HANDLE icdev;
	CDrugstore *m_d;
	CProducer *m_p;
	CTransfer *m_t;
	int type; //1-���a��  2-���Dվ 3-ˎ��
	CADODatabase * pDB;
	CADORecordset* pRs;
	CDrug(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDrug();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRUG_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_cbox;
	CString m_did;
	CString m_Dname;
//	long m_lp;
	long m_Ip;
};