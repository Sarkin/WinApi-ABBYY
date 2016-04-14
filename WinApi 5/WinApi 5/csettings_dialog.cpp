#include "csettings_dialog.h"

#include "resource.h"

CSettingsDialog::CSettingsDialog() {
}

CSettingsDialog::~CSettingsDialog() {
}

void CSettingsDialog::Show(HWND handle) {
	nResult_ = DialogBoxParam(GetModuleHandle(0), MAKEINTRESOURCE(IDD_SETTINGS_DIALOG), handle,
        reinterpret_cast<DLGPROC>(dialogProc), (LPARAM)this);
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

void CSettingsDialog::OnCommand(WPARAM wParam, LPARAM lParam) {

}

INT_PTR CALLBACK CSettingsDialog::localDialogProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        OnCommand(wParam, lParam);
    default:
        return FALSE;
    }
    return 0;
}