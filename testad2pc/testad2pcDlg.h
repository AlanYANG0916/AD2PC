
// testad2pcDlg.h : 头文件
//



#pragma once
#include "MySocket.h"
#include "ClientSock.h"


// Ctestad2pcDlg 对话框
class Ctestad2pcDlg : public CDialogEx
{
// 构造
public:
	Ctestad2pcDlg(CWnd* pParent = NULL);	// 标准构造函数

	HTREEITEM m_Root;
	CMySocket m_Svr;
	void OnAccept(int nErrCode);
	void OnClientClose(int nErrCode, CClientSock* pConn);
	void OnRcv(CClientSock* pConn);

// 对话框数据

	enum { IDD = IDD_TESTAD2PC_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnStart();
	afx_msg void OnBtnStop();

	DECLARE_MESSAGE_MAP()



};
