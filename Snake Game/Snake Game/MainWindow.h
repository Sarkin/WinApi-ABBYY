#pragma once

#include <Windows.h>

#include "SnakeGame.h"
#include "SettingsDialog.h"

class CMainWindow {
public:
    CMainWindow();
    ~CMainWindow();

    static bool RegisterClassW();
    bool Create();
    HWND CreateFullscreenWindow();
    void Show(int cmdShow);
    void Update();
    void Draw();
    void ApplySettings(const CSettings&);
    CSettings GetSettings();


    int GetSpeed();
    HWND GetHandle();

protected:
    void OnDestroy();
    void OnCreate();
    void OnClose();
    void OnNCCreate(HWND handle);
    void OnCommand(WPARAM, LPARAM);

private:
    static const LPCWSTR class_name_;
    static const HICON icon32_;
    static const HICON icon64_;

    bool confirmClose();
    void showSettings();

    HWND handle_;
    CSnakeGame* g_snake_;
    CSettingsDialog settings_dialog_;
    int speed_;
    int nplayers_;

    virtual LRESULT __stdcall localWindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
    static LRESULT __stdcall windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};
