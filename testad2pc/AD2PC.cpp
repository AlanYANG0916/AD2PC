#include "stdafx.h"
#include "AD2PC.h"
#include "testad2pcDlg.h"
#include "testad2pc.h"


AD2PC::AD2PC(void)
:m_pDlg(NULL)
{
	memset(&FromADBuf, 0, sizeof(DataFromAD));		//最近将发向运动平台的数据,设置存储空间ToDOFBuf，初始化为0，存储空间的大小为DataToDOF的size
	memset(&ToADBuf, 0, sizeof(DataToAD));	//最近从运动平台获取到的数据

}


AD2PC::~AD2PC(void)
{
}





bool AD2PC::Init(HWND hWnd)
{
	if (!AfxSocketInit())
		return false;
	//tcp服务器
	//if(!Create(AD_SERVER_PORT,SOCK_STREAM,FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE,L"192.168.0.131"))	//SOCK_DGRAM:UDP,SOCK_STREAM :TCP
	//return false;
	Bind(8080U,L"192.168.0.131");

	Listen();
	//OnAccept();
	//udp服务器
	//if (!Create(11000, SOCK_DGRAM, FD_READ | FD_WRITE))	//SOCK_DGRAM:UDP,SOCK_STREAM :TCP
		//return false;

	return true;
}

void AD2PC::OnAccept(int nErrorCode) {
	if (nErrorCode == 0) m_pDlg->OnAccept();
}

bool AD2PC::SendData(DataToAD  *pData)//发送数据
{
	//if (pData != NULL &&  IsConnected())
	//{
		//if(bEmergence && pData->nCmd != S_CMD_Back2MID)//如果处于紧急状态或者目前位置不是中间态，则返回错误
		//return false;

		//if (pData != &ToADBuf)
			//memcpy(&ToADBuf, pData, sizeof(DataToAD));

		//nSendCount++;
		int ii = 0;


		ii = Send(pData, sizeof(DataToAD), 0);//szIP,MSG_DONTROUTE，调用该成员函数sendto的数据发送到特定目标，若成功发送则返回1
		//ii = SendTo(pData, sizeof(DataToAD), AD_CLIENT_PORT, AD_TARGET_IP);//szIP,MSG_DONTROUTE，调用该成员函数sendto的数据发送到特定目标，若成功发送则返回1

		return ii>0;
	//}

	//return false;
}

void AD2PC::OnReceive(int nErrorCode)//接收数据
{
	DataFromAD dh;
	int a = -1, b = -1;
	a = ReceiveFrom(&dh, sizeof(DataFromAD), CString(szIP), nPort, 0);
	a = Receive(&dh,1,0);

	//if ((b = ReceiveFrom(&dh, sizeof(DataFromAD), CString(szIP), nPort, MSG_DONTROUTE)) == int(-1))
		//if(a!=0)
	//{
		//nRecvCount++;
		ProcData(&dh);
	//}
	a = 0;
}

void AD2PC::ProcData(DataFromAD *pData)
{
	//if(pData == NULL || pData->nCheckID != ToDOFBuf.nCheckID)
	//return;

	if (pData != &FromADBuf)
		memcpy(&FromADBuf, pData, sizeof(DataFromAD));//复制缓冲区之间的字节。
}

bool AD2PC::IsConnected()
{
	return m_hSocket != SOCKET_ERROR;
}

void AD2PC::SetParent(Ctestad2pcDlg* pDlg) {
	m_pDlg  = pDlg;
}