#include "csettings_dialog.h"

#include "resource.h"

CSettingsDialog::CSettingsDialog() {
}

CSettingsDialog::~CSettingsDialog() {
}

void CSettingsDialog::Show(HWND handle) {
	DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_SETTINGS_DIALOG), handle,
        reinterpret_cast<DLGPROC>(dialogProc));
}

INT_PTR CALLBACK CSettingsDialog::dialogProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_NCCREATE: {
        CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
        CSettingsDialog* settings_dialog = (CSettingsDialog*)cs->lpCreateParams;
        SetLastError(0);
        if (SetWindowLongPtr(handle, GWLP_USERDATA, (LONG)settings_dialog) == 0 &&
            GetLastError() != 0) {
            return FALSE;
        }
        //settings_dialog->OnNCCreate(handle);
        return TRUE;
    }
    default:
        CSettingsDialog* settings_dialog = (CSettingsDialog*)GetWindowLongPtr(handle, GWLP_USERDATA);
        if (settings_dialog) {
            return settings_dialog->localDialogProc(handle, message, wParam, lParam);
        }
        return DefWindowProc(handle, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK CSettingsDialog::localDialogProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    default:
        return DefWindowProc(handle, message, wParam, lParam);
    }
    return 0;
}