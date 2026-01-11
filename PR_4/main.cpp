#include <windows.h>
#include <iostream>
#include <iomanip>
#include <string>

CRITICAL_SECTION g_csDatabase;

class Database {
public:
    Database() {
        InitializeCriticalSection(&g_csDatabase);
    }

    ~Database() {
        DeleteCriticalSection(&g_csDatabase);
    }

    void SaveData(const std::string &symbol, const std::string &threadName) {
        EnterCriticalSection(&g_csDatabase);

        std::cout << threadName << " - SaveData - Started\n";

        std::cout << threadName << " - SaveData - working\n";

        for (int i = 0; i < 30; ++i) {
            std::cout << symbol;
            std::cout.flush();
            Sleep(80);
        }

        std::cout << "\n";
        std::cout << threadName << " - SaveData - ended\n";

        LeaveCriticalSection(&g_csDatabase);
    }
};

static Database db;

DWORD WINAPI WorkerThread1(LPVOID lpParam) {
    const std::string name = "worker thread #1";

    std::cout << name << " - started\n";
    std::cout << name << " - Calling Database.SaveData\n";

    db.SaveData("x", name);

    std::cout << name << " - Returned from SaveData\n";

    return 0;
}

DWORD WINAPI WorkerThread2(LPVOID lpParam) {
    const std::string name = "worker thread #2";

    std::cout << name << " - started\n";
    std::cout << name << " - Calling Database.SaveData\n";

    db.SaveData("0", name);

    std::cout << name << " - Returned from SaveData\n";

    return 0;
}

int main() {
    std::cout << "main - creating worker threads\n\n";

    HANDLE hThread1 = CreateThread(NULL, 0, WorkerThread1, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, WorkerThread2, NULL, 0, NULL);

    if (hThread1 == NULL || hThread2 == NULL) {
        std::cerr << "Ошибка создания потоков!\n";
        return 1;
    }

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);

    std::cout << "\nВсе потоки завершили работу.\n\n";

    system("pause");
    return 0;
}
