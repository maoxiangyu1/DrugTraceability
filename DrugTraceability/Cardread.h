#pragma once
#include "ado.h"
#include "Drugstore.h"
#include "Producer.h"
#include "Transfer.h"
#include "Admin.h"
// CCardread �Ի���

class CCardread : public CDialogEx
{
	DECLARE_DYNAMIC(CCardread)

public:
	unsigned char pHashMD5[15][16];
	Currency c[15];
	CString F_name[15];
	unsigned char hid[15][17];
	unsigned char time[15][17];
	DONGLE_HANDLE hDongle;
	int Step;//����
	CAdmin *m_a;
	CDrugstore *m_d;
	CProducer *m_p;
	CTransfer *m_t;
	int type; //0-ҩ��� 1-���a��  2-���Dվ 3-ˎ��
	HANDLE icdev;
	CADODatabase * pDB;
	CADORecordset* pRs;
	CCardread(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCardread();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ICREAD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	CString Buffer;
	CString m_did;
	CString Dname;
};