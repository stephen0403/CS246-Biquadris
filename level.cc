#include "level.h"
#include "block.h"

Level::Level(Board *board): board{board} {}

Block *Level::createBlock(char type) {
    switch (type) {
        case 'I':
            return new IBlock{board};
        case 'J':
            return new JBlock{board};
        case 'L':
            return new LBlock{board};
        case 'O':
            return new OBlock{board};
        case 'S':
            return new SBlock{board};
        case 'Z':
            return new ZBlock{board};
        case 'T':
            return new TBlock{board};
        default:
            return nullptr;
    }
}
