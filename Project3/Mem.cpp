#include "Mem.h"


Mem::Mem(char* procName, int bufferSize): m_pID(0)
{
	int len = strlen(procName) + 1;
	m_pName = new char[len];
	strcpy_s(m_pName, len, procName);

	m_buffer = new byte[bufferSize];
}

Mem::~Mem(void)
{
	delete[] m_pName;
	delete[] m_buffer;
}

void Mem::GetPID()
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pInfo;
    pInfo.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &pInfo))
    {
        while (Process32Next(snapshot, &pInfo))
        {
            if (_stricmp(m_pName, pInfo.szExeFile) == 0)
            {
                m_pID = pInfo.th32ProcessID;
                CloseHandle(snapshot);
                return;
            }
        }
    }
    CloseHandle(snapshot);
    m_pID = 0;
}


void Mem::Open(DWORD accessRight)
{
    GetPID();
	m_hProc = OpenProcess(accessRight, false, m_pID);
}

void Mem::Close()
{
	CloseHandle(m_hProc);
}

DWORD Mem::getPID()
{
	return m_pID;
}
