#pragma once

#include <Windows.h>

const CLSID LxssUserSessionFactory = { 0x4f476546, 0xb412, 0x4579, 0xb64c, 0x123df331e3d6 };
const IID LxssUserSession = { 0x536a6bcf, 0xfe04, 0x41d9, 0xb978, 0xdcaca9a9b5b9 };
const GUID LxssInstance = { 0x8f9e8123, 0x58d4, 0x484a, 0xac25, 0x7ef7d5f7448f };
struct LXSS_STD_HANDLES {
	/* For old console ? */
	/* HI POS === 1 */
	HANDLE STDIN; /* STDIN (create pipe) */
	HANDLE STDOUT; /* STDOUT */
	HANDLE STDERR; /* STDERR */
	/* all zero if LXSS_CONSOLE_DATA used */
};
struct LXSS_CONSOLE_DATA { 
	/* unclear... */
	/* low 32 bits of LXSS_STD_HANDLES (?) */
	DWORD IN_BUF; /* For keys (arrors...) */
	DWORD OUT_BUF; /* STDOUT (console) */
	DWORD IN_EVENT; /* for example resize.... */
	/* Buffer.EventType != 1, Buffer.EventType == 4 */
	
	WORD SCREEN_WIDTH;
	WORD SCREEN_HEIGHT;
	/* GetConsoleScreenBufferInfo */
	/*
	  LOWORD(v2) = ConsoleScreenBufferInfo.srWindow.Right - ConsoleScreenBufferInfo.srWindow.Left + 1;
      HIWORD(v2) = ConsoleScreenBufferInfo.srWindow.Bottom - ConsoleScreenBufferInfo.srWindow.Top + 1;
	*/
};
class ILxssInstance : public IUnknown {
public:
	virtual int GetConfiguration(int**) = 0;
	virtual int GetId(_GUID *) = 0;
	virtual int QueryState(int *) = 0;
	virtual int SetState(int, int *) = 0;
	virtual int CreateLxProcess(
		char const * exec /* in linux */ ,
		unsigned long argc, 
		char const ** args,
		unsigned long env_count, 
		char const ** env,
		char const * current_path /* maybe */,
		unsigned long keep_runing, /* 0 for bash -c xxx 1 for other */
		LXSS_STD_HANDLES *_LXSS_STD_HANDLES,
		LXSS_CONSOLE_DATA *_LXSS_CONSOLE_DATA,
		unsigned long uid /* =0 or read from reg */, 
		HANDLE * process /* &v =0 */) = 0;
	virtual int RegisterAdssBusServer(char const *, unsigned long *) = 0;
	virtual int ConnectAdssBusServer(char const *, unsigned long *) = 0;
	virtual ~ILxssInstance() = 0;
	virtual int GetState(void) = 0;
	virtual int StartSelf(void) = 0;
	virtual int GetSuspendState(void)=0;
};

class ILxssSession : public IUnknown {
public:
	virtual int GetCurrentInstance(ILxssInstance**) = 0;
	virtual int StartDefaultInstance(_GUID const &, void * *) = 0;
	virtual int SetState(int state /* 1 to 8 */, unsigned long) = 0;
	virtual int QueryState(int *state) = 0;
	virtual int InitializeFileSystem(wchar_t const *, wchar_t const *, wchar_t const *) = 0;
	virtual ~ILxssSession() = 0;
};