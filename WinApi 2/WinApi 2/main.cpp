#include <Windows.h>

#include "coverlapped_window.h"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int nCmdShow) {
	if (!COverlappedWindow::RegisterClassW()) {
		return -1;
	}

	COverlappedWindow overlapped_window;
	if (!overlapped_window.Create()) {
		return -1;
	}
	overlapped_window.Show(nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}