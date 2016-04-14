#include <Windows.h>
#include <string>

#include "cedit_control_window.h"
#include "csettings_dialog.h"

class CNotepadWindow {
public:
    CNotepadWindow();
    ~CNotepadWindow();

    static bool RegisterClassW();
    bool Create();
    void Show(int cmdShow);
    HWND GetHandle();
    HWND GetEditControlHandle();
    HWND GetSettingsDialogHandle();
    BYTE GetOpacity();
    void SetOpacity(BYTE);

protected:
    void OnDestroy();
    void OnNCCreate(HWND handle);
    void OnCreate();
    void OnSizeChanged();
    void OnClose();
    void OnCommand(WPARAM wParam, LPARAM lParam);
    bool ConfirmClose();

private:
    static const LPCWSTR class_name_;
    HWND handle_;
    bool edit_control_changed_;
    BYTE opacity_;

    static const HICON icon32_;
    static const HICON icon64_;

    CEditControlWindow edit_control_;
    CSettingsDialog settings_dialog_;

    virtual LRESULT __stdcall localWindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
    static LRESULT __stdcall windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

    bool saveEditControlContent(HWND edit_control_handle);
    void setWindowTitle();
    void showSettings();
};
