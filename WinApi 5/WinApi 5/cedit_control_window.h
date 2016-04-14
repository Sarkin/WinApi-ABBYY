#include <Windows.h>
#include <string>

class CEditControlWindow {
public:
    CEditControlWindow();
    ~CEditControlWindow();

    bool Create(HWND parent_handle);
    void Show();
    void Resize(const RECT& rect);
    HWND GetHandle();
    void SetEditControlText();

private:
    static const LPCWSTR class_name_;
    HWND handle_;

    void loadFileInResource(int name, int type, DWORD& size, const wchar_t*& data);
};