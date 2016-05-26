#include "Draw.h"

void DrawTile(HDC hdc, int x, int y, int tile_size, COLORREF color) {
    RECT rc = { x, y, x + tile_size, y + tile_size };
    COLORREF oldcr = SetBkColor(hdc, color);
    ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rc, L"", 0, 0);
    SetBkColor(hdc, oldcr);
}
