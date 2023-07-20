#include "level0.h"
#include "block.h"
#include <fstream>

using namespace std;

Level0::Level0(Board *board, string filename): Level(board), filename{filename} {}

Block *Level0::generateBlock() {
    ifstream f {filename};
    char type;
    f >> type;
    if (f.eof()) {
        f.clear();
        f.seekg(0, ios::beg);
        f >> type;
    }

    return createBlock(type);
}
