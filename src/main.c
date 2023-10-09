#define UNICODE
#include <windows.h>

HWND label;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    SYSTEMTIME st;

    switch (uMsg) {
        case WM_CREATE:
            SetWindowPos(hwnd, NULL, 0, 0, 100, 100, SWP_NOMOVE);
            break;
        case WM_SIZE:
            WORD w = LOWORD(lParam);
            WORD h = HIWORD(lParam);
            MoveWindow(label, 0, 0, w, h, 1);
            break;
        case WM_LBUTTONUP:
        case WM_CLOSE:
            PostQuitMessage(0);
            break;
        case WM_TIMER:
            GetSystemTime(&st);
            LONG beatSeconds = 10 * (3600 + (st.wHour * 3600) +
                                     (st.wMinute * 60) + st.wSecond);
            beatSeconds %= 864000;
            DOUBLE beats = beatSeconds / 86.4;

            /* Hey, Aaron -- isn't this nuts?

            Well, these are the lengths I will travel to avoid importing the
            MSVC C runtime libraries, and therefore make this a self-contained
            pure Win32 binary. */

            WCHAR buf[7] = {L'@'};

            buf[1] = L'0' + ((WORD)(beats / 1000) % 10);
            buf[2] = L'0' + ((WORD)(beats / 100) % 10);
            buf[3] = L'0' + ((WORD)(beats / 10) % 10);
            buf[4] = L'.';
            buf[5] = L'0' + ((WORD)beats % 10);
            SetWindowText(label, (LPCWSTR)(&buf));
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"INSOM_WNDCLASS";
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClass(&wc);

    SetProcessDPIAware();

    HWND hwnd =
        CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_NOACTIVATE | WS_EX_APPWINDOW |
                           WS_EX_PALETTEWINDOW,
                       L"INSOM_WNDCLASS", L".beat", WS_OVERLAPPED | WS_BORDER,
                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                       CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    if (hwnd == NULL) return -1;

    label = CreateWindowEx(0, L"STATIC", L"IDK",
                           SS_CENTER | SS_CENTERIMAGE | WS_VISIBLE | WS_CHILD,
                           0, 0, 300, 300, hwnd, NULL, hInstance, NULL);
    if (label == NULL) return -1;

    ShowWindow(hwnd, nCmdShow);
    SetTimer(hwnd, 10522, 100, NULL);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (!IsDialogMessage(hwnd, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    KillTimer(hwnd, 10522);

    return 0;
}
