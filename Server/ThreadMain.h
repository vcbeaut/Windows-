#pragma once

#include "stdafx.h"
#include "MySocket.h"
class CThreadMain
{
public:
	CThreadMain();
	~CThreadMain();
	void GetInfo();
	SOCKET Run();
private:
	CMySocket m_sock;
};

