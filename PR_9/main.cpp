#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    SYSTEM_INFO si;
    GetSystemInfo(&si);
    SIZE_T pageSize = si.dwPageSize;

    cout << "Размер страницы системы: " << pageSize << " байт\n\n";

    LPVOID region = VirtualAlloc(NULL, pageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!region) {
        cout << "Ошибка VirtualAlloc: " << GetLastError() << endl;
        return 1;
    }

    cout << "Регион памяти успешно зарезервирован и зафиксирован\n";
    cout << "Адрес региона: 0x" << hex << uppercase << region << nouppercase << dec << "\n\n";

    FillMemory(region, pageSize, 0x7F);
    cout << "Регион заполнен значением 0x7F\n\n";

    MEMORY_BASIC_INFORMATION mbi;
    SIZE_T queryResult = VirtualQuery(region, &mbi, sizeof(mbi));

    if (queryResult == 0) {
        cout << "Ошибка VirtualQuery: " << GetLastError() << endl;
        VirtualFree(region, 0, MEM_RELEASE);
        return 1;
    }

    cout << "Информация об участке памяти (VirtualQuery):\n";
    cout << fixed << left;
    cout << "  BaseAddress : 0x" << hex << uppercase << mbi.BaseAddress << dec << "\n";
    cout << "  RegionSize : " << mbi.RegionSize << " байт ("
         << mbi.RegionSize / pageSize << " страниц" << ")\n";
    cout << "  State : ";
    switch (mbi.State) {
        case MEM_COMMIT:  cout << "MEM_COMMIT (0x1000) — память зафиксирована\n"; break;
        case MEM_RESERVE: cout << "MEM_RESERVE (0x2000)\n"; break;
        case MEM_FREE:    cout << "MEM_FREE (0x10000)\n"; break;
        default:          cout << "Неизвестно (0x" << hex << mbi.State << ")\n"; dec; break;
    }
    cout << "  AllocationProtect : 0x" << hex << uppercase << mbi.AllocationProtect << dec << " — ";
    switch (mbi.AllocationProtect) {
        case PAGE_READWRITE:   cout << "PAGE_READWRITE\n"; break;
        case PAGE_READONLY:    cout << "PAGE_READONLY\n"; break;
        case PAGE_EXECUTE_READWRITE: cout << "PAGE_EXECUTE_READWRITE\n"; break;
        default:               cout << "другой атрибут защиты\n"; break;
    }

    VirtualFree(region, 0, MEM_RELEASE);

    cout << "\nРегион памяти успешно освобождён.\n";
    return 0;
}