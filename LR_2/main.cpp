#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

int main()
{
    SetConsoleOutputCP(65001);
    _setmode(_fileno(stdout), _O_U16TEXT);

    WCHAR fileName[MAX_PATH];
    HMODULE hExe = GetModuleHandleW(NULL);

    GetModuleFileNameW(hExe, fileName, MAX_PATH);
    std::wcout << L"EXE модуль:\n";
    std::wcout << L"Дескриптор: " << hExe << L"\n";
    std::wcout << L"Полное имя: " << fileName << L"\n";

    HMODULE hUser32 = GetModuleHandleW(L"user32.dll");
    GetModuleFileNameW(hUser32, fileName, MAX_PATH);
    std::wcout << L"\nDLL модуль user32.dll:\n";
    std::wcout << L"Дескриптор: " << hUser32 << L"\n";
    std::wcout << L"Полное имя: " << fileName << L"\n";

    DWORD pid = GetCurrentProcessId();
    std::wcout << L"\nИдентификатор процесса: " << pid << L"\n";

    HANDLE hPseudo = GetCurrentProcess();
    std::wcout << L"Псевдодескриптор: " << hPseudo << L"\n";

    HANDLE hDup;
    DuplicateHandle(
        hPseudo,
        hPseudo,
        hPseudo,
        &hDup,
        0,
        FALSE,
        DUPLICATE_SAME_ACCESS
    );
    std::wcout << L"Дескриптор (DuplicateHandle): " << hDup << L"\n";

    HANDLE hOpen = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    std::wcout << L"Дескриптор (OpenProcess): " << hOpen << L"\n";

    CloseHandle(hOpen);
    std::wcout << L"Закрыт дескриптор OpenProcess\n";

    CloseHandle(hDup);
    std::wcout << L"Закрыт дескриптор DuplicateHandle\n";

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32W pe;
    pe.dwSize = sizeof(pe);

    std::wcout << L"\nСписок процессов:\n";
    int processCount = 0;

    if (Process32FirstW(snap, &pe))
    {
        do {
            std::wcout << L"PID: " << pe.th32ProcessID
                       << L" Потоков: " << pe.cntThreads
                       << L" Имя: " << pe.szExeFile << L"\n";
            processCount++;
        } while (Process32NextW(snap, &pe) && processCount < 3);
    }

    HANDLE snapThreads = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

    THREADENTRY32 te;
    te.dwSize = sizeof(te);

    std::wcout << L"\nСписок потоков:\n";
    int threadCount = 0;
    if (Thread32First(snapThreads, &te))
    {
        do {
            std::wcout << L"TID: " << te.th32ThreadID
                       << L" PID: " << te.th32OwnerProcessID
                       << L"\n";
            threadCount++;
        } while (Thread32Next(snapThreads, &te) && threadCount > 3);
    }

    HANDLE snapModules = CreateToolhelp32Snapshot(
        TH32CS_SNAPMODULE, pid);

    MODULEENTRY32W me;
    me.dwSize = sizeof(me);

    std::wcout << L"\nМодули текущего процесса:\n";
    if (Module32FirstW(snapModules, &me))
    {
        do {
            std::wcout << L"Имя: " << me.szModule
                       << L" Адрес: " << me.modBaseAddr
                       << L" Размер: " << me.modBaseSize
                       << L"\n";
        } while (Module32NextW(snapModules, &me));
    }

    CloseHandle(snap);
    CloseHandle(snapThreads);
    CloseHandle(snapModules);

    return 0;
}
