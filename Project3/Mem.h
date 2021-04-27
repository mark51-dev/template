#pragma once
#include <Windows.h>
#include <TlHelp32.h>

class Mem
{
public:
	Mem(char* procName, int bufferSize = 32);
	~Mem(void);

	void Open(DWORD accessRight = PROCESS_ALL_ACCESS);
	void Close();
	DWORD getPID();
private:
	void GetPID();
	char* m_pName;
	HANDLE m_hProc;
	DWORD m_pID;
	byte* m_buffer;
	int m_bufferSize;
};

