#pragma once

#include <functional>
#include <Windows.h>

struct CSettings {
    int speed;
    int nplayers;

    CSettings() {
        speed = 1;
        nplayers = 1;
    }
};

class CSettingsDialog {
public:
    CSettingsDialog();
    ~CSettingsDialog();

    void Create(HWND parent_handle);

protected:
    bool OnCommand(WPARAM, LPARAM);
    void OnScroll(WPARAM, LPARAM);
    void OnInitialize(HWND);
    bool OnDestroy();

private:
    HWND handle_;
    HWND parent_handle_;
    HWND edit_control_handle_;
    CSettings current_settings_;
    CSettings new_settings_;

    void show();
    void hide();
    void getCurrentSettings();
    void applySettings(const CSettings&);

    static INT_PTR CALLBACK dialogProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
    virtual INT_PTR CALLBACK localDialogProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};
