#include "level0.h"
#include "block.h"
#include <fstream>

using namespace std;

Level0::Level0(string filename): filename{filename} {}

Block *Level0::generateBlock() {
    ifstream f {filename};
    char type;
    f >> type;
    if (f.eof()) {
        f.clear();
        f.seekg(0, ios::beg);
        f >> type;
    }

    switch(type) {
        case 'I':
            return new Iblock{board};
        case 'J':
            return new Jblock{board};
        case 'L':
            return new Lblock{board};
        case 'O':
            return new Oblock{board};   
        case 'S':
            return new Sblock{board};
        case 'Z':
            return new Zblock{board};
        case 'T':
            return new Tblock{board};
        default:
            return nullptr;
    }
}
