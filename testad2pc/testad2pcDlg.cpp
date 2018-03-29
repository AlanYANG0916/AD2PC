
// testad2pcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "testad2pc.h"
#include "testad2pcDlg.h"
#include "afxdialogex.h"
#include "math.h"
#include "mmsystem.h"
#include<ATLBASE.H>
#include<iomanip>
#include <io.h>

#pragma comment(lib,"winmm.lib")//预编译静态链接库
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ctestad2pcDlg 对话框



Ctestad2pcDlg::Ctestad2pcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TESTAD2PC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctestad2pcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ctestad2pcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Ctestad2pcDlg::OnBtnStart)
	ON_BN_CLICKED(IDCANCEL, &Ctestad2pcDlg::OnBtnStop)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Ctestad2pcDlg 消息处理程序

BOOL Ctestad2pcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_Svr.SetDlg(this);
	//m_edtPort.SetWindowText("6100");
	//m_Root = m_treeClient.InsertItem("客户端", TVI_ROOT);
	//GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Ctestad2pcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ctestad2pcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Ctestad2pcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Ctestad2pcDlg::OnRcv(CClientSock* pConn)
{
	if (NULL != pConn)
	{
		char rcvBuf[513] = { 0 };
		int nRcved = 0;
		nRcved = pConn->Receive(rcvBuf, 512);
		if (SOCKET_ERROR != nRcved)
		{
			pConn->Send(rcvBuf, strlen(rcvBuf));
		}
	}
}

//有客户端断开
void Ctestad2pcDlg::OnClientClose(int nErrCode, CClientSock* pConn)
{
	//123
}

//有新连接
void Ctestad2pcDlg::OnAccept(int nErrCode)
{
	if (0 == nErrCode)
	{
		CClientSock* pNewConn = new CClientSock;
		pNewConn->SetDlg(this);
		m_Svr.Accept(*pNewConn);
	}
	else
	{
	}
}

void Ctestad2pcDlg::OnBtnStart()
{
	// TODO: Add your control notification handler code here
	//CString strPort=L"8080";
	//m_edtPort.GetWindowText(strPort);
	if (!m_Svr.Create(8080U, SOCK_STREAM, FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE))
	{
		MessageBox(L"Create Socket Error!");
		return;
	}
	if (!m_Svr.Listen())
	{
		int nErrorCode = m_Svr.GetLastError();
		if (nErrorCode != WSAEWOULDBLOCK)
		{
			MessageBox(L"Listen Error!");
			m_Svr.Close();
			PostQuitMessage(0);
			return;
		}
	}
	//GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
}

void Ctestad2pcDlg::OnBtnStop()
{
	// TODO: Add your control notification handler code here

	//while (!m_ConnList.IsEmpty())
	//{
		//CClientSock* pConn = (CClientSock*)m_ConnList.RemoveHead();
		//delete pConn;
	//}

	//HTREEITEM hCurrent = m_treeClient.GetNextItem(m_Root, TVGN_CHILD);
	//while (NULL != hCurrent)
	//{
		//m_treeClient.DeleteItem(hCurrent);
		//hCurrent = m_treeClient.GetNextItem(hCurrent, TVGN_NEXT);
	//}

	m_Svr.Close();
	//GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	//GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
}
