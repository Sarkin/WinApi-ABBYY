#include <Windows.h>

#include "MainWindow.h"

int Run(CMainWindow&);

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int nCmdShow) {
    if (!CMainWindow::RegisterClassW()) {
        return -1;
    }

    CMainWindow main_window;
    if (!main_window.Create()) {
        return -1;
    }

    main_window.Show(nCmdShow);

    return Run(main_window);
}

int Run(CMainWindow& main_window) {
    __int64 timer_frequency;
    if (!QueryPerformanceFrequency((LARGE_INTEGER *)&timer_frequency)) {
        MessageBox(0, L"Performance timer does not exist!", L"Error!", MB_OK);
        return 0;
    }
    __int64 clocks_per_frame = timer_frequency / 15;

    __int64 curr_count;
    __int64 old_count;
    QueryPerformanceCounter((LARGE_INTEGER *)&old_count);

    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            QueryPerformanceCounter((LARGE_INTEGER *)&curr_count);
            if (curr_count > old_count) {
                main_window.Update();
                main_window.Draw();
                old_count += clocks_per_frame;
            }
        }

    }
    return (int)msg.wParam;
}
