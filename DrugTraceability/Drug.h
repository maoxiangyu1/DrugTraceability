#pragma once
class CDrug
{
public:
	char DrugID[11];//ҩƷID
	char Name[20];//����
	char Component[40];//�ɷ�
	char HowEat[40];//ʹ�÷���
	char Effect[60];//ҩЧ
	CTime StartTime;//��������
	CTime EndTime;//��������
	BOOL Register(char DrugID, char Name, char Component, char HowEat[40], char Effect, CTime StartTime, CTime EndTime);
	BOOL WriteOff(char DrugID);
	CDrug();
	~CDrug();
};
