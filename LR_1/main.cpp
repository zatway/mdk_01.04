#include <windows.h>
#include <iostream>
#include <fcntl.h>
#include <io.h>

#pragma comment(lib, "advapi32.lib")

void PrintSystemInfo();
void PrintOSVersion();
std::wstring GetErrorMessage(DWORD errorCode);

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U16TEXT);

    WCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName) / sizeof(WCHAR);
    if (GetComputerNameW(computerName, &size)) {
        std::wcout << L"Имя компьютера: " << computerName << L"\n";
    } else {
        std::wcout << L"Ошибка " << GetErrorMessage(GetLastError()) << L"\n";
    }

    WCHAR userName[256];
    DWORD userSize = sizeof(userName) / sizeof(WCHAR);
    if (GetUserNameW(userName, &userSize)) {
        std::wcout << L"Текущий пользователь: " << userName << L"\n";
    } else {
        std::wcout << L"Ошибка GetUserName: " << GetErrorMessage(GetLastError()) << L"\n";
    }

    WCHAR path[MAX_PATH];

    GetWindowsDirectoryW(path, MAX_PATH);
    std::wcout << L"Каталог Windows: " << path << L"\n";

    GetSystemDirectoryW(path, MAX_PATH);
    std::wcout << L"Системный каталог: " << path << L"\n";

    GetTempPathW(MAX_PATH, path);
    std::wcout << L"Каталог временных файлов: " << path << L"\n";

    PrintOSVersion();

    PrintSystemInfo();

    return 0;
}

void PrintOSVersion()
{
    typedef NTSTATUS(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);
    HMODULE hNtdll = GetModuleHandleW(L"ntdll.dll");
    if (!hNtdll) return;

    auto RtlGetVersion = (RtlGetVersionPtr)GetProcAddress(hNtdll, "RtlGetVersion");
    if (!RtlGetVersion) return;

    RTL_OSVERSIONINFOW ver = { sizeof(ver) };
    if (RtlGetVersion(&ver) == 0) {
        std::wcout << L"\nВерсия операционной системы:\n";
        std::wcout << L"Major: " << ver.dwMajorVersion
                   << L"Minor: " << ver.dwMinorVersion
                   << L"Build: " << ver.dwBuildNumber
                   << L"Platform: " << ver.dwPlatformId << L"\n";

        if (ver.dwMajorVersion == 10 && ver.dwBuildNumber >= 22000)
            std::wcout << L" Windows 11\n";
        else if (ver.dwMajorVersion == 10 && ver.dwBuildNumber >= 10240)
            std::wcout << L" Windows 10\n";
        else if (ver.dwMajorVersion == 6 && ver.dwMinorVersion == 3)
            std::wcout << L" Windows 8.1\n";
        else if (ver.dwMajorVersion == 6 && ver.dwMinorVersion == 2)
            std::wcout << L" Windows 8\n";
        else if (ver.dwMajorVersion == 6 && ver.dwMinorVersion == 1)
            std::wcout << L" Windows 7\n";
    }
}

void PrintSystemInfo()
{
    SYSTEM_INFO si;
    GetNativeSystemInfo(&si);

    std::wcout << L"\nСистемная информация:\n";
    std::wcout << L"  Количество логических процессоров: " << si.dwNumberOfProcessors << L"\n";
    std::wcout << L"  Размер страницы памяти: " << si.dwPageSize << L" байт\n";
    std::wcout << L"  Минимальный адрес приложения: 0x" << std::hex << si.lpMinimumApplicationAddress << L"\n";
    std::wcout << L"  Максимальный адрес приложения: 0x" << std::hex << si.lpMaximumApplicationAddress << L"\n";
    std::wcout << L"  Маска активных процессоров: 0x" << std::hex << si.dwActiveProcessorMask << L"\n";
    std::wcout << L"  Уровень процессора: " << si.wProcessorLevel << L"\n";
    std::wcout << L"  Архитектура: ";

    switch (si.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64:   std::wcout << L"x64 AMD \n"; break;
        case PROCESSOR_ARCHITECTURE_INTEL:   std::wcout << L"INTEL\n"; break;
        case PROCESSOR_ARCHITECTURE_ARM:     std::wcout << L"ARM\n"; break;
        default:                             std::wcout << L"Неизвестно (" << si.wProcessorArchitecture << L")\n";
    }
}

std::wstring GetErrorMessage(DWORD errorCode)
{
    WCHAR* msg = nullptr;
    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        nullptr, errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&msg, 0, nullptr);

    std::wstring result = msg ? msg : L"Неизвестная ошибка";
    if (msg) LocalFree(msg);
    return result;
}