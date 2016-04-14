#pragma once

#include <Windows.h>

struct Settings {
    BYTE opacity;
    LOGFONT font;
};

class CSettingsDialog {
public:
    CSettingsDialog();
    ~CSettingsDialog();

    void Create(HWND parent_handle);

    HWND GetHandle();

protected:
    bool OnCommand(WPARAM, LPARAM);
    void OnScroll(WPARAM, LPARAM);
    void OnInitialize(HWND);
    bool OnDestroy();

private:
    HWND handle_;
    HWND parent_handle_;
    HWND edit_control_handle_;
    Settings current_settings_;
    Settings new_settings_;
    HFONT hfont_;
    bool preview_;

    void show();
    void hide();
    void getCurrentSettings();
    void applySettings(const Settings&, bool preview = true);

    static INT_PTR CALLBACK dialogProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
    virtual INT_PTR CALLBACK localDialogProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};

