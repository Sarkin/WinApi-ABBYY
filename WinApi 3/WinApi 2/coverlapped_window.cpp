#include "coverlapped_window.h"

#include <Windows.h>

const LPCWSTR COverlappedWindow::class_name_ = L"OverlappedWindow";
const double COverlappedWindow::deltaTime_ = 0.05;

void COverlappedWindow::initialize() {
	timerId_ = 0;
	time_ = 0;
	handle_ = 0;
	ellipse_radius_ = 0;
}

COverlappedWindow::COverlappedWindow() {
	initialize();
}

COverlappedWindow::COverlappedWindow(int ellipse_radius) {
	initialize();
	ellipse_radius_ = ellipse_radius;
}

COverlappedWindow::~COverlappedWindow() {
	if (handle_) {
		DestroyWindow(handle_);
	}
}

bool COverlappedWindow::RegisterClassW() {
	WNDCLASSEX wnd_class = { };
	wnd_class.cbSize = sizeof(WNDCLASSEX);
	wnd_class.style = CS_HREDRAW | CS_VREDRAW;
	wnd_class.lpfnWndProc = windowProc;
	wnd_class.hInstance = GetModuleHandle(NULL);
	wnd_class.lpszClassName = class_name_;
	wnd_class.hCursor = ::LoadCursor(GetModuleHandle(0), IDC_ARROW);
	return RegisterClassEx(&wnd_class);
}

bool COverlappedWindow::Create() {
	handle_ = CreateWindowEx(0, class_name_,
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
	if (handle_ == NULL) {
		return false;
	}
	return true;
}

void COverlappedWindow::Show(int cmdShow) {
	ShowWindow(handle_, cmdShow);
	UpdateWindow(handle_);
}

void COverlappedWindow::OnNCCreate(HWND handle) {
	handle_ = handle;
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
		overlapped_window->OnNCCreate(handle);
		return TRUE;
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

void COverlappedWindow::OnCreate() {
    timerId_ = SetTimer(handle_, 0, (int)(deltaTime_ * 1000), 0);
}

void COverlappedWindow::OnDestroy() {
	KillTimer(handle_, timerId_);
}

void COverlappedWindow::OnPaint() {
    RECT client_rect;
	GetClientRect(handle_, &client_rect);

    PAINTSTRUCT paint_struct;
    HDC windowDC = BeginPaint(handle_, &paint_struct);

    HDC displayBufferDC = CreateCompatibleDC(windowDC);
    HBITMAP displayBuffer = CreateCompatibleBitmap(windowDC, client_rect.right - client_rect.left, 
        client_rect.bottom - client_rect.top);
    HGDIOBJ oldDisplayBuffer = SelectObject(displayBufferDC, displayBuffer);

    int R = min((client_rect.right - client_rect.left) / 2, (client_rect.bottom - client_rect.top) / 2) - ellipse_radius_;
    int x = (client_rect.left + client_rect.right) / 2 + R * cos(time_);
    int y = (client_rect.top + client_rect.bottom) / 2 + R * sin(time_);

    FillRect(displayBufferDC, &client_rect, (HBRUSH)GetStockObject(GRAY_BRUSH));
    drawEllipse(displayBufferDC, x, y);
    BitBlt(windowDC, client_rect.left, client_rect.top, client_rect.right - client_rect.left, 
        client_rect.bottom - client_rect.top, displayBufferDC, 0, 0, SRCCOPY);

    SelectObject(displayBufferDC, oldDisplayBuffer);
    DeleteObject(displayBuffer);
    DeleteDC(displayBufferDC);
    EndPaint(handle_, &paint_struct);
}

void COverlappedWindow::drawEllipse(HDC targetDC, int x, int y) {
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    HBRUSH innBrush = CreateSolidBrush(RGB(0, 0, 0));
    HGDIOBJ oldPen = SelectObject(targetDC, pen);
    HGDIOBJ oldBrush = SelectObject(targetDC, innBrush);

    Ellipse(targetDC, x - ellipse_radius_, y - ellipse_radius_,
		x + ellipse_radius_, y + ellipse_radius_);

    SelectObject(targetDC, oldPen);
    SelectObject(targetDC, oldBrush);
    DeleteObject(innBrush);
    DeleteObject(pen);
}

void COverlappedWindow::OnTimer() {
    RECT rect;
    GetClientRect(handle_, &rect);
    time_ += deltaTime_;
    InvalidateRect(handle_, &rect, FALSE);
}

LRESULT _stdcall COverlappedWindow::localWindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		OnDestroy();
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		OnPaint();
		break;
	case WM_TIMER:
		OnTimer();
		break;
	case WM_CREATE:
		OnCreate();
		break;
	default:
		return DefWindowProc(handle, message, wParam, lParam);
	}
	return 0;
}