#pragma once

const int DX[5] = { 1, 0, -1, 0, 0 };
const int DY[5] = { 0, 1, 0, -1, 0 };

enum Direction {
    Right, Up, Left, Down, Hold
};

class CMotion {
public:
    CMotion(int x, int y, Direction d);
    CMotion();
    ~CMotion();

    void SetDirection(Direction d);
    void Update();
private:
    int x_;
    int y_;
    Direction d_;
};