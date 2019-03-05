#pragma once

//加密狗错误
#define   DONGLE_SUCCESS                       0x00000000          // 操作成功
#define   DONGLE_NOT_FOUND                     0xF0000001          // 未找到指定的设备
#define   DONGLE_INVALID_HANDLE				   0xF0000002		   // 无效的句柄
#define   DONGLE_INVALID_PARAMETER			   0xF0000003		   // 参数错误
#define   DONGLE_COMM_ERROR					   0xF0000004		   // 通讯错误
#define   DONGLE_INSUFFICIENT_BUFFER		   0xF0000005		   // 缓冲区空间不足
#define   DONGLE_NOT_INITIALIZED               0xF0000006		   // 产品尚未初始化 (即没设置PID)
#define   DONGLE_ALREADY_INITIALIZED		   0xF0000007		   // 产品已经初始化 (即已设置PID)
#define   DONGLE_ADMINPIN_NOT_CHECK			   0xF0000008		   // 开发商密码没有验证
#define   DONGLE_USERPIN_NOT_CHECK			   0xF0000009		   // 用户密码没有验证
#define   DONGLE_INCORRECT_PIN				   0xF000FF00		   // 密码不正确 (后2位指示剩余次数)
#define   DONGLE_PIN_BLOCKED				   0xF000000A		   // PIN码已锁死
#define   DONGLE_ACCESS_DENIED				   0xF000000B		   // 访问被拒绝 
#define   DONGLE_FILE_EXIST					   0xF000000E		   // 文件已存在
#define   DONGLE_FILE_NOT_FOUND				   0xF000000F		   // 未找到指定的文件
#define	  DONGLE_READ_ERROR                    0xF0000010          // 读取数据错误
#define	  DONGLE_WRITE_ERROR                   0xF0000011          // 写入数据错误
#define	  DONGLE_FILE_CREATE_ERROR             0xF0000012          // 创建文件错误
#define	  DONGLE_FILE_READ_ERROR               0xF0000013          // 读取文件错误
#define	  DONGLE_FILE_WRITE_ERROR              0xF0000014          // 写入文件错误
#define	  DONGLE_FILE_DEL_ERROR                0xF0000015          // 删除文件错误
#define   DONGLE_FAILED                        0xF0000016          // 操作失败
#define   DONGLE_CLOCK_EXPIRE                  0xF0000017          // 加密锁时钟到期
#define   DONGLE_ERROR_UNKNOWN		           0xFFFFFFFF		   // 未知的错误

//
class Execption
{
public:
	static CString ISERROR(DWORD WINAPI e);
	Execption();
	~Execption();
};

