#include <iostream>
#include <string>
//making sure we dont move outside of memory
#include <cassert>

using namespace std;

static char table[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};

//getting the table into a format of a double array
inline char& table_at(uint8_t x, uint8_t y) {
    assert(x < 3 && y < 3);
    return table[x + y * 3];
};

void displayBoard()
{
    printf(
        "   a     b     c\n"
        "      |     |\n"
        "1  %c  |  %c  |  %c\n"
        " _____|_____|_____\n"
        "      |     |     \n"
        "2  %c  |  %c  |  %c\n"
        " _____|_____|_____\n"
        "      |     |     \n"
        "3  %c  |  %c  |  %c\n"
        "      |     |\n",
        table[0], table[1], table[2], table[3], table[4], table[5], table[6], table[7], table[8]
    );
}

int main()
{
    displayBoard();

    int tttarr[2][3];

    
}