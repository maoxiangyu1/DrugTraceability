#pragma once
#include "Login.h"

// CProducer �Ի���

class CProducer : public CDialogEx
{
	DECLARE_DYNAMIC(CProducer)

public:
	CLogin * m_main;
	CProducer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProducer();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRODUCER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};