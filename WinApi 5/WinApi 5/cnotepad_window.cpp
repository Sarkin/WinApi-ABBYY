#include <Windows.h>

#include "resource.h"
#include "cnotepad_window.h"

const LPCWSTR CNotepadWindow::class_name_ = L"NotepadWindow";
const HICON CNotepadWindow::icon32_ = (HICON)LoadImage(GetModuleHandle(0), L"icon32.ico",
    IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
const HICON CNotepadWindow::icon64_ = (HICON)LoadImage(GetModuleHandle(0), L"icon64.ico",
    IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);

CNotepadWindow::CNotepadWindow() {
    edit_control_ = CEditControlWindow();
    edit_control_changed_ = false;
    current_brush_ = 0;
}

CNotepadWindow::~CNotepadWindow() {
    if (handle_) {
        DestroyWindow(handle_);
    }
}

bool CNotepadWindow::RegisterClassW() {
    WNDCLASSEX wnd_class = { };
    wnd_class.cbSize = sizeof(WNDCLASSEX);
    wnd_class.lpfnWndProc = windowProc;
    wnd_class.hInstance = GetModuleHandle(NULL);
    wnd_class.lpszClassName = class_name_;
    wnd_class.hIcon = icon64_;
    wnd_class.hIconSm = icon32_;
    wnd_class.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU);
    return RegisterClassEx(&wnd_class);
}

void CNotepadWindow::setWindowTitle() {
    wchar_t* title = new wchar_t[256];
    LoadString(GetModuleHandle(0), IDS_WINDOW_TITLE, title, 256);
    SetWindowText(handle_, title);
    delete[] title;
}

void CNotepadWindow::showSettings() {
	settings_dialog_.Create(handle_);
}

bool CNotepadWindow::Create() {
    handle_ = CreateWindowEx(WS_EX_LAYERED, class_name_, L"Notepad", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, GetModuleHandle(0), this);
    SetOpacity(255);
    setWindowTitle();
    edit_control_.SetEditControlText();
    return (handle_ != NULL);
}

void CNotepadWindow::Show(int cmdShow) {
    ShowWindow(handle_, cmdShow);
    edit_control_.Show();
}

void CNotepadWindow::OnDestroy() {
    DestroyIcon(icon32_);
    DestroyIcon(icon64_);
    DeleteObject(current_brush_);
    HFONT font = reinterpret_cast<HFONT>(SendMessage(handle_, WM_GETFONT, 0, 0));
    DeleteObject(font);
    PostQuitMessage(0);
}

void CNotepadWindow::OnNCCreate(HWND handle) {
    handle_ = handle;
}

