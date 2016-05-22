#include <Windows.h>

#include "cmain_window.h"

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

    __int64 curr_count;
    __int64 old_count;
    QueryPerformanceCounter((LARGE_INTEGER *)&curr_count);

    double elapsed_time = 0.0;

    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            old_count = curr_count;
            QueryPerformanceCounter((LARGE_INTEGER *)&curr_count);
            elapsed_time += (double)((curr_count - old_count) * timer_frequency);

            main_window.Update(elapsed_time);
        }
    }
    return (int)msg.wParam;
}
