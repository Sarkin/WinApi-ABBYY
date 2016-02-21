#include <Windows.h>

#include "coverlapped_window.h"

const LPCWSTR COverlappedWindow::class_name_ = L"OverlappedWindow";

COverlappedWindow::COverlappedWindow() {
}

COverlappedWindow::~COverlappedWindow() {
	if (handle) {
		DestroyWindow(handle);
	}
}

bool COverlappedWindow::RegisterClassW() {
	WNDCLASSEX wnd_class = { };
	wnd_class.cbSize = sizeof(WNDCLASSEX);
	wnd_class.style = CS_HREDRAW | CS_VREDRAW;
	wnd_class.lpfnWndProc = windowProc;
	wnd_class.hInstance = GetModuleHandle(NULL);
	wnd_class.lpszClassName = class_name_;

	return RegisterClassEx(&wnd_class);
}

bool COverlappedWindow::Create() {
	handle = CreateWindowEx(
		0,
		class_name_,
		L"Sample",
		WS_OVERLAPPED,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		this
);
	if (handle == NULL) {
		return false;
	}
	return true;
}

void COverlappedWindow::Show(int cmdShow) {
	ShowWindow(handle, cmdShow);
	UpdateWindow(handle);
}

void COverlappedWindow::OnDestroy() {
}

LRESULT _stdcall COverlappedWindow::windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_NCCREATE: {
		CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
		COverlappedWindow* overlapped_window = (COverlappedWindow*)cs->lpCreateParams;
		SetLastError(0);
		if (SetWindowLongPtr(handle, GWLP_USERDATA, (LONG)overlapped_window) == 0 &&
			GetLastError() != 0) {
				return FALSE;
		}
		return TRUE;
	}
	case WM_DESTROY: {
		COverlappedWindow* overlapped_window = (COverlappedWindow*)GetWindowLongPtr(handle, GWLP_USERDATA);
		if (overlapped_window) {
			overlapped_window->OnDestroy();
		}
		PostQuitMessage(0);
		break;
	}
	default:
		COverlappedWindow* overlapped_window = (COverlappedWindow*)GetWindowLongPtr(handle, GWLP_USERDATA);
		if (overlapped_window) {
			return overlapped_window->localWindowProc(handle, message, wParam, lParam);
		}
		return DefWindowProc(handle, message, wParam, lParam);
	}
	return 0;
}