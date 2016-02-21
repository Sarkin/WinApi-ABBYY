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
	void OnDestroy();

private:
	static const LPCWSTR class_name_;
	HWND handle;

	virtual LRESULT __stdcall localWindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) = 0;
	static LRESULT __stdcall windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};
