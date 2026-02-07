#include <windows.h>
#include <iostream>

int shared_resource = 0;
CRITICAL_SECTION cs;
HANDLE hMutex;
HANDLE hEvent;

DWORD WINAPI SectionTask(LPVOID lpParam) {
    for (int i = 0; i < 100000; i++) {
        EnterCriticalSection(&cs);
        shared_resource++;
        LeaveCriticalSection(&cs);
    }
    return 0;
}

DWORD WINAPI MutexTask(LPVOID lpParam) {
    WaitForSingleObject(hMutex, INFINITE);
    const char* text = (const char*)lpParam;
    for (int i = 0; text[i] != '\0'; i++) {
        std::cout << text[i];
        Sleep(20);
    }
    std::cout << std::endl;
    ReleaseMutex(hMutex);
    return 0;
}

DWORD WINAPI EventTask(LPVOID lpParam) {
    std::cout << "Ожидания сигнала" << std::endl;
    WaitForSingleObject(hEvent, INFINITE);
    std::cout << "Сигнал получен" << std::endl;
    return 0;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "Критические секции" << std::endl;
    InitializeCriticalSection(&cs);
    HANDLE h1 = CreateThread(NULL, 0, SectionTask, NULL, 0, NULL);
    HANDLE h2 = CreateThread(NULL, 0, SectionTask, NULL, 0, NULL);
    WaitForSingleObject(h1, INFINITE);
    WaitForSingleObject(h2, INFINITE);
    std::cout << "Значение: " << shared_resource << std::endl << std::endl;

    std::cout << "Мьютексы" << std::endl;
    hMutex = CreateMutex(NULL, FALSE, NULL);
    HANDLE m1 = CreateThread(NULL, 0, MutexTask, (void*)"ПЕРВЫЙ ПОТОК", 0, NULL);
    HANDLE m2 = CreateThread(NULL, 0, MutexTask, (void*)"второй поток", 0, NULL);
    WaitForSingleObject(m1, INFINITE);
    WaitForSingleObject(m2, INFINITE);
    std::cout << std::endl;

    std::cout << "События" << std::endl;
    hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    HANDLE e1 = CreateThread(NULL, 0, EventTask, NULL, 0, NULL);
    std::cout << "Enter для вызова события" << std::endl;
    std::cin.get();
    SetEvent(hEvent);
    WaitForSingleObject(e1, INFINITE);

    DeleteCriticalSection(&cs);
    CloseHandle(hMutex);
    CloseHandle(hEvent);
    CloseHandle(h1); CloseHandle(h2);
    CloseHandle(m1); CloseHandle(m2);
    CloseHandle(e1);

    return 0;
}