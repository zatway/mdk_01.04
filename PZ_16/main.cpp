#include <windows.h>
#include <iostream>

using namespace std;

void ReadStringValue(HKEY hKey, const char* valueName)
{
    char buffer[512];
    DWORD bufferSize = sizeof(buffer);
    DWORD type;

    if (RegQueryValueExA(hKey, valueName, NULL, &type,
        (LPBYTE)buffer, &bufferSize) == ERROR_SUCCESS)
    {
        if (type == REG_SZ)
            cout << valueName << ": " << buffer << endl;
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    HKEY hKey;

    cout << "Информация об ОС" << endl;
    if (RegOpenKeyExA(
        HKEY_LOCAL_MACHINE,
        "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
        0,
        KEY_READ,
        &hKey) == ERROR_SUCCESS)
    {
        ReadStringValue(hKey, "ProductName");
        ReadStringValue(hKey, "EditionID");
        ReadStringValue(hKey, "CurrentBuild");
        ReadStringValue(hKey, "SystemRoot");
        RegCloseKey(hKey);
    }

    cout << "\nИнформация о BIOS" << endl;
    if (RegOpenKeyExA(
        HKEY_LOCAL_MACHINE,
        "HARDWARE\\DESCRIPTION\\System\\BIOS",
        0,
        KEY_READ,
        &hKey) == ERROR_SUCCESS)
    {
        ReadStringValue(hKey, "BIOSVendor");
        ReadStringValue(hKey, "BIOSVersion");
        ReadStringValue(hKey, "SystemManufacturer");
        RegCloseKey(hKey);
    }

    cout << "\nАвтозагрузка" << endl;
    if (RegOpenKeyExA(
        HKEY_LOCAL_MACHINE,
        "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
        0,
        KEY_READ,
        &hKey) == ERROR_SUCCESS)
    {
        char valueName[256];
        BYTE data[512];
        DWORD valueSize, dataSize, type;
        DWORD index = 0;

        while (true)
        {
            valueSize = sizeof(valueName);
            dataSize = sizeof(data);

            if (RegEnumValueA(
                hKey,
                index,
                valueName,
                &valueSize,
                NULL,
                &type,
                data,
                &dataSize) != ERROR_SUCCESS)
                break;

            cout << valueName << " -> " << data << endl;
            index++;
        }
        RegCloseKey(hKey);
    }

    system("pause");
    return 0;
}
