#include <Windows.h>

#include "eclipse_window.h"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int nCmdShow) {
	if (!EclipseWindow::RegisterClassW()) {
		return -1;
	}

	EclipseWindow eclipse_window;
	if (!eclipse_window.Create()) {
		return -1;
	}
	eclipse_window.Show(nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}