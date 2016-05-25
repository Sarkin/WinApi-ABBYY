#include "MainWindow.h"

const LPCWSTR CMainWindow::class_name_ = L"Main Window";

CMainWindow::CMainWindow() {
}

CMainWindow::~CMainWindow() {
}

bool CMainWindow::RegisterClassW() {
    WNDCLASSEX wnd_class = {};
    wnd_class.cbSize = sizeof(WNDCLASSEX);
    wnd_class.lpfnWndProc = windowProc;
    wnd_class.hInstance = GetModuleHandle(NULL);
    wnd_class.lpszClassName = class_name_;
    return RegisterClassEx(&wnd_class);
}

bool CMainWindow::Create() {
    handle_ = CreateWindowEx(0, class_name_, L"Notepad", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, GetModuleHandle(0), this);
    return (handle_ != NULL);
}

void CMainWindow::Show(int cmdShow) {
    ShowWindow(handle_, cmdShow);
}

void CMainWindow::OnCreate() {
    g_snake_ = CSnakeGame(GetModuleHandle(0), handle_);
}

void CMainWindow::OnDestroy() {
}

void CMainWindow::OnNCCreate(HWND handle) {
    handle_ = handle;
}

void CMainWindow::Update() {
    g_snake_.Update();
}

HWND CMainWindow::GetHandle() {
    return handle_;
}

LRESULT _stdcall CMainWindow::windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_NCCREATE: {
        CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
        CMainWindow* notepad_window = (CMainWindow*)cs->lpCreateParams;
        SetLastError(0);
        if (SetWindowLongPtr(handle, GWLP_USERDATA, (LONG)notepad_window) == 0 &&
            GetLastError() != 0) {
            return FALSE;
        }
        notepad_window->OnNCCreate(handle);
        return TRUE;
    }
    default:
        CMainWindow* notepad_window = (CMainWindow*)GetWindowLongPtr(handle, GWLP_USERDATA);
        if (notepad_window) {
            return notepad_window->localWindowProc(handle, message, wParam, lParam);
        }
        return DefWindowProc(handle, message, wParam, lParam);
    }
    return 0;
}

LRESULT _stdcall CMainWindow::localWindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        OnDestroy();
        PostQuitMessage(0);
        break;
    case WM_CLOSE:
        DestroyWindow(handle_);
        break;
    case WM_CREATE:
        OnCreate();
        break;
    default:
        return DefWindowProc(handle, message, wParam, lParam);
    }
    return 0;
}
