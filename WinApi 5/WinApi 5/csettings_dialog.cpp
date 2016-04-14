#include "csettings_dialog.h"

#include <Commctrl.h>

#include "resource.h"
#include "cnotepad_window.h"

COLORREF CSettingsDialog::custom_colors_[16] = { 0 };

CSettingsDialog::CSettingsDialog() {
    handle_ = 0;
    preview_ = false;
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
    edit_control_handle_ = reinterpret_cast<CNotepadWindow*>(GetWindowLongPtr(parent_handle,
        GWLP_USERDATA))->GetEditControlHandle();
	handle_ = CreateDialogParam(GetModuleHandle(0), MAKEINTRESOURCE(IDD_SETTINGS_DIALOG), parent_handle,
        reinterpret_cast<DLGPROC>(dialogProc), reinterpret_cast<LPARAM>(this));
    show();
}

HWND CSettingsDialog::GetHandle() {
    return handle_;
}

void CSettingsDialog::OnInitialize(HWND handle) {
    handle_ = handle;
    SendMessage(GetDlgItem(handle_, IDC_SLIDER_WINDOW_TRANSPARENCY), TBM_SETRANGE, true, MAKELONG(0, 255));
    SendMessage(GetDlgItem(handle_, IDC_SLIDER_FONTSIZE), TBM_SETRANGE, true, MAKELONG(8, 72));
    getCurrentSettings();
    SendMessage(GetDlgItem(handle_, IDC_SLIDER_WINDOW_TRANSPARENCY), TBM_SETPOS, true, (LPARAM)current_settings_.opacity);
    SendMessage(GetDlgItem(handle_, IDC_SLIDER_FONTSIZE), TBM_SETPOS, true, (LPARAM)current_settings_.font.lfHeight);
    new_settings_ = current_settings_;
}

bool CSettingsDialog::OnDestroy() {
    bool destroyed = DestroyWindow(handle_);
    handle_ = 0;
    preview_ = false;
    DeleteObject(hfont_);
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
    case IDC_CHECK_PREVIEW:
        preview_ = IsDlgButtonChecked(handle_, IDC_CHECK_PREVIEW) == BST_CHECKED;
        applySettings((preview_)? new_settings_: current_settings_);
        return true;
    case IDC_BUTTON_FONT:
        chooseColor(new_settings_.font_color);
        return true;
    case IDC_BUTTON_BACKGROUND:
        chooseColor(new_settings_.background_color);
        return true;
    }
    applySettings(new_settings_, preview_);
    return false;
}

void CSettingsDialog::OnScroll(WPARAM wParam, LPARAM lParam) {
    HWND slider_handle = reinterpret_cast<HWND>(lParam);
    if (slider_handle == GetDlgItem(handle_, IDC_SLIDER_WINDOW_TRANSPARENCY)) {
        new_settings_.opacity = (BYTE)SendMessage(slider_handle, TBM_GETPOS, 0, 0);
    } else if (slider_handle == GetDlgItem(handle_, IDC_SLIDER_FONTSIZE)) {
        new_settings_.font.lfHeight = SendMessage(slider_handle, TBM_GETPOS, 0, 0);
    }
    applySettings(new_settings_, preview_);
}

void CSettingsDialog::show() {
    ShowWindow(handle_, SW_SHOW);
}

void CSettingsDialog::hide() {
    ShowWindow(handle_, SW_HIDE);
}

void CSettingsDialog::getCurrentSettings() {
    CNotepadWindow* notepad_window = reinterpret_cast<CNotepadWindow*>(GetWindowLongPtr(parent_handle_, GWLP_USERDATA));
    current_settings_.opacity = notepad_window->GetOpacity();
    hfont_ = reinterpret_cast<HFONT>(SendMessage(edit_control_handle_, WM_GETFONT, 0, 0));
    GetObject(hfont_, sizeof(LOGFONT), &current_settings_.font);
    current_settings_.background_color = notepad_window->GetBackgroundColor();
    current_settings_.font_color = notepad_window->GetFontColor();
}

void CSettingsDialog::applySettings(const Settings& settings, bool preview) {
    if (!preview) {
        return;
    }
    CNotepadWindow* notepad_window = reinterpret_cast<CNotepadWindow*>(GetWindowLongPtr(parent_handle_, GWLP_USERDATA));
    notepad_window->SetOpacity(settings.opacity);
    DeleteObject(hfont_);
    hfont_ = CreateFontIndirect(&settings.font);
    SendMessage(edit_control_handle_, WM_SETFONT, reinterpret_cast<WPARAM>(hfont_), TRUE);
    notepad_window->SetFontColor(settings.font_color);
    notepad_window->SetBackgroundColor(settings.background_color);
}

void CSettingsDialog::chooseColor(DWORD& color) {
    CHOOSECOLOR choose_color = {};
    choose_color.hwndOwner = handle_;
    choose_color.lStructSize = sizeof(CHOOSECOLOR);
    choose_color.rgbResult = color;
    choose_color.Flags = CC_ANYCOLOR | CC_FULLOPEN | CC_RGBINIT;
    choose_color.lpCustColors = custom_colors_;
    if (ChooseColor(&choose_color)) {
        color = choose_color.rgbResult;
    }
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