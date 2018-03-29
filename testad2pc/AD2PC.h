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
	float state[6];			//{��ҡ�����㣬����ǰ�򣬲�������}
};


struct DataFromAD
{
	BYTE flag;
	//float state[6];			//{��ҡ�����㣬����ǰ�򣬲�������}
};


enum
{
	ad_enable = 1,		//ʹ�ܿ���
	ad_lock = 2,		//�������
	ad_init = 3,		//��ʼ��
	ad_torun = 4,		//��ʼ����
	ad_reset = 5,		//����
	ad_down = 6,       //����
	ad_working = 7,   //������
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
	DataFromAD	FromADBuf;				//����������˶�ƽ̨������(�ӹ���վ������վ)
	DataToAD	ToADBuf;		//������˶�ƽ̨��ȡ��������(�ӹ���վ������վ)
	DWORD nSendCount;
	DWORD nRecvCount;
};