#include <Windows.h>

#pragma once
class CSettingsDialog {
public:
    CSettingsDialog();
    ~CSettingsDialog();

    void Show(HWND handle);

protected:
    void OnCommand(WPARAM, LPARAM);

private:
    INT_PTR nResult_;

    static INT_PTR CALLBACK dialogProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
    virtual INT_PTR CALLBACK localDialogProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};

