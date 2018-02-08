#pragma once

#include "stdafx.h"
class CMySocket
{
public:
	CMySocket();
	~CMySocket();
	SOCKET StartSocket();
	int MyRecv(SOCKET socket, char* buf, int bytes);
	int MySend(SOCKET socket, const char* buf, int bytes);
	int m_port;
	char Address[160];
};

