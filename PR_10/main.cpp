#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

void PrintRegionContent(LPVOID ptr, SIZE_T bytes) {
    BYTE* p = static_cast<BYTE*>(ptr);
    cout << "Первые 16 байт региона: ";
    for (SIZE_T i = 0; i < min(bytes, SIZE_T(16)); ++i) {
        cout << hex << setw(2) << setfill('0') << static_cast<int>(p[i]) << " ";
        if ((i + 1) % 8 == 0) cout << "  ";
    }
    cout << dec << endl;
}

void PrintError(DWORD errorCode) {
    LPVOID lpMsgBuf = nullptr;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        nullptr,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0,
        nullptr);

    cout << "Ошибка: " << errorCode << " — " << (lpMsgBuf ? static_cast<char*>(lpMsgBuf) : "неизвестная ошибка") << endl;
    if (lpMsgBuf) LocalFree(lpMsgBuf);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    SYSTEM_INFO si;
    GetSystemInfo(&si);
    SIZE_T pageSize = si.dwPageSize;

    cout << "Размер страницы системы: " << pageSize << " байт\n\n";

    LPVOID region = VirtualAlloc(nullptr, pageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!region) {
        PrintError(GetLastError());
        return 1;
    }

    cout << "Регион успешно зарезервирован и зафиксирован\n";
    cout << "Адрес региона: 0x" << hex << uppercase << region << nouppercase << dec << "\n\n";

    FillMemory(region, pageSize, 0x7F);
    cout << "Регион заполнен значением 0x7F\n\n";

    cout << "Содержимое региона до изменения защиты:\n";
    PrintRegionContent(region, pageSize);

    DWORD oldProtect;
    if (!VirtualProtect(region, pageSize, PAGE_READONLY, &oldProtect)) {
        PrintError(GetLastError());
        VirtualFree(region, 0, MEM_RELEASE);
        return 1;
    }

    cout << "\nУспешно изменена защита региона:\n";
    cout << "  Старая защита: 0x" << hex << uppercase << oldProtect << dec << " (PAGE_READWRITE)\n";
    cout << "  Новая защита:  PAGE_READONLY (0x02)\n\n";

    cout << "Попытка записи в регион с защитой PAGE_READONLY (ожидается нарушение доступа)...\n";
    if (IsBadWritePtr(region, 1)) {
        cout << "Запись запрещена — память недоступна для записи (PAGE_READONLY)\n";
    } else {
        cout << "Запись разрешена (это ошибка!)\n";
    }

    if (!VirtualProtect(region, pageSize, oldProtect, &oldProtect)) {
        PrintError(GetLastError());
    }
    else {
        cout << "Исходная защита успешно восстановлена\n";
    }

    if (!VirtualFree(region, 0, MEM_RELEASE)) {
        PrintError(GetLastError());
    }
    else {
        cout << "Регион успешно освобождён\n";
    }

    return 0;
}