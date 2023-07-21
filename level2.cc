#include "level2.h"
#include <vector>
using namespace std;

Level2::Level2(Board *board): Level(board) {}

Block *Level2::generateBlock() {
    vector<char> blocks {'S', 'Z', 'I', 'J', 'L', 'O', 'T'};
    int index = rand() % blocks.size();
    char type = blocks[index];

    return createBlock(type);
}
