#include "stdafx.h"
#include "MySocket.h"


CMySocket::CMySocket()
{
}


CMySocket::~CMySocket()
{
}


void CMySocket::Clean(){
	::WSACleanup();
}