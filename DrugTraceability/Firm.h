#pragma once
struct firminfo
{
	char FirmID[8]; //公司ID
	int FirmType;   //公司类型  1-药监局 2-生产商 3-中转站 4-药店
	char Name[30];    //名称
	char Address[80]; //地址
	char Tel[11];//电话
	char LeaderName[8]; //领导人
	CTime StartTime; //注册日期
	CTime EndTime; //失效日期
	char Info[100]; //公司简介
};
class CFirm
{
public:
	struct firminfo firm;
	BOOL Register(char FirmID, int FirmType, char Name, char Address, char Tel, char LeaderName, CTime StartTime, CTime EndTime, char Info);
	BOOL WriteOff(char FiemID);
	CFirm();
	~CFirm();
};

