
// testad2pcDlg.h : ͷ�ļ�
//



#pragma once
#include "MySocket.h"
#include "ClientSock.h"


// Ctestad2pcDlg �Ի���
class Ctestad2pcDlg : public CDialogEx
{
// ����
public:
	Ctestad2pcDlg(CWnd* pParent = NULL);	// ��׼���캯��

	HTREEITEM m_Root;
	CMySocket m_Svr;
	void OnAccept(int nErrCode);
	void OnClientClose(int nErrCode, CClientSock* pConn);
	void OnRcv(CClientSock* pConn);

// �Ի�������

	enum { IDD = IDD_TESTAD2PC_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnStart();
	afx_msg void OnBtnStop();

	DECLARE_MESSAGE_MAP()



};
