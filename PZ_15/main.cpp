#define STRICT
#define WIN32_LEAN_AND_MEAN
#define UNICODE
#define _UNICODE

#include <windows.h>
#include <cstdio>
#include "Library.h"

const wchar_t g_szClassName[] = L"MyWindowClass";

HWND hEditInput;
HWND hEditOutput;
HWND hButton;
HWND hLabelInput;
HWND hLabelOutput;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG msg;
    WNDCLASSEX wndClass = {0};

    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WindowProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = g_szClassName;
    wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wndClass)) return FALSE;

    hWnd = CreateWindow(
            g_szClassName,
            L"Вычисление факториала",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            500, 300,
            NULL, NULL,
            hInstance,
            NULL
    );

    if (hWnd == NULL) return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CREATE:
        {
            HINSTANCE hInst = ((LPCREATESTRUCT)lParam)->hInstance;

            hLabelInput = CreateWindow(
                L"STATIC", L"Введите число n (0-20):",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                20, 20, 300, 20,
                hWnd, NULL, hInst, NULL);

            hLabelOutput = CreateWindow(
                L"STATIC", L"Результат:",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                20, 100, 300, 20,
                hWnd, NULL, hInst, NULL);

            hEditInput = CreateWindow(
                L"EDIT", L"",
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                20, 50, 200, 30,
                hWnd, NULL, hInst, NULL);

            hButton = CreateWindow(
                L"BUTTON", L"Вычислить",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                250, 50, 120, 30,
                hWnd, NULL, hInst, NULL);

            hEditOutput = CreateWindow(
                L"EDIT", L"",
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_READONLY | ES_AUTOHSCROLL,
                20, 130, 400, 30,
                hWnd, NULL, hInst, NULL);

            return 0;
        }

        case WM_COMMAND:
        {
            if (lParam == (LPARAM)hButton && HIWORD(wParam) == BN_CLICKED)
            {
                wchar_t buf[32];
                GetWindowTextW(hEditInput, buf, 32);

                int n = (int)wcstol(buf, NULL, 10);

                unsigned long long res = factorial(n);

                wchar_t outBuf[64];
                if (n < 0)
                    swprintf(outBuf, 64, L"Ошибка: отрицательное число");
                else if (n > 20 && res == 0)
                    swprintf(outBuf, 64, L"Переполнение (n слишком большой)");
                else if (res == 0 && n > 0)
                    swprintf(outBuf, 64, L"Переполнение");
                else
                    swprintf(outBuf, 64, L"%llu", res);

                SetWindowTextW(hEditOutput, outBuf);
            }
            return 0;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}