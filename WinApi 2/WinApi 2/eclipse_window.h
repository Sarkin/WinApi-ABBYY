#ifndef WINAPI_TASK2_ECLIPSE_WINDOW_H_
#define WINAPI_TASK2_ECLIPSE_WINDOW_H_

#include <Windows.h>
#include <string>

#include "coverlapped_window.h"

class EclipseWindow : public COverlappedWindow {
public:
	EclipseWindow();
	~EclipseWindow();

protected:
	virtual void OnDestroy();
    void OnCreate();
    void OnPaint();
    void OnTimer();

private:
	static const LPCWSTR class_name_;
	HWND handle_;
	COverlappedWindow* wrapped_window_;

	UINT_PTR timerId;
    double time;
    static const double deltaTime;
    static const int r = 30;

	void drawEllipse(HDC targetDC, int x, int y);

	LRESULT __stdcall localWindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif