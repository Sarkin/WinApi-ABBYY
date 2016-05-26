#pragma once

#include <Windows.h>

#include "SnakeGame.h"

class CMainWindow {
public:
    CMainWindow();
    ~CMainWindow();

    static bool RegisterClassW();
    bool Create();
    void Show(int cmdShow);
    void Update();
    void Draw();
    HWND GetHandle();

protected:
    void OnDestroy();
    void OnCreate();
    void OnNCCreate(HWND handle);

private:
    static const LPCWSTR class_name_;
    HWND handle_;
    CSnakeGame g_snake_;

    virtual LRESULT __stdcall localWindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
    static LRESULT __stdcall windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};
