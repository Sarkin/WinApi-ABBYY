#include "MainWindow.h"

const LPCWSTR CMainWindow::class_name_ = L"Main Window";

CMainWindow::CMainWindow() : g_snake_(50, 50) {
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
    DWORD dwStyle = WS_OVERLAPPEDWINDOW&~(WS_MAXIMIZEBOX | WS_THICKFRAME);
    std::pair<int, int > grid_size = g_snake_.GetGridSize();
    int tile_sz = g_snake_.GetTileSize();
    RECT rc = { 0, 0, grid_size.second * tile_sz, grid_size.first * tile_sz };
    AdjustWindowRect(&rc, dwStyle, FALSE);
    handle_ = CreateWindowEx(0, class_name_, L"Snake Game",  dwStyle | WS_VISIBLE, 0,
        0, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, GetModuleHandle(0), this);
    return (handle_ != NULL);
}

void CMainWindow::Show(int cmdShow) {
    ShowWindow(handle_, cmdShow);
}

void CMainWindow::OnCreate() {
}

void CMainWindow::OnDestroy() {
}

void CMainWindow::OnNCCreate(HWND handle) {
    handle_ = handle;
}

void CMainWindow::Update() {
    g_snake_.Update();
}

void CMainWindow::Draw() {
    RECT client_rect;
    GetClientRect(handle_, &client_rect);

    HDC window_dc = GetDC(handle_);

    HDC display_buffer_dc = CreateCompatibleDC(window_dc);
    HBITMAP display_buffer = CreateCompatibleBitmap(window_dc, client_rect.right - client_rect.left,
        client_rect.bottom - client_rect.top);
    HGDIOBJ old_display_buffer = SelectObject(display_buffer_dc, display_buffer);

    g_snake_.Draw(display_buffer_dc);

    BitBlt(window_dc, client_rect.left, client_rect.top, client_rect.right - client_rect.left,
        client_rect.bottom - client_rect.top, display_buffer_dc, 0, 0, SRCCOPY);

    SelectObject(display_buffer_dc, old_display_buffer);
    
    DeleteObject(display_buffer);
    DeleteDC(display_buffer_dc);

    ReleaseDC(handle_, window_dc);
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
