#include <Windows.h>

#include "cnotepad_window.h"
#include "resource.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int nCmdShow) {
    if (!CNotepadWindow::RegisterClassW()) {
        return -1;
    }

    CNotepadWindow notepad_window;
    if (!notepad_window.Create()) {
        return -1;
    }
    notepad_window.Show(nCmdShow);
    
    HACCEL notepad_window_accelerator = LoadAccelerators(hInstance,
        MAKEINTRESOURCE(IDR_NOTEPAD_WINDOW_ACCELERATOR_TABLE));
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        if (!TranslateAcceleratorW(notepad_window.GetHandle(), notepad_window_accelerator, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    DestroyAcceleratorTable(notepad_window_accelerator);
    return msg.wParam;
}