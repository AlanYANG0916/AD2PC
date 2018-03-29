#pragma once
#include "afxsock.h"
#include <fstream>
#include "afxwin.h"
#include "afxcmn.h"


const UINT AD_SERVER_PORT = 8080;
const UINT AD_CLIENT_PORT = 4000;
#define AD_TARGET_IP L"192.168.0.10"

struct DataToAD
{
	BYTE flag;
	float state[6];			//{横摇，纵倾，航向，前向，侧向，升降}
};


struct DataFromAD
{
	BYTE flag;
	//float state[6];			//{横摇，纵倾，航向，前向，侧向，升降}
};


enum
{
	ad_enable = 1,		//使能开关
	ad_lock = 2,		//滑轨解锁
	ad_init = 3,		//初始化
	ad_torun = 4,		//开始工作
	ad_reset = 5,		//归零
	ad_down = 6,       //落下
	ad_working = 7,   //工作中
};

class Ctestad2pcDlg;

class AD2PC :public CAsyncSocket
{
public:
	AD2PC(void);
	~AD2PC(void);

	wchar_t szIP[40];
	UINT nPort;

	bool Init(HWND hWnd);
	bool SendData(DataToAD  *pData);
	void ProcData(DataFromAD *pData);
	bool IsConnected();

	virtual void OnReceive(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);

private:
	Ctestad2pcDlg *m_pDlg;
public:

	void SetParent(Ctestad2pcDlg* pDlg);




public:
	DataFromAD	FromADBuf;				//最近将发向运动平台的数据(从工作站到工控站)
	DataToAD	ToADBuf;		//最近从运动平台获取到的数据(从工控站到工作站)
	DWORD nSendCount;
	DWORD nRecvCount;
};