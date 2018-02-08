#include "ThreadMain.h"


CThreadMain::CThreadMain()
{
}


CThreadMain::~CThreadMain()
{
}

void CThreadMain::GetInfo(){
	m_sock.m_port = 8424;
	strcpy(m_sock.Address, "127.0.0.1");	
}

SOCKET CThreadMain::Run(){
	SOCKET s = m_sock.StartSocket();
	while (1){
		if (s == NULL){
			printf("Connect Error!\n");
			continue;
		}
		else{
			printf("Connect success");
			return s;
		}
	}
}