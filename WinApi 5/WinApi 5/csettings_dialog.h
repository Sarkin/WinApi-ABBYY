#include <Windows.h>

#pragma once
class CSettingsDialog {
public:
    CSettingsDialog();
    ~CSettingsDialog();

    void Show(HWND handle);
    virtual INT_PTR CALLBACK localDialogProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
    static INT_PTR CALLBACK dialogProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};

