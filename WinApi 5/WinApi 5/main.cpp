#include <Windows.h>

#include "cnotepad_window.h"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int nCmdShow) {
	if (!CNotepadWindow::RegisterClassW()) {
		return -1;
	}

	CNotepadWindow notepad_window;
	if (!notepad_window.Create()) {
		return -1;
	}
	notepad_window.Show(nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}