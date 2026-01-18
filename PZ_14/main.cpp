#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

const char g_szClassName[] = "MyWindowClass";
COLORREF g_bgColor = RGB(0, 0, 0);

int WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG msg;
    WNDCLASSEX wndClass;

    // Заполнение структуры оконного класса
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wndClass.lpfnWndProc = WindowProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = g_szClassName;
    wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wndClass)) return FALSE;

    hWnd = CreateWindow(
            g_szClassName,
            "Window application",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            800, 600,
            NULL, NULL,
            hInstance,
            NULL
    );

    if (hWnd == NULL) return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    ZeroMemory(&msg, sizeof(MSG));

    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
        }
    }

    UnregisterClass(g_szClassName, hInstance);
    return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            RECT rect;
            GetClientRect(hWnd, &rect);

            HBRUSH hBrush = CreateSolidBrush(g_bgColor);
            FillRect(hdc, &rect, hBrush);
            DeleteObject(hBrush);

            // Текст по центру
            SetTextColor(hdc, RGB(255, 255, 255));
            SetBkMode(hdc, TRANSPARENT);
            DrawText(hdc, "Hello world", -1, &rect,
                     DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            EndPaint(hWnd, &ps);
            return 0;
        }

        case WM_ACTIVATE:
        {
            if (wParam != 0)
                g_bgColor = RGB(0, 0, 255);     // Синий
            else
                g_bgColor = RGB(128, 128, 128); // Серый

            InvalidateRect(hWnd, NULL, TRUE);
            return 0;
        }

        case WM_MOVE:
        {
            g_bgColor = RGB(0, 255, 0);  // Зелёный при перемещении
            InvalidateRect(hWnd, NULL, TRUE);
            return 0;
        }

        case WM_RBUTTONDBLCLK:
        {
            g_bgColor = RGB(255, 0, 0);  // Красный при двойном клике правой кнопкой
            InvalidateRect(hWnd, NULL, TRUE);
            return 0;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}