#ifndef WINAPI_TASK2_COVERLAPPEDWINDOW_H_
#define WINAPI_TASK2_COVERLAPPEDWINDOW_H_

#include <Windows.h>
#include <string>

class COverlappedWindow {
public:
	COverlappedWindow();
	COverlappedWindow(int ellipse_radius);
	~COverlappedWindow();

	static bool RegisterClassW();

	bool Create();
	void Show(int cmdShow);

protected:
	void OnDestroy();
	void OnNCCreate(HWND handle);
	void OnCreate();
    void OnPaint();
    void OnTimer();
private:
	static const LPCWSTR class_name_;
	HWND handle_;

	UINT_PTR timerId_;
    double time_;
    static const double deltaTime_;
    int ellipse_radius_;

	void initialize();
	void drawEllipse(HDC targetDC, int x, int y);

	virtual LRESULT __stdcall localWindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT __stdcall windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif