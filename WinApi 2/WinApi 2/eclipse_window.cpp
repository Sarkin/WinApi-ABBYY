#include "eclipse_window.h"

#include <Windows.h>

const LPCWSTR EclipseWindow::class_name_ = L"EclipseWindow";

EclipseWindow::EclipseWindow() {
}

EclipseWindow::~EclipseWindow() {
	if (handle_) {
		DestroyWindow(handle_);
	}
}

void EclipseWindow::OnDestroy() {
//	KillTimer(handle_, timerId);
}

LRESULT _stdcall EclipseWindow::localWindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
	return 0;
}