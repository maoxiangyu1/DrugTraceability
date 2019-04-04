// InfoSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "InfoSearch.h"
#include "afxdialogex.h"


// CInfoSearch 对话框

IMPLEMENT_DYNAMIC(CInfoSearch, CDialogEx)

CInfoSearch::CInfoSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INFOSEARCH_DIALOG, pParent)
	, m_type(_T(""))
	, m_key(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CInfoSearch::~CInfoSearch()
{
}

void CInfoSearch::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CInfoSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, com);
	DDX_Control(pDX, IDC_LIST1, m_listPerson);
	DDX_CBString(pDX, IDC_COMBO1, m_type);
	DDX_Text(pDX, IDC_EDIT2, m_key);
}


BEGIN_MESSAGE_MAP(CInfoSearch, CDialogEx)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDDEL, &CInfoSearch::OnBnClickedDel)
	ON_BN_CLICKED(IDSEARCH, &CInfoSearch::OnBnClickedSearch)
	ON_BN_CLICKED(IDCHANGE, &CInfoSearch::OnBnClickedChange)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CInfoSearch, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IInfoSearch 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {4814F9AB-6A8B-47FA-98E8-C5D6350CAB88}
static const IID IID_IInfoSearch =
{ 0x4814F9AB, 0x6A8B, 0x47FA, { 0x98, 0xE8, 0xC5, 0xD6, 0x35, 0xC, 0xAB, 0x88 } };

BEGIN_INTERFACE_MAP(CInfoSearch, CDialogEx)
	INTERFACE_PART(CInfoSearch, IID_IInfoSearch, Dispatch)
END_INTERFACE_MAP()


// CInfoSearch 消息处理程序


BOOL CInfoSearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO:  在此添加额外的初始化
	CString s;
	CString strsql;
	s = "File Name=linkDB.udl";
	pDB = new CADODatabase;
	pRs = new CADORecordset(pDB);
	if (!pDB->Open(s))
	{
		AfxMessageBox("数据库链接失败！单击退出！");
		this->EndDialog(0);
		return TRUE;
	}
	m_listPerson.ModifyStyle(0L, LVS_REPORT);
	m_listPerson.ModifyStyle(LVS_SHOWSELALWAYS, 0L);
	m_listPerson.ModifyStyle(0L, LVS_SHOWSELALWAYS);    //高亮显示被选中项
	m_listPerson.SetExtendedStyle(LVS_EX_FULLROWSELECT | //允许整行选中
		LVS_EX_HEADERDRAGDROP |  //允许整列拖动
		LVS_EX_GRIDLINES |     //画出网格线
		LVS_EX_ONECLICKACTIVATE |     //单击选中项
		LVS_EX_FLATSB);    //扁平风格显示滚动条
	if (type == 1)
	{
		//====
		SetWindowText("公司查询");
		com.AddString("公司编号");
		com.AddString("公司名称");
		com.AddString("公司地址");
		com.AddString("公司负责人");
		com.AddString("公司类型");
		com.AddString("公司简述");
		com.AddString("公司电话");
		//===
		m_listPerson.InsertColumn(0, "公司编号", LVCFMT_LEFT, 130, 0);
		m_listPerson.InsertColumn(1, "公司名称", LVCFMT_LEFT, 130, 1);
		m_listPerson.InsertColumn(2, "公司地址", LVCFMT_LEFT, 130, 2);
		m_listPerson.InsertColumn(3, "公司负责人", LVCFMT_LEFT, 130, 3);
		m_listPerson.InsertColumn(4, "公司类别", LVCFMT_LEFT, 130, 4);
		m_listPerson.InsertColumn(5, "公司简介", LVCFMT_LEFT, 130, 5);
		m_listPerson.InsertColumn(6, "公司电话", LVCFMT_LEFT, 130, 6);
		m_listPerson.InsertColumn(7, "注册时间", LVCFMT_LEFT, 130, 7);
		m_listPerson.InsertColumn(8, "注册时长(月)", LVCFMT_LEFT, 130, 8);
		strsql.Format("SELECT * FROM Firm");
		pRs->Open(_bstr_t(strsql), 1);
		
	}
	if (type == 2)
	{
		//===
		SetWindowText("药品查询");
		com.AddString("药品编号");
		com.AddString("药品名称");
		com.AddString("药品成份");
		com.AddString("药品效用");
		com.AddString("药品简述");
		//===
		m_listPerson.InsertColumn(0, "药品编号", LVCFMT_LEFT, 130, 0);
		m_listPerson.InsertColumn(1, "药品名称", LVCFMT_LEFT, 130, 1);
		m_listPerson.InsertColumn(2, "药品成分", LVCFMT_LEFT, 130, 2);
		m_listPerson.InsertColumn(3, "药品效用", LVCFMT_LEFT, 130, 3);
		m_listPerson.InsertColumn(4, "注册时间", LVCFMT_LEFT, 130, 4);
		m_listPerson.InsertColumn(5, "药品简介", LVCFMT_LEFT, 130, 5);
		m_listPerson.InsertColumn(6, "有效时长(月)", LVCFMT_LEFT, 130, 6);
		strsql.Format("SELECT * FROM Drug");
		pRs->Open(_bstr_t(strsql), 1);

	}
	if (!pRs->GetRecordCount())
	{
		m_listPerson.DeleteAllItems();
		return TRUE;
	}
	pRs->Open(_bstr_t(strsql), 1);
	RefreshList(*pRs);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CInfoSearch::OnDestroy()
{
	CDialogEx::OnDestroy();
	pRs->Close();
	pDB->Close();
	free(pRs);
	free(pDB);
	
	// TODO: 在此处添加消息处理程序代码
}

