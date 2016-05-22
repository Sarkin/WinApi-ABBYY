#pragma once

#include <Windows.h>

struct Settings {
    BYTE opacity;
    LOGFONT font;
    DWORD font_color;
    DWORD background_color;

    Settings() {
        opacity = 0;
        font_color = 0;
        background_color = 0;
    }
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
    static COLORREF custom_colors_[16];

    void show();
    void hide();
    void getCurrentSettings();
    void applySettings(const Settings&, bool preview = true);
    void chooseColor(DWORD&);

    static INT_PTR CALLBACK dialogProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
    virtual INT_PTR CALLBACK localDialogProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};

