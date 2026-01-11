#include <windows.h>
#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");

    TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = MAX_COMPUTERNAME_LENGTH + 1;

    if (GetComputerName(computerName, &size))
    {
        std::wcout << L"Имя компьютера: " << computerName << std::endl;
    }

    TCHAR windowsDir[MAX_PATH];
    GetWindowsDirectory(windowsDir, MAX_PATH);
    std::wcout << L"Каталог Windows: " << windowsDir << std::endl;

    TCHAR systemDir[MAX_PATH];
    GetSystemDirectory(systemDir, MAX_PATH);
    std::wcout << L"Системный каталог: " << systemDir << std::endl;

    TCHAR tempDir[MAX_PATH];
    GetTempPath(MAX_PATH, tempDir);
    std::wcout << L"Временный каталог: " << tempDir << std::endl;

    OSVERSIONINFO osInfo;
    osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    if (GetVersionEx(&osInfo))
    {
        std::wcout << L"Версия ОС: "
                   << osInfo.dwMajorVersion << L"."
                   << osInfo.dwMinorVersion << std::endl;
    }

    system("pause");
    return 0;
}