BOOL CInfoSearch::RefreshList(CADORecordset& recordset)
{
	if (type == 1)
	{
		m_listPerson.DeleteAllItems();

		if (!recordset.IsOpen())
			return FALSE;

		recordset.MoveFirst();
		CString FID, FName, FLeader, Faddress, FTel, FInfo, FRegTime, FType, deadline;
		int indexofList = 0;
		while (!(recordset.IsEOF()))
		{
			recordset.GetFieldValue("FID", FID);
			recordset.GetFieldValue("FName", FName);
			recordset.GetFieldValue("FAddress", Faddress);
			recordset.GetFieldValue("FLeader", FLeader);
			recordset.GetFieldValue("FType", FType);
			recordset.GetFieldValue("FInfo", FInfo);
			recordset.GetFieldValue("FTel", FTel);			
			recordset.GetFieldValue("FRegisterTime", FRegTime);
			recordset.GetFieldValue("FDeadline", deadline);


			m_listPerson.InsertItem(indexofList, FID);
			m_listPerson.SetItemText(indexofList, 1, FName);
			m_listPerson.SetItemText(indexofList, 2, Faddress);
			m_listPerson.SetItemText(indexofList, 3, FLeader);
			m_listPerson.SetItemText(indexofList, 4, FType);
			m_listPerson.SetItemText(indexofList, 5, FInfo);
			m_listPerson.SetItemText(indexofList, 6, FTel);
			m_listPerson.SetItemText(indexofList, 7, FRegTime);
			m_listPerson.SetItemText(indexofList, 8, deadline);
			indexofList += 1;
			recordset.MoveNext();
		}
		recordset.MoveFirst();

		return TRUE;
	}
	if (type == 2)
	{
		m_listPerson.DeleteAllItems();

		if (!recordset.IsOpen())
			return FALSE;

		recordset.MoveFirst();
		CString DID, DName, DComponent, DEffect, DRegisterTime, DInfo,DDeadline;
		int indexofList = 0;
		while (!(recordset.IsEOF()))
		{
			recordset.GetFieldValue("DID", DID);
			recordset.GetFieldValue("DName", DName);
			recordset.GetFieldValue("DComponent", DComponent);
			recordset.GetFieldValue("DEffect", DEffect);
			recordset.GetFieldValue("DRegisterTime", DRegisterTime);
			recordset.GetFieldValue("DInfo", DInfo);
			recordset.GetFieldValue("DDeadline", DDeadline);


			m_listPerson.InsertItem(indexofList, DID);
			m_listPerson.SetItemText(indexofList, 1, DName);
			m_listPerson.SetItemText(indexofList, 2, DComponent);
			m_listPerson.SetItemText(indexofList, 3, DEffect);
			m_listPerson.SetItemText(indexofList, 4, DRegisterTime);
			m_listPerson.SetItemText(indexofList, 5, DInfo);
			m_listPerson.SetItemText(indexofList, 6, DDeadline);

			indexofList += 1;
			recordset.MoveNext();
		}
		recordset.MoveFirst();

		return TRUE;
	}
	
}