void CNotepadWindow::OnCreate() {
    edit_control_.Create(handle_);
    font_color_ = RGB(0, 0, 0);
    background_color_ = RGB(255, 255, 255);
    HFONT hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
    SendMessage(edit_control_.GetHandle(), WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
}

void CNotepadWindow::OnSizeChanged() {
    RECT rect;
    GetClientRect(handle_, &rect);
    edit_control_.Resize(rect);
}

bool CNotepadWindow::ConfirmClose() {
    int clicked = MessageBox(handle_, L"Save the text?", L"Confirmation", MB_YESNOCANCEL);
    switch (clicked) {
    case IDYES:
        return saveEditControlContent(edit_control_.GetHandle());
    case IDNO:
        return true;
    case IDCANCEL:
        return false;
    default:
        return false;
    }
}

LRESULT CNotepadWindow::OnColorEdit(HDC hdc) {
    SetBkColor(hdc, background_color_);
    SetTextColor(hdc, font_color_);
    DeleteObject(current_brush_);
    current_brush_ = CreateSolidBrush(background_color_);
    return (LRESULT)current_brush_;
}

void CNotepadWindow::OnClose() {
    if (!edit_control_changed_ || ConfirmClose()) {
        DestroyWindow(handle_);
    }
}

bool CNotepadWindow::saveEditControlContent(HWND edit_control_handle) {
    LRESULT text_length = SendMessage(edit_control_handle, WM_GETTEXTLENGTH, 0, 0);
    wchar_t* text = new wchar_t[text_length + 1];
    SendMessage(edit_control_handle, WM_GETTEXT, text_length + 1, LPARAM(text));

    OPENFILENAME ofn = {};
    wchar_t szFileName[MAX_PATH] = L"";

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = handle_;
    ofn.lpstrFilter = (LPCWSTR)L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = (LPWSTR)szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = (LPCWSTR)L"txt";

    bool saved = GetSaveFileName(&ofn);
    if (saved) {
        HANDLE file_handle = CreateFile(ofn.lpstrFile, GENERIC_WRITE | GENERIC_READ,
            FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
        unsigned short bom = 0xFEFF;
        WriteFile(file_handle, &bom, 2, NULL, NULL);
        WriteFile(file_handle, text, (text_length + 1) * sizeof(wchar_t), NULL, NULL);
        CloseHandle(file_handle);
    }
    delete[] text;
    return saved;
}

void CNotepadWindow::OnCommand(WPARAM wParam, LPARAM lParam) {
    switch (LOWORD(wParam)) {
    case ID_FILE_SAVE:
        saveEditControlContent(edit_control_.GetHandle());
        break;
    case ID_FILE_EXIT:
        OnClose();
        break;
    case ID_VIEW_SETTINGS:
        showSettings();
        break;
    case ID_ACCELERATOR_EXIT:
        OnClose();
        break;
    }
    if (HIWORD(wParam) == EN_CHANGE) {
        edit_control_changed_ = true;
    }
}

HWND CNotepadWindow::GetHandle() {
    return handle_;
}

HWND CNotepadWindow::GetEditControlHandle() {
    return edit_control_.GetHandle();
}

HWND CNotepadWindow::GetSettingsDialogHandle() {
    return settings_dialog_.GetHandle();
}

BYTE CNotepadWindow::GetOpacity() {
    return opacity_;
}

DWORD CNotepadWindow::GetBackgroundColor() {
    return background_color_;
}

DWORD CNotepadWindow::GetFontColor() {
    return font_color_;
}

void CNotepadWindow::SetBackgroundColor(DWORD background_color) {
    background_color_ = background_color;
}

void CNotepadWindow::SetFontColor(DWORD font_color) {
    font_color_ = font_color;
}

void CNotepadWindow::SetOpacity(BYTE opacity) {
    opacity_ = opacity;
    SetLayeredWindowAttributes(handle_, 0, opacity, LWA_ALPHA);
}

LRESULT _stdcall CNotepadWindow::windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_NCCREATE: {
        CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
        CNotepadWindow* notepad_window = (CNotepadWindow*)cs->lpCreateParams;
        SetLastError(0);
        if (SetWindowLongPtr(handle, GWLP_USERDATA, (LONG)notepad_window) == 0 &&
            GetLastError() != 0) {
            return FALSE;
        }
        notepad_window->OnNCCreate(handle);
        return TRUE;
    }
    default:
        CNotepadWindow* notepad_window = (CNotepadWindow*)GetWindowLongPtr(handle, GWLP_USERDATA);
        if (notepad_window) {
            return notepad_window->localWindowProc(handle, message, wParam, lParam);
        }
        return DefWindowProc(handle, message, wParam, lParam);
    }
    return 0;
}

LRESULT _stdcall CNotepadWindow::localWindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        OnDestroy();
        break;
    case WM_CREATE:
        OnCreate();
        break;
    case WM_SIZE:
        OnSizeChanged();
        break;
    case WM_CLOSE:
        OnClose();
        break;
    case WM_COMMAND:
        OnCommand(wParam, lParam);
        break;
    case WM_CTLCOLOREDIT:
        return OnColorEdit(reinterpret_cast<HDC>(wParam));
    default:
        return DefWindowProc(handle, message, wParam, lParam);
    }
    return 0;
}