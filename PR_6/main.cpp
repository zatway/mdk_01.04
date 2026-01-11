#include <windows.h>
#include <iostream>
#include <iomanip>
#include <string>

std::string FormatBytes(ULONGLONG bytes)
{
    const char* units[] = { "Б", "КБ", "МБ", "ГБ", "ТБ" };
    int unitIndex = 0;
    double value = static_cast<double>(bytes);

    while (value >= 1024.0 && unitIndex < 4)
    {
        value /= 1024.0;
        ++unitIndex;
    }

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << value << " " << units[unitIndex];
    return oss.str();
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    MEMORYSTATUSEX memStatus = {};
    memStatus.dwLength = sizeof(MEMORYSTATUSEX);

    if (!GlobalMemoryStatusEx(&memStatus))
    {
        std::cerr << "Ошибка вызова GlobalMemoryStatusEx: " << GetLastError() << "\n";
        system("pause");
        return 1;
    }

    std::cout << "Состояние памяти системы\n";

    std::cout << "Процент используемой физической памяти: "
              << memStatus.dwMemoryLoad << "%\n\n";

    std::cout << "Физическая память:\n";
    std::cout << "   Всего: " << FormatBytes(memStatus.ullTotalPhys) << "\n";
    std::cout << "   Доступно: " << FormatBytes(memStatus.ullAvailPhys) << "\n";
    std::cout << "   Используется: "
              << FormatBytes(memStatus.ullTotalPhys - memStatus.ullAvailPhys)
              << " (" << memStatus.dwMemoryLoad << "%)\n\n";

    std::cout << "Файл подкачки:\n";
    std::cout << "   Всего: " << FormatBytes(memStatus.ullTotalPageFile) << "\n";
    std::cout << "   Доступно: " << FormatBytes(memStatus.ullAvailPageFile) << "\n";
    std::cout << "   Используется: "
              << FormatBytes(memStatus.ullTotalPageFile - memStatus.ullAvailPageFile) << "\n\n";

    std::cout << "Виртуальная память:\n";
    std::cout << "   Всего: " << FormatBytes(memStatus.ullTotalVirtual) << "\n";
    std::cout << "   Доступно: " << FormatBytes(memStatus.ullAvailVirtual) << "\n\n";

    std::cin.get();

    return 0;
}