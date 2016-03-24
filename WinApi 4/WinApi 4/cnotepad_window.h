#include <Windows.h>
#include <string>

#include "cedit_control_window.h"

class CNotepadWindow {
public:
	CNotepadWindow();
	~CNotepadWindow();

	static bool RegisterClassW();

	bool Create();
	void Show(int cmdShow);

protected:
	void OnDestroy();
	void OnNCCreate(HWND handle);
	void OnCreate();
	void OnSizeChanged();
	bool OnClose();
	void OnCommand(WPARAM wParam, LPARAM lParam);

private:
	static const LPCWSTR class_name_;
	HWND handle_;
	bool edit_control_changed_;

	CEditControlWindow edit_control_;

	virtual LRESULT __stdcall localWindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT __stdcall windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	void SaveEditControlContent(HWND edit_control_handle);
};
