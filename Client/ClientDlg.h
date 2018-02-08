
// ClientDlg.h : 头文件
//

#pragma once
#include "MySocket.h"

// CClientDlg 对话框
class CClientDlg : public CDialogEx
{
// 构造
public:
	CClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENT_DIALOG };

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
	DECLARE_MESSAGE_MAP()
public:
	SOCKET s;
	CMySocket m_Mysock;
	CToolBar m_toolbar;
	CImageList m_imagelist;
	CStatusBar m_statusbar;
public:
	static DWORD WINAPI Client(LPVOID self);
	void UpdataMain(int port);
	void init();
	afx_msg void OnClose();
};
