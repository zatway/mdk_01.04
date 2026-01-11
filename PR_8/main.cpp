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

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    SYSTEM_INFO si;
    GetSystemInfo(&si);

    DWORD pageSize = si.dwPageSize;
    DWORD allocGranularity = si.dwAllocationGranularity;

    cout << "Размер страницы системы: " << pageSize << " байт\n";
    cout << "Гранулярность выделения регионов: " << allocGranularity << " байт\n\n";

    SIZE_T regionSize = 2ULL * pageSize;

    LPVOID region1 = VirtualAlloc(NULL, regionSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!region1) {
        cout << "Ошибка резервирования региона 1: " << GetLastError() << endl;
        return 1;
    }

    LPVOID region2 = VirtualAlloc(NULL, regionSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!region2) {
        cout << "Ошибка резервирования региона 2: " << GetLastError() << endl;
        VirtualFree(region1, 0, MEM_RELEASE);
        return 1;
    }

    cout << "Регион 1 зарезервирован по адресу: 0x" << hex << uppercase << region1 << endl;
    cout << "Регион 2 зарезервирован по адресу: 0x" << region2 << nouppercase << dec << "\n\n";

    cout << "Обнуление региона 1" << endl;
    ZeroMemory(region1, regionSize);

    cout << "Введите число от 0 до 127 для заполнения региона 2: ";
    int userInput = 0;
    cin >> userInput;

    BYTE fillValue = (userInput >= 0 && userInput <= 127) ? static_cast<BYTE>(userInput) : 42;
    if (userInput < 0 || userInput > 127) {
        cout << "Некорректное значение → используется 42 по умолчанию\n";
    }

    cout << "Заполнение региона 2 значением 0x" << hex << uppercase << static_cast<int>(fillValue) << dec << " (FillMemory)..." << endl;
    FillMemory(region2, regionSize, fillValue);

    cout << "\nСодержимое региона 1:" << endl;
    PrintRegionContent(region1, regionSize);

    cout << "\nСодержимое региона 2:" << endl;
    PrintRegionContent(region2, regionSize);

    VirtualFree(region1, 0, MEM_RELEASE);
    VirtualFree(region2, 0, MEM_RELEASE);

    return 0;
}