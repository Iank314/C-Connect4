#include <string.h>
#include "hw1.h"

extern char board[MAX_ROWS][MAX_COLS];

int main() {
    int act_num_x = -1, act_num_o = -1;
    const char *init_board = "-o----o--oxx---o--ox--------o--x--xx--xxxo--------------x-x-----o---x------xx-ox-----o-------o-----oo-oo----x---o----x-x----o------x---------------xoo-x---x--ox--o-x---o------o----ooo-x--x-----------------ox----x---x--xxoo--------o--o----oo-o--------o---x---ooox--x------x-------xo----o--------x---o-ooo--o---x-x-x---o-o--ox-----xx------ooo-o----o-----o-ox--oox-x----xxx--oo--xo--x-ooo----o-o-x-----x";
    char board_array[MAX_ROWS][MAX_COLS] = {
    {'l','T','q','<','=','r','d','F','i','!','T','v',',','u','a','=','k','E','U','[',},
    {'Q','V','b','$','c','O','f',']','U','_','!','?','1','o','[','O','`','@','u','G',},
    {'>','K',';','J','>','}','d','*','C','7','c','q','m','F','u','O','u','Y','*','I',},
    {':','(','h','H','w','B','w','X','_','k','|','~','4','9','F','R','7',')','Y','Z',},
    {'@','=','I',',','`','?','X','W','u','_','}','-','g','c','V',']','&','N','6','f',},
    {':','0','b','N','I',')','}','`','/','X','8','M','r','a','V','T','}','/',')','t',},
    {'n','$','"','S','g','X','0','n','%','C','R','?','T','5','k','}',';','i',']','K',},
    {'?','q','x','3','Q','O','d','L','[','m','>','G','q','>','z','V','s','(','E','x',},
    {'L','t','9','}','(','"','x','C','k','U','k',',','E','a','<','v','.','!','C','i',},
    {'k','b','.','Z','!','&','1','t','.','T','k','W','I','"','U','Q','$','O','q','o',},
    {'"',']','x','G','<','2',';','J','3',']','4','{','?','B','S','=','H','e','/','S',},
    {'7','z',',',']','y','^','/','}','+','}','k','.','X','d','R','t','t','n','?','%',},
    {'H','P','"','d','o','U','"','5','8','.','f','O','(','r','.','!','N',':','|','Z',},
    {'6','h','h','n','J','8','a','?','$','}','E','L','L','D','1','<','v','0','O','0',},
    {'?','6',']','C','&','g','A','T',' ','>','/','3','(','t','~','O','.','`','n','2',},
    {']','1',']',')','U','m','B','M','~','q','Z',';','(','4','^','+','y',' ','`','y',},
    {'<','o','-','C','e',',','r','p','j','_',' ','G','p',']','P','D','K','r','n','G',},
    {'b','I','b','g','Z','A','s','T','>','T','N','Z','A','X','{','$','b','k','t','M',},
    {'H','r','q',':','O','B','[','w','2','J','?','t','s','"','Z','N','@','N','$',']',},
    {'#','O','4','A','&','-','F','h','y','8','6','B','+','(','Y','[','G','5','P','V',},
    };
    memcpy(board, board_array, sizeof(board_array));
    (void)solve(init_board, 20, 20, &act_num_x, &act_num_o);
}