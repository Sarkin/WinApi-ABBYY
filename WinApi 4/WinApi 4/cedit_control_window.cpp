#include "cedit_control_window.h"

#include <Windows.h>
#include <string>

#define ID_EDITCHILD 100

const LPCWSTR CEditControlWindow::class_name_ = L"EDIT";

CEditControlWindow::CEditControlWindow() {
}

CEditControlWindow::~CEditControlWindow() {
}

bool CEditControlWindow::Create(HWND parent_handle) {
	handle_ = CreateWindowEx(0, class_name_, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL |
		ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 0, 0, 0, 0,  parent_handle, 
		(HMENU)ID_EDITCHILD, GetModuleHandle(0), NULL);
	return (handle_ != NULL);
}

void CEditControlWindow::Show(int cmdShow) {
	ShowWindow(handle_, cmdShow);
	SetFocus(handle_);
}

void CEditControlWindow::Resize(const RECT& rect) {
	SetWindowPos(handle_, HWND_TOP, rect.left, rect.top, rect.right - rect.left,
		rect.bottom - rect.top, 0);
}

HWND CEditControlWindow::GetHandle() {
	return handle_;
}