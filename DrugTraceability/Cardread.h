#pragma once
#include "ado.h"
#include "Drugstore.h"
#include "Producer.h"
#include "Transfer.h"
#include "Admin.h"
// CCardread 对话框

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
	int Step;//步数
	CAdmin *m_a;
	CDrugstore *m_d;
	CProducer *m_p;
	CTransfer *m_t;
	int type; //0-药监局 1-生產商  2-中轉站 3-藥店
	HANDLE icdev;
	CADODatabase * pDB;
	CADORecordset* pRs;
	CCardread(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCardread();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ICREAD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
