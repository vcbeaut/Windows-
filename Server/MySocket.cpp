#include "MySocket.h"


CMySocket::CMySocket()
{
}


CMySocket::~CMySocket()
{
}

SOCKET CMySocket::StartSocket()
{
	WSAData wsa;
	if (::WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("初始化SOCKET失败");
		return NULL;
	}
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		int er = WSAGetLastError();
		printf("创建SOCKET失败,err number: %d",er);
		return NULL;
	}
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_port);
	addr.sin_addr.S_un.S_addr = inet_addr(Address);
	if (connect(s, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		printf("Connect Error\n");
		DWORD e = GetLastError();
		printf("LastError:%d\n", e);
		s = NULL;
	}
	else
	{
		//printf("Connect Success!\n");
		return s;
	}
}