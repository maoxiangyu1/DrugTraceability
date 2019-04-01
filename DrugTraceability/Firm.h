#pragma once
struct firminfo
{
	char FirmID[8]; //��˾ID
	int FirmType;   //��˾����  1-ҩ��� 2-������ 3-��תվ 4-ҩ��
	char Name[30];    //����
	char Address[80]; //��ַ
	char Tel[11];//�绰
	char LeaderName[8]; //�쵼��
	CTime StartTime; //ע������
	CTime EndTime; //ʧЧ����
	char Info[100]; //��˾���
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
