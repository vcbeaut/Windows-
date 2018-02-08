
// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientDlg 对话框



CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CClientDlg 消息处理程序

void CClientDlg::init(){

	WSAData wsa;
	if (::WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		MessageBox(_T("WSAStartup error"));
		return;
	}

	s  = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		int er = WSAGetLastError();
		return;
	}

	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.S_un.S_addr = INADDR_ANY;
	service.sin_port = htons(8424);

	//----------------------
	// Bind the socket.
	if (bind(s, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		closesocket(s);
		return;
	}
	if (listen(s, SOMAXCONN) == SOCKET_ERROR)
	{
		int er = WSAGetLastError();
		closesocket(s);
	}
	while (1){
		SOCKET SerSock;
		SOCKADDR_IN Seraddr;
		int Seraddrsize = sizeof(Seraddr);
		SerSock = accept(s, (SOCKADDR*)&Seraddr, &Seraddrsize);
		if (SerSock == INVALID_SOCKET)
		{
			continue;
		}
		MessageBox(_T("success"));
		return;
	}
}

DWORD WINAPI CClientDlg::Client(LPVOID self){
	CClientDlg *t = (CClientDlg*)self;
	t->init();
	return 0;
}

BOOL CClientDlg::OnInitDialog()
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

	// TODO:  在此添加额外的初始化代码
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);  //IDR_MENU1为菜单栏ID号  
	SetMenu(&menu);

	UpdataMain(8424);
	::CloseHandle(CreateThread(0, 0, Client, (LPVOID)this, 0, 0));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClientDlg::UpdataMain(int port){
	//加载CImageList图像列表
	m_imagelist.Create(32, 32, ILC_COLOR24 | ILC_MASK, 1, 1);
	CBitmap bmp;
	for (int i = 0; i < 8; ++i){
		bmp.LoadBitmapW(IDB_BITMAP1 + i);
		m_imagelist.Add(&bmp, RGB(255, 255, 255));
		bmp.DeleteObject();
	}

	//创建工具栏
	UINT IDArray[8] = { 10001, 10002, 10003, 10004, 10005, 10006, 10007, 10008 };
	m_toolbar.CreateEx(this);
	m_toolbar.SetButtons(IDArray, 8);
	m_toolbar.SetSizes(CSize(60, 56), CSize(24, 24));
	m_toolbar.SetButtonText(0, _T("文件管理"));
	m_toolbar.SetButtonText(1, _T("屏幕监控"));
	m_toolbar.SetButtonText(2, _T("超级终端"));
	m_toolbar.SetButtonText(3, _T("进程管理"));
	m_toolbar.SetButtonText(4, _T("视频监控"));
	m_toolbar.SetButtonText(5, _T("卸载主机"));
	m_toolbar.SetButtonText(6, _T("程序设置"));
	m_toolbar.SetButtonText(7, _T("关于软件"));
	m_toolbar.GetToolBarCtrl().SetImageList(&m_imagelist);

	//创建状态栏
	UINT b[2] = { 1001, 1002 };
	m_statusbar.CreateEx(this);
	m_statusbar.SetIndicators(b, 2);
	m_statusbar.SetPaneInfo(0, b[0], SBPS_NOBORDERS, 400);
	m_statusbar.SetPaneInfo(1, b[1], SBPS_NOBORDERS, 180);
	CString portStr;
	portStr.Format(_T("监听端口:%d"), port);
	m_statusbar.SetPaneText(0, portStr);
	m_statusbar.SetPaneText(1, _T("在线主机:0台"));
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);	//显示工具栏和状态栏


}


void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDlg::OnPaint()
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int t = MessageBox(_T("确定要退出程序吗？"), _T("提示"), MB_YESNO | MB_ICONINFORMATION);
	if (t = IDYES){
		::closesocket(s);
		m_Mysock.Clean();
	}
	CDialogEx::OnClose();
}
