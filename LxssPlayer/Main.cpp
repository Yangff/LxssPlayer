#include "Lxss.h"

const char * CODE[] = { "HOSTTYPE=x86_64" ,"TERM=xterm",  "LANG=en_US.UTF-8",  "SHELL=/bin/bash" };

int main() {
	CoInitializeEx(NULL, NULL);
	CoInitializeSecurity(0i64, -1, 0i64, 0i64, 0, 3u, 0i64, 0x20u, 0i64);
	ILxssSession *session = 0;
	HRESULT rst = CoCreateInstance(LxssUserSessionFactory,
		0i64,
		4u,
		LxssUserSessionFactory,
		(LPVOID*)&session);
	ILxssInstance *ins;
	rst = session->StartDefaultInstance(LxssInstance, (LPVOID*)&ins);
	HANDLE hProcess;
	ins->CreateLxProcess( /* ... */ );
	CoUninitialize();
}
// uid from 
// RegOpenCurrentUser(0x20006u, &hKey);
//Software\\Microsoft\\Windows\\CurrentVersion\\Lxss
// DefaultUid