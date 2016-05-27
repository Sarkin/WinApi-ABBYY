#include "MainWindow.h"

#include <functional>

#include "resource.h"

const LPCWSTR CMainWindow::class_name_ = L"Main Window";
const HICON CMainWindow::icon32_ = (HICON)LoadImage(GetModuleHandle(0), L"icon32.ico",
    IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
const HICON CMainWindow::icon64_ = (HICON)LoadImage(GetModuleHandle(0), L"icon64.ico",
    IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);

CMainWindow::CMainWindow() {
    g_snake_ = new CSnakeGame(50, 50);
    speed_ = 1;
}

CMainWindow::~CMainWindow() {
    delete g_snake_;
}

bool CMainWindow::RegisterClassW() {
    WNDCLASSEX wnd_class = {};
    wnd_class.cbSize = sizeof(WNDCLASSEX);
    wnd_class.lpfnWndProc = windowProc;
    wnd_class.hInstance = GetModuleHandle(NULL);
    wnd_class.lpszClassName = class_name_;
    wnd_class.hIcon = icon64_;
    wnd_class.hIconSm = icon32_;
    wnd_class.lpszMenuName = MAKEINTRESOURCE(ID_GAME_MENU);
    return RegisterClassEx(&wnd_class);
}

bool CMainWindow::Create() {
    HMONITOR hmon = MonitorFromWindow(NULL,
        MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = { sizeof(mi) };
    if (!GetMonitorInfo(hmon, &mi)) return NULL;
    DWORD dwStyle = WS_OVERLAPPEDWINDOW&~(WS_MAXIMIZEBOX | WS_THICKFRAME);
    std::pair<int, int > grid_size = g_snake_->GetGrid().GetGridSize();
    int tile_sz = g_snake_->GetGrid().GetTileSize();
    RECT rc = { 0, 0, grid_size.second * tile_sz, grid_size.first * tile_sz };
    AdjustWindowRect(&rc, dwStyle, TRUE);
    handle_ = CreateWindowEx(0, class_name_, L"Snake Game",  dwStyle | WS_VISIBLE, 0, 
        0, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, GetModuleHandle(0), this);
    return (handle_ != NULL);
}

HWND CMainWindow::CreateFullscreenWindow() {
    HMONITOR hmon = MonitorFromWindow(NULL,
        MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = { sizeof(mi) };
    if (!GetMonitorInfo(hmon, &mi)) return NULL;
    DWORD dwStyle = WS_POPUP|WS_VISIBLE;
    int tile_sz = g_snake_->GetGrid().GetTileSize();
    RECT rc = mi.rcMonitor;
    AdjustWindowRect(&rc, dwStyle, FALSE);
    handle_ = CreateWindowEx(0, class_name_, L"Snake Game", WS_POPUP | WS_VISIBLE,
        rc.left,
        rc.top,
        rc.right - rc.left,
        rc.bottom - rc.top, NULL, NULL, GetModuleHandle(0), this);
    return handle_;
}

void CMainWindow::Show(int cmdShow) {
    ShowWindow(handle_, cmdShow);
}

void CMainWindow::OnCreate() {
    SetWindowText(handle_, L"Sarkin's Snake Game");
}

void CMainWindow::OnDestroy() {
    DestroyIcon(icon32_);
    DestroyIcon(icon64_);
}

void CMainWindow::OnNCCreate(HWND handle) {
    handle_ = handle;
}

bool CMainWindow::confirmClose() {
    int clicked = MessageBox(handle_, L"Exit the game?", L"Confirmation", MB_YESNO);
    switch (clicked) {
    case IDYES:
        return true;
    case IDNO:
        return false;
    default:
        return false;
    }
}

void CMainWindow::OnClose() {
    if (confirmClose()) {
        DestroyWindow(handle_);
    }
}

int CMainWindow::GetSpeed() {
    return speed_;
}

void CMainWindow::OnCommand(WPARAM wParam, LPARAM lParam) {
    switch (LOWORD(wParam)) {
    case ID_GAME_EXIT:
        OnClose();
        break;
    case ID_GAME_PAUSE:
        g_snake_->Pause();
        break;
    case ID_GAME_NEWGAME:
        delete g_snake_;
        g_snake_ = new CSnakeGame(50, 50);
        break;
    case ID_GAME_SETTINGS:
        showSettings();
        break;
    }
}

void CMainWindow::showSettings() {
    settings_dialog_.Create(handle_);
}

void CMainWindow::ApplySettings(const CSettings& settings) {
    speed_ = settings.speed;
    nplayers_ = settings.nplayers;
}

CSettings CMainWindow::GetSettings() {
    CSettings ret;
    ret.speed = speed_;
    ret.nplayers = nplayers_;
    return ret;
}

void CMainWindow::Update() {
    g_snake_->Update();
}

void CMainWindow::Draw() {
    RECT client_rect;
    GetClientRect(handle_, &client_rect);

    HDC window_dc = GetDC(handle_);

    HDC display_buffer_dc = CreateCompatibleDC(window_dc);
    HBITMAP display_buffer = CreateCompatibleBitmap(window_dc, client_rect.right - client_rect.left,
        client_rect.bottom - client_rect.top);
    HGDIOBJ old_display_buffer = SelectObject(display_buffer_dc, display_buffer);

    g_snake_->Draw(display_buffer_dc);

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
        OnClose();
        break;
    case WM_CREATE:
        OnCreate();
        break;
    case WM_KEYDOWN:
        g_snake_->HandleInput(wParam, lParam);
        break;
    case WM_COMMAND:
        OnCommand(wParam, lParam);
        break;
    default:
        return DefWindowProc(handle, message, wParam, lParam);
    }
    return 0;
}
