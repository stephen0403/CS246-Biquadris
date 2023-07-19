#include "blind.h"

static const int COLUMN_LEFT = 3;
static const int COLUMN_RIGHT = 9;
static const int ROW_TOP = 3;
static const int ROW_BOTTOM = 12;

Blind::Blind(absBoard* board): Decorator {board} {}

char Blind::tileAt(int row, int col) {
    if (!blockDropped && row <= ROW_BOTTOM && row >= ROW_TOP
        && col <= COLUMN_RIGHT && col >= COLUMN_LEFT) return '?';
}

void Blind::setTrue() {
    blockDropped = true;
}
