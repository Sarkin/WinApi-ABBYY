#ifndef WINAPI_TASK2_COVERLAPPEDWINDOW_H_
#define WINAPI_TASK2_COVERLAPPEDWINDOW_H_

#include <Windows.h>
#include <string>

class COverlappedWindow {
public:
	COverlappedWindow();
	~COverlappedWindow();

	static bool RegisterClassW();

	bool Create();
	void Show(int cmdShow);

protected:
	virtual void OnDestroy();
	virtual void OnNCCreate(HWND handle);

private:
	static const LPCWSTR class_name_;
	HWND handle_;

	virtual LRESULT __stdcall localWindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) = 0;
	static LRESULT __stdcall windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif