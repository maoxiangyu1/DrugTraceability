// Firmsearch.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Firmsearch.h"
#include "afxdialogex.h"
#include "Firmchange.h"

// CFirmsearch 对话框

IMPLEMENT_DYNAMIC(CFirmsearch, CDialogEx)

CFirmsearch::CFirmsearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFirmsearch::IDD, pParent)
{

	EnableAutomation();

	m_key = _T("");
	m_type = _T("");
}

CFirmsearch::~CFirmsearch()
{
}

void CFirmsearch::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CFirmsearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_key);
	DDX_CBString(pDX, IDC_COMBO1, m_type);
	DDX_Control(pDX, IDC_LIST1, m_listPerson);
}


BEGIN_MESSAGE_MAP(CFirmsearch, CDialogEx)
	ON_BN_CLICKED(IDSEARCH, &CFirmsearch::OnBnClickedSearch)
	ON_BN_CLICKED(IDDEL, &CFirmsearch::OnBnClickedDel)
	ON_BN_CLICKED(IDCHANGE, &CFirmsearch::OnBnClickedChange)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFirmsearch, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IFirmsearch 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {F1FE3C91-F101-4ABF-A0FE-26F0FEA2B290}
static const IID IID_IFirmsearch =
{ 0xF1FE3C91, 0xF101, 0x4ABF, { 0xA0, 0xFE, 0x26, 0xF0, 0xFE, 0xA2, 0xB2, 0x90 } };

BEGIN_INTERFACE_MAP(CFirmsearch, CDialogEx)
	INTERFACE_PART(CFirmsearch, IID_IFirmsearch, Dispatch)
END_INTERFACE_MAP()


// CFirmsearch 消息处理程序


BOOL CFirmsearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_listPerson.ModifyStyle(0L,LVS_REPORT);   
	m_listPerson.ModifyStyle(LVS_SHOWSELALWAYS,0L);
	m_listPerson.ModifyStyle(0L,LVS_SHOWSELALWAYS);    //高亮显示被选中项
	m_listPerson.SetExtendedStyle(LVS_EX_FULLROWSELECT| //允许整行选中
		LVS_EX_HEADERDRAGDROP|  //允许整列拖动
		LVS_EX_GRIDLINES|     //画出网格线
		LVS_EX_ONECLICKACTIVATE|     //单击选中项
		LVS_EX_FLATSB);    //扁平风格显示滚动条
	m_listPerson.InsertColumn(0,"公司编号",LVCFMT_LEFT,130,0);
	m_listPerson.InsertColumn(1,"公司名称",LVCFMT_LEFT,130,1);
	m_listPerson.InsertColumn(2,"公司负责人",LVCFMT_LEFT,130,2);
	m_listPerson.InsertColumn(3,"公司地址",LVCFMT_LEFT,130,3);
	m_listPerson.InsertColumn(4,"公司电话",LVCFMT_LEFT,130,4);
	m_listPerson.InsertColumn(5,"公司类别",LVCFMT_LEFT,130,5);
	m_listPerson.InsertColumn(6,"公司简介",LVCFMT_LEFT,130,6);
	m_listPerson.InsertColumn(7,"注册时间",LVCFMT_LEFT,130,7);
	CString strsql;
	strsql.Format("SELECT * FROM Firm");
	m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
	if(!m_admin->m_login->pRs->GetRecordCount())
	{
		m_listPerson.DeleteAllItems();
		return TRUE;
	}
	m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
	RefreshList(*(m_admin->m_login->pRs));
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
BOOL CFirmsearch::RefreshList(CADORecordset& recordset)
{
	m_listPerson.DeleteAllItems();
	
	if(!recordset.IsOpen())
		return FALSE;
	
	recordset.MoveFirst();
    CString FID,Fname,Fboss,Faddress,Ftel,Finfo,Fdate,Ftype;
	int indexofList=0;
	while( !(recordset.IsEOF()) )
	{    
		recordset.GetFieldValue("FID",FID);
		recordset.GetFieldValue("Fname",Fname);
		recordset.GetFieldValue("Fboss",Fboss);
		recordset.GetFieldValue("Faddress",Faddress);
		recordset.GetFieldValue("Ftel",Ftel);
		recordset.GetFieldValue("Ftype",Ftype);
		recordset.GetFieldValue("Finfo",Finfo);
		recordset.GetFieldValue("Fdate",Fdate);
		
		

		
		m_listPerson.InsertItem(indexofList,FID);
		m_listPerson.SetItemText(indexofList,1, Fname);
		m_listPerson.SetItemText(indexofList,2,Fboss);
		m_listPerson.SetItemText(indexofList,3,Faddress);
		m_listPerson.SetItemText(indexofList,4,Ftel);
		m_listPerson.SetItemText(indexofList,5,Ftype);
		m_listPerson.SetItemText(indexofList,6,Finfo);
		m_listPerson.SetItemText(indexofList,7,Fdate);

		indexofList+=1;
		recordset.MoveNext();
	}
	recordset.MoveFirst();
	
	return TRUE;
}

