#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>



int get_pid_by_name(const char* processName)
{
    PROCESSENTRY32 process_entry = { sizeof(PROCESSENTRY32) };
    HANDLE process_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (Process32First(process_snapshot, &process_entry)) 
    {
        do
        {
            if (!strcmp(process_entry.szExeFile, processName))
            {
                return process_entry.th32ProcessID;
            }
        } while (Process32Next(process_snapshot, &process_entry));
    }
    CloseHandle(process_snapshot);
    return 0;
}

DWORD get_module_pointer(const char* module_name, DWORD process_id_)
{
    MODULEENTRY32 module_entry = { sizeof(MODULEENTRY32) };

    HANDLE modules_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_id_);
    if (Module32First(modules_snapshot, &module_entry))
    {
        do
        {
            if (!strcmp(module_entry.szModule, module_name))
            {
                return (DWORD)module_entry.modBaseAddr;
            }
        } while (Module32Next(modules_snapshot, &module_entry));
    }
    CloseHandle(modules_snapshot);
    return 0;
}


int main()
{

	DWORD PID = get_pid_by_name("csgo.exe");
    DWORD moduleBaseAddr = get_module_pointer("client.dll", PID);

    DWORD dwLocalPlayer = moduleBaseAddr + 0xD8C2BC;
    DWORD LocalPlayer;
    DWORD health;

    HANDLE game = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

    ReadProcessMemory(game, (LPCVOID)(dwLocalPlayer), &LocalPlayer, sizeof(dwLocalPlayer), NULL);
    ReadProcessMemory(game, (LPCVOID)(LocalPlayer + 0x100), &health, sizeof(LocalPlayer), NULL);

    
    std::cout << "HEALTH IS " << health << std::endl;
    system("pause");

    return 0;
}