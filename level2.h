#ifndef LEVEL2_H
#define LEVEL2_H

#include "level.h"
#include "block.h"

class Level2: public Level {

public:
    Level2(Board *board);
    Block *generateBlock() override;
};

#endif
