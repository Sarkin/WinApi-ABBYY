#include <Windows.h>
#include <string>

class CEditControlWindow {
public:
	CEditControlWindow();
	~CEditControlWindow();

	bool Create(HWND parent_handle);
	void Show(int cmdShow);
	void Resize(const RECT& rect);
	HWND GetHandle();
	void SetEditControlText();

private:
	static const LPCWSTR class_name_;
	HWND handle_;

	void LoadFileInResource(int name, int type, DWORD& size, const wchar_t*& data);
};