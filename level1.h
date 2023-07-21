#ifndef LEVEL1_H
#define LEVEL1_H

#include "level.h"
#include "block.h"

class Level1: public Level {

public:
    Level1(Board *board);
    Block *generateBlock() override;
};

#endif
