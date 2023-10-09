#define UNICODE
#include <windows.h>

HWND label;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            SetWindowPos(hwnd, NULL, 0, 0, 300, 300, SWP_NOMOVE);
            break;
        case WM_SIZE:
            WORD w = LOWORD(lParam);
            WORD h = HIWORD(lParam);
            SetWindowText(label, L"Hello, world!");
            MoveWindow(label, 0, 0, w, h, 1);
            break;
        case WM_CLOSE:
            PostQuitMessage(0);
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

    HWND hwnd =
        CreateWindowEx(0, L"INSOM_WNDCLASS", L"INSOM", WS_OVERLAPPEDWINDOW,
                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                       CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    if (hwnd == NULL) return -1;

    label = CreateWindowEx(0, L"STATIC", L"IDK",
                           SS_CENTER | SS_CENTERIMAGE | WS_VISIBLE | WS_CHILD,
                           0, 0, 300, 300, hwnd, NULL, hInstance, NULL);
    if (label == NULL) return -1;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (!IsDialogMessage(hwnd, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}
