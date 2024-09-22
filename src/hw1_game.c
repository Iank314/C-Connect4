#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hw1.h"
void play_game(int rows, int cols);
int main(int argc, char **argv) 
{
    assert(argc == 4);
    initialize_board(argv[3], (int)strtoul(argv[1], NULL, 10), (int)strtoul(argv[2], NULL, 10));
    //Write your code here
    play_game(atoi(argv[1]), atoi(argv[2]));
    return 0;
}