#pragma once
class CDrug
{
public:
	char DrugID[11];//药品ID
	char Name[20];//名称
	char Component[40];//成分
	char HowEat[40];//使用方法
	char Effect[60];//药效
	CTime StartTime;//生产日期
	CTime EndTime;//过期日期
	BOOL Register(char DrugID, char Name, char Component, char HowEat[40], char Effect, CTime StartTime, CTime EndTime);
	BOOL WriteOff(char DrugID);
	CDrug();
	~CDrug();
};

