#pragma once
class CMySocket
{
public:
	CMySocket();
	~CMySocket();
public:
	void Clean();
	int RecvCommand(SOCKET socket, char* buf, int bytes);
	int SendCommand(SOCKET socket, const char* buf, int bytes);
};

