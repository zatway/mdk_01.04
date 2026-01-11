#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <iomanip>

void printHandle(const wchar_t* prefix, HANDLE h)
{
    std::wcout << prefix << L"0x"
               << std::hex << std::uppercase << std::setw(16) << std::setfill(L'0')
               << reinterpret_cast<uintptr_t>(h) << std::dec << std::nouppercase << L"\n";
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U8TEXT);
    DWORD pid = GetCurrentProcessId();
    std::wcout << L"Идентификатор текущего процесса (PID): "
               << pid << L"\n";

    HANDLE pseudoHandle = GetCurrentProcess();
    std::wcout << L"Псевдодескриптор текущего процесса: ";
    printHandle(L"", pseudoHandle);

    HANDLE realHandleFromDup = nullptr;
    BOOL success = DuplicateHandle(
        pseudoHandle,
        pseudoHandle,
        pseudoHandle,
        &realHandleFromDup,
        0,
        FALSE,
        DUPLICATE_SAME_ACCESS
    );

    if (!success)
    {
        std::wcerr << L"Ошибка DuplicateHandle: " << GetLastError() << L"\n";
        return 1;
    }

    std::wcout << L"Настоящий дескриптор DuplicateHandle: ";
    printHandle(L"", realHandleFromDup);

    HANDLE realHandleFromOpen = OpenProcess(
        PROCESS_QUERY_LIMITED_INFORMATION | SYNCHRONIZE,
        FALSE,
        pid
    );

    if (realHandleFromOpen == nullptr)
    {
        std::wcerr << L"Ошибка OpenProcess: " << GetLastError() << L"\n";
    }
    else
    {
        std::wcout << L"Настоящий дескриптор OpenProcess: ";
        printHandle(L"", realHandleFromOpen);
    }

    std::wcout << L"\n";

    std::wcout << L"Закрываем дескриптор DuplicateHandle ";
    if (realHandleFromOpen != nullptr)
    {
        if (CloseHandle(realHandleFromOpen))
            std::wcout << L"успешно\n";
        else
            std::wcerr << L"ошибка " << GetLastError() << L"\n";
    }
    else
    {
        std::wcout << L"(дескриптор не был получен)\n";
    }

    std::wcout << L"Закрываем дескриптор OpenProcess ";
    if (CloseHandle(realHandleFromDup))
        std::wcout << L"успешно\n";
    else
        std::wcerr << L"ошибка " << GetLastError() << L"\n";

    std::wcout << L"\n";

    return 0;
}