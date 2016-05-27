#include "SettingsDialog.h"

#include <Commctrl.h>

#include "resource.h"
#include "MainWindow.h"

CSettingsDialog::CSettingsDialog() {
    handle_ = 0;
    current_settings_ = {};
    new_settings_ = {};
}

CSettingsDialog::~CSettingsDialog() {
}

void CSettingsDialog::Create(HWND parent_handle) {
    if (handle_) {
        SetFocus(handle_);
        return;
    }
    parent_handle_ = parent_handle;
	handle_ = CreateDialogParam(GetModuleHandle(0), MAKEINTRESOURCE(IDD_SETTINGS_DIALOG), parent_handle,
        reinterpret_cast<DLGPROC>(dialogProc), reinterpret_cast<LPARAM>(this));
    show();
}

void CSettingsDialog::OnInitialize(HWND handle) {
    handle_ = handle;
    SendMessage(GetDlgItem(handle_, IDC_SPEED_SLIDER), TBM_SETRANGE, true, MAKELONG(1, 4));
    getCurrentSettings();
    SendMessage(GetDlgItem(handle_, IDC_SPEED_SLIDER), TBM_SETPOS, true, (LPARAM)current_settings_.speed);
    new_settings_ = current_settings_;
}

bool CSettingsDialog::OnDestroy() {
    bool destroyed = DestroyWindow(handle_);
    handle_ = 0;
    return destroyed;
}

bool CSettingsDialog::OnCommand(WPARAM wParam, LPARAM lParam) {
    switch (LOWORD(wParam)) {
    case IDCANCEL:
        applySettings(current_settings_);
        OnDestroy();
        return true;
    case IDOK:
        applySettings(new_settings_);
        OnDestroy();
        return true;
    case IDC_1PLAYER:
        new_settings_.nplayers = 1;
        return true;
    case IDC_2PLAYERS:
        new_settings_.nplayers = 2;
        return true;
    }
    return false;
}

void CSettingsDialog::OnScroll(WPARAM wParam, LPARAM lParam) {
    HWND slider_handle = reinterpret_cast<HWND>(lParam);
    if (slider_handle == GetDlgItem(handle_, IDC_SPEED_SLIDER)) {
        new_settings_.speed = (BYTE)SendMessage(slider_handle, TBM_GETPOS, 0, 0);
    }
}

void CSettingsDialog::show() {
    ShowWindow(handle_, SW_SHOW);
}

void CSettingsDialog::hide() {
    ShowWindow(handle_, SW_HIDE);
}

void CSettingsDialog::getCurrentSettings() {
    CMainWindow* main_window = reinterpret_cast<CMainWindow*>(GetWindowLongPtr(parent_handle_, GWLP_USERDATA));
    current_settings_ = main_window->GetSettings();
}

void CSettingsDialog::applySettings(const CSettings& settings) {
    CMainWindow* main_window = reinterpret_cast<CMainWindow*>(GetWindowLongPtr(parent_handle_, GWLP_USERDATA));
    main_window->ApplySettings(settings);
}

INT_PTR CALLBACK CSettingsDialog::dialogProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG: {
        CSettingsDialog* settings_dialog = (CSettingsDialog*)lParam;
        SetLastError(0);
        if (SetWindowLongPtr(handle, GWLP_USERDATA, (LONG)settings_dialog) == 0 &&
            GetLastError() != 0) {
            return FALSE;
        }
        settings_dialog->OnInitialize(handle);
        return TRUE;
    }
    default:
        CSettingsDialog* settings_dialog = (CSettingsDialog*)GetWindowLongPtr(handle, GWLP_USERDATA);
        if (settings_dialog) {
            return settings_dialog->localDialogProc(handle, message, wParam, lParam);
        }
        return FALSE;
    }
    return 0;
}

INT_PTR CALLBACK CSettingsDialog::localDialogProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        return OnCommand(wParam, lParam);
    case WM_HSCROLL:
        OnScroll(wParam, lParam);
        return TRUE;
    }
    return FALSE;
}