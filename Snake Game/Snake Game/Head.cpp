#include "Head.h"

CHead::CHead(int length) : length_(length) {
}

int CHead::GetLength() const {
    return length_;
}

void CHead::SetLength(int length) {
    length_ = length;
}
