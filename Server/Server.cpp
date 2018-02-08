// Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MySocket.h"
#include "ThreadMain.h"
void Server(){
	CThreadMain Thread_Main;
	Thread_Main.GetInfo();
	Thread_Main.Run();
	

}

int _tmain(int argc, _TCHAR* argv[])
{
	Server();
	Sleep(1000 * 20);
	return 0;
}