void CFirmsearch::OnBnClickedSearch()
{
	UpdateData(true);
	CString strsql;
	if(m_key=="")
	{
		strsql.Format("SELECT * FROM Firm");
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		if(!m_admin->m_login->pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return;
		}
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		RefreshList(*(m_admin->m_login->pRs));
		return;
	}
	if(m_type=="公司ID")
	{
		strsql.Format("SELECT * FROM Firm where FID='%s'",m_key);
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		if(!m_admin->m_login->pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return;
		}
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		RefreshList(*(m_admin->m_login->pRs));
		return;
	}
	if(m_type=="公司名称")
	{
		strsql.Format("SELECT * FROM Firm where Fname='%s'",m_key);
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		if(!m_admin->m_login->pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return;
		}
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		RefreshList(*(m_admin->m_login->pRs));
		return;
	}
	if(m_type=="公司负责人")
	{
		strsql.Format("SELECT * FROM Firm where Fboss='%s'",m_key);
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		if(!m_admin->m_login->pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return;
		}
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		RefreshList(*(m_admin->m_login->pRs));
		return;
	}
	if(m_type=="公司类别")
	{
		strsql = "select * from Firm where Ftype like '%"+m_key+"%'";
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		if(!m_admin->m_login->pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return;
		}
		//strsql.Format("SELECT * FROM Firm where Fboss='%s'",m_key);
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		RefreshList(*(m_admin->m_login->pRs));
		return;
	}
	if(m_type=="公司地址")
	{
		strsql = "select * from Firm where Faddress like '%"+m_key+"%'";
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		if(!m_admin->m_login->pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return;
		}
		//strsql.Format("SELECT * FROM Firm where Fboss='%s'",m_key);
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		RefreshList(*(m_admin->m_login->pRs));
		return;
	}
	if(m_type=="公司简介")
	{
		strsql = "select * from Firm where Finfo like '%"+m_key+"%'";
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		if(!m_admin->m_login->pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return;
		}
		//strsql.Format("SELECT * FROM Firm where Fboss='%s'",m_key);
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		RefreshList(*(m_admin->m_login->pRs));
		return;
	}
}


void CFirmsearch::OnBnClickedDel()
{
	POSITION pos = m_listPerson.GetFirstSelectedItemPosition();
	int nItem = m_listPerson.GetNextSelectedItem(pos);
	CString s=m_listPerson.GetItemText(nItem,0);
	if(s=="")
	{
		AfxMessageBox("请选中您要删除的信息！");
		return;
	}
	CString S;
	S.Format("delete Firm where FID='%s'",s);
	if(m_admin->m_login->pDB->Execute(S)==TRUE)
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


void CFirmsearch::OnBnClickedChange()
{
	POSITION pos = m_listPerson.GetFirstSelectedItemPosition();
	int nItem = m_listPerson.GetNextSelectedItem(pos);
	m_FID=m_listPerson.GetItemText(nItem,0);
	if(m_FID=="")
	{
		AfxMessageBox("请选中要更改的公司信息！");
		return;
	}
	m_Fname=m_listPerson.GetItemText(nItem,1);
	m_Fboss=m_listPerson.GetItemText(nItem,2);
	m_Faddress=m_listPerson.GetItemText(nItem,3);
	m_Ftel=m_listPerson.GetItemText(nItem,4);
	m_Finfo=m_listPerson.GetItemText(nItem,6);
	CFirmchange dlg;
	dlg.m_firmsearch=this;
	if(dlg.DoModal()==0)
	{
		CString s;
		s.Format("SELECT * FROM Firm");
		m_admin->m_login->pRs->Open(_bstr_t(s),1);
		if(!m_admin->m_login->pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return;
		}
		m_admin->m_login->pRs->Open(_bstr_t(s),1);
		RefreshList(*(m_admin->m_login->pRs));
	}
}