void CInfoSearch::OnBnClickedDel()
{
	if (type == 1)
	{
		POSITION pos = m_listPerson.GetFirstSelectedItemPosition();
		int nItem = m_listPerson.GetNextSelectedItem(pos);
		CString s = m_listPerson.GetItemText(nItem, 0);
		if (s == "")
		{
			AfxMessageBox("请选中您要删除的信息！");
			return;
		}
		CString S;
		S.Format("delete Firm where FID='%s'", s);
		if (pDB->Execute(S) == TRUE)
		{
			m_listPerson.DeleteItem(nItem);
			AfxMessageBox("删除公司信息成功！");
			return;
		}
		else
		{
			AfxMessageBox("删除公司信息失败！");
			return;
		}
	}
	if (type == 2)
	{
		POSITION pos = m_listPerson.GetFirstSelectedItemPosition();
		int nItem = m_listPerson.GetNextSelectedItem(pos);
		CString s = m_listPerson.GetItemText(nItem, 0);
		if (s == "")
		{
			AfxMessageBox("请选中您要删除的信息！");
			return;
		}
		CString S;
		S.Format("delete Drug where DID='%s'", s);
		if (pDB->Execute(S) == TRUE)
		{
			m_listPerson.DeleteItem(nItem);
			AfxMessageBox("删除药品信息成功！");
			return;
		}
		else
		{
			AfxMessageBox("删除药品信息失败！");
			return;
		}
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CInfoSearch::OnBnClickedSearch()
{
	UpdateData(TRUE);
	CString strsql;
	if (type == 1)
	{
		if (m_key == "")
		{
			strsql.Format("SELECT * FROM Firm");
			pRs->Open(_bstr_t(strsql), 1);
			if (!pRs->GetRecordCount())
			{
				m_listPerson.DeleteAllItems();
				return;
			}
			pRs->Open(_bstr_t(strsql), 1);
			RefreshList(*(pRs));
			return;
		}
		if (m_type == "")
		{
			AfxMessageBox("请选择查询类型！");
			return;
		}
		if (m_type == "公司编号")
		{
			strsql = "select * from Firm where FID like '%" + m_key + "%'";
		}
		if (m_type == "公司名称")
		{
			strsql = "select * from Firm where FName like '%" + m_key + "%'";
		}
		if (m_type == "公司地址")
		{
			strsql = "select * from Firm where FAddress like '%" + m_key + "%'";
		}
		if (m_type == "公司负责人")
		{
			strsql = "select * from Firm where FLeader like '%" + m_key + "%'";
		}
		if (m_type == "公司类型")
		{
			strsql = "select * from Firm where FType like '%" + m_key + "%'";
		}
		if (m_type == "公司简述")
		{
			strsql = "select * from Firm where FInfo like '%" + m_key + "%'";
		}
		if (m_type == "公司电话")
		{
			strsql = "select * from Firm where FTel like '%" + m_key + "%'";
		}
	}
	if (type == 2)
	{
		if (m_key == "")
		{
			strsql.Format("SELECT * FROM Drug");
			pRs->Open(_bstr_t(strsql), 1);
			if (!pRs->GetRecordCount())
			{
				m_listPerson.DeleteAllItems();
				return;
			}
			pRs->Open(_bstr_t(strsql), 1);
			RefreshList(*(pRs));
			return;
		}
		if (m_type == "")
		{
			AfxMessageBox("请选择查询类型！");
			return;
		}
		if (m_type == "药品编号")
		{
			strsql = "select * from Drug where DID like '%" + m_key + "%'";
		}
		if (m_type == "药品名称")
		{
			strsql = "select * from Drug where DName like '%" + m_key + "%'";
		}
		if (m_type == "药品成份")
		{
			strsql = "select * from Drug where DComponent like '%" + m_key + "%'";
		}
		if (m_type == "药品效用")
		{
			strsql = "select * from Drug where DEffect like '%" + m_key + "%'";
		}
		if (m_type == "药品简述")
		{
			strsql = "select * from Drug where DInfo like '%" + m_key + "%'";
		}
	}

	pRs->Open(_bstr_t(strsql), 1);
	if (!pRs->GetRecordCount())
	{
		m_listPerson.DeleteAllItems();
		return;
	}
	pRs->Open(_bstr_t(strsql), 1);
	RefreshList(*(pRs));
	// TODO: 在此添加控件通知处理程序代码
}


void CInfoSearch::OnBnClickedChange()
{
	AfxMessageBox("刷新成功！");
	// TODO: 在此添加控件通知处理程序代码
}
