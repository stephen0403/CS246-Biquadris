#include "level1.h"
#include <vector>
using namespace std;

Level1::Level1(Board *board): Level(board) {}

Block *Level1::generateBlock() {
    vector<char> blocks {'S', 'Z', 'S', 'Z', 'I', 'J', 'L', 'O', 'T'};
    int index = rand() % blocks.size();
    char type = blocks[index];

    return createBlock(type);
}
