
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持


#include<dbt.h>
#pragma   comment   (linker,"/NODEFAULTLIB:libc.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
no_namespace  rename("EOF", "adoEOF"),rename("BOF","adoBOF")

struct Firm
{
	char FirmID[17]; //公司ID
	char Name[30];    //名称
	char Address[60]; //地址
	char LeaderName[20]; //领导人
	char Info[200]; //公司简介
	char Tel[12];//电话
	char StartTime[11]; //注册日期
	int Deadline; //有效期	
	int FirmType;   //公司类型  1-药监局 2-生产商 3-中转站 4-药店
};
struct Drug
{
	char DrugID[11];//药品ID
	char Name[20];//名称
	char Component[40];//成分
	char HowEat[40];//使用方法
	char Effect[60];//药效
	char StartTime[11];//生产日期
	char Info[200]; //简述
	int Deadline;//过期日期
};
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


