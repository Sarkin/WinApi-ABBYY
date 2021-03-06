#include <Windows.h>

#include "cnotepad_window.h"

const LPCWSTR CNotepadWindow::class_name_ = L"NotepadWindow";

CNotepadWindow::CNotepadWindow() {
	edit_control_ = CEditControlWindow();
	edit_control_changed_ = false;
}

CNotepadWindow::~CNotepadWindow() {
	if (handle_) {
		DestroyWindow(handle_);
	}
}

bool CNotepadWindow::RegisterClassW() {
	WNDCLASSEX wnd_class = { };
	wnd_class.cbSize = sizeof(WNDCLASSEX);
	wnd_class.lpfnWndProc = windowProc;
	wnd_class.hInstance = GetModuleHandle(NULL);
	wnd_class.lpszClassName = class_name_;

	return RegisterClassEx(&wnd_class);
}

bool CNotepadWindow::Create() {
	handle_ = CreateWindowEx(0, class_name_, L"Notepad", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, GetModuleHandle(0), this);
	return (handle_ != NULL);
}

void CNotepadWindow::Show(int cmdShow) {
	ShowWindow(handle_, cmdShow);
	edit_control_.Show(cmdShow);
}

void CNotepadWindow::OnDestroy() {
	PostQuitMessage(0);
}

void CNotepadWindow::OnNCCreate(HWND handle) {
	handle_ = handle;
}

void CNotepadWindow::OnCreate() {
	edit_control_.Create(handle_);
}

void CNotepadWindow::OnSizeChanged() {
	RECT rect;
	GetClientRect(handle_, &rect);
	edit_control_.Resize(rect);
}

bool CNotepadWindow::OnClose() {
	if (!edit_control_changed_) {
		return true;
	}

	int clicked = MessageBox(handle_, L"Save the text?", L"Confirmation", MB_YESNOCANCEL);
	switch (clicked) {
	case IDYES:
		SaveEditControlContent(edit_control_.GetHandle());
		return true;
	case IDNO:
		return true;
	case IDCANCEL:
		return false;
	default:
		return false;
	}
}

void CNotepadWindow::SaveEditControlContent(HWND edit_control_handle) {
	int text_length = SendMessage(edit_control_handle, WM_GETTEXTLENGTH, 0, 0);
	wchar_t* text = new wchar_t[text_length + 5];
	SendMessage(edit_control_handle, WM_GETTEXT, text_length + 1, LPARAM(text));

	OPENFILENAME ofn = { };
	wchar_t szFileName[MAX_PATH] = L"";

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = handle_;
	ofn.lpstrFilter = (LPCWSTR)L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = (LPWSTR)szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = (LPCWSTR)L"txt";

	if (GetSaveFileName(&ofn)) {
		HANDLE file_handle = CreateFile(ofn.lpstrFile, GENERIC_WRITE | GENERIC_READ,
			FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
		WriteFile(file_handle, text, text_length + 1, NULL, NULL);
		CloseHandle(file_handle);
	}
	delete[] text;
}

void CNotepadWindow::OnCommand(WPARAM wParam, LPARAM lParam) {
	if (HIWORD(wParam) == EN_CHANGE) {
		edit_control_changed_ = true;
	}
}

LRESULT _stdcall CNotepadWindow::windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_NCCREATE: {
		CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
		CNotepadWindow* notepad_window = (CNotepadWindow*)cs->lpCreateParams;
		SetLastError(0);
		if (SetWindowLongPtr(handle, GWLP_USERDATA, (LONG)notepad_window) == 0 &&
			GetLastError() != 0) {
			return FALSE;
		}
		notepad_window->OnNCCreate(handle);
		return TRUE;
	}
	default:
		CNotepadWindow* notepad_window = (CNotepadWindow*)GetWindowLongPtr(handle, GWLP_USERDATA);
		if (notepad_window) {
			return notepad_window->localWindowProc(handle, message, wParam, lParam);
		}
		return DefWindowProc(handle, message, wParam, lParam);
	}
	return 0;
}

LRESULT _stdcall CNotepadWindow::localWindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		OnDestroy();
		break;
	case WM_CREATE:
		OnCreate();
		break;
	case WM_SIZE:
		OnSizeChanged();
		break;
	case WM_CLOSE:
		if (OnClose()) {
			return DefWindowProc(handle, message, wParam, lParam);
		}
		break;
	case WM_COMMAND:
		OnCommand(wParam, lParam);
		break;
	default:
		return DefWindowProc(handle, message, wParam, lParam);
	}
	return 0;
}