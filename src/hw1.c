#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "hw1.h"

#define NUM_ROWS 20
#define NUM_COLS 20

#define FOUND_SOLUTION 1
#define HEURISTICS_FAILED 0
#define INITIAL_BOARD_FOUR_IN_A_ROW -1
#define INITIAL_BOARD_INVALID_CHARACTERS -2
#define INITIAL_BOARD_NO_SOLUTION -3



char board[NUM_ROWS][NUM_COLS] = {0};

void initialize_board(const char *initial_state, int num_rows, int num_cols) 
{
    int index = 0;
    for (int i = 0; i < num_rows; i++) 
    {
        for (int j = 0; j < num_cols; j++) 
        {
            board[i][j] = initial_state[index++];
        }
    }
}


void prompt_input(char *piece, int *row, int *col, int num_rows, int num_cols) 
{
    while (true) 
    {
        printf("Choose a piece (x or o) or q to quit: ");
        scanf(" %c", piece);
        if (*piece == 'x' || *piece == 'o' || *piece == 'q') break;
        printf("Invalid choice. ");
    }

    if (*piece == 'q') return;

    while (true) 
    {
        printf("Choose a row (0-%d): ", num_rows - 1);
        scanf("%d", row);
        if (*row >= 0 && *row < num_rows) break;
        printf("Invalid choice. ");
    }

    while (true) 
    {
        printf("Choose a column (0-%d): ", num_cols - 1);
        scanf("%d", col);
        if (*col >= 0 && *col < num_cols) break;
        printf("Invalid choice. ");
    }
}
int check_win_direction(int num_rows, int num_cols, int row_pos, int col_pos)
{
    char token = board[row_pos][col_pos];
    if (token == '-')
    {
        return 0;
    }

    int count = 1;
    int temp_row = row_pos + 1;
    while (temp_row < num_rows && board[temp_row][col_pos] == token)
    {
        count++;
        temp_row++;
    }
    temp_row = row_pos - 1;
    while (temp_row >= 0 && board[temp_row][col_pos] == token)
    {
        count++;
        temp_row--;
    }
    if (count >= 4)
    {
        return 1;
    }
    count = 1;
    temp_row = row_pos + 1;
    int temp_col = col_pos + 1;
    while (temp_row < num_rows && temp_col < num_cols && board[temp_row][temp_col] == token)
    {
        count++;
        temp_row++;
        temp_col++;
    }
    temp_row = row_pos - 1;
    temp_col = col_pos - 1;
    while (temp_row >= 0 && temp_col >= 0 && board[temp_row][temp_col] == token)
    {
        count++;
        temp_row--;
        temp_col--;
    }
    if (count >= 4)
    {
        return 1;
    }
    count = 1;
    temp_row = row_pos - 1;
    temp_col = col_pos + 1;
    while (temp_row >= 0 && temp_col < num_cols && board[temp_row][temp_col] == token)
    {
        count++;
        temp_row--;
        temp_col++;
    }
    temp_row = row_pos + 1;
    temp_col = col_pos - 1;
    while (temp_row < num_rows && temp_col >= 0 && board[temp_row][temp_col] == token)
    {
        count++;
        temp_row++;
        temp_col--;
    }
    if (count >= 4)
    {
        return 1;
    }

    count = 1;
    temp_col = col_pos + 1;
    while (temp_col < num_cols && board[row_pos][temp_col] == token)
    {
        count++;
        temp_col++;
    }
    temp_col = col_pos - 1;
    while (temp_col >= 0 && board[row_pos][temp_col] == token)
    {
        count++;
        temp_col--;
    }
    if (count >= 4)
    {
        return 1;
    }

    return 0;
}
void play_game(int num_rows, int num_cols)
 {
    char piece;
    int row, col;

    while (true) 
    {
        for (int i = 0; i < num_rows; i++) 
        {
            for (int j = 0; j < num_cols; j++) 
            {
                printf("%c ", board[i][j]);
            }
            printf("\n");
        }

        prompt_input(&piece, &row, &col, num_rows, num_cols);

        if (piece == 'q') break;

        if (board[row][col] != '-') 
        {
            printf("Invalid choice. That space is already occupied.\n");
            continue;
        }

        board[row][col] = piece;

         if (check_win_direction(num_rows, num_cols, row, col))
        {
            printf("Invalid choice. You have created 4-in-a-row.\n");
            board[row][col] = '-';
        }

        bool full = true;
        for (int i = 0; i < num_rows; i++) 
        {
            for (int j = 0; j < num_cols; j++) 
            {
                if (board[i][j] == '-') {
                    full = false;
                    break;
                }
            }
        }
        if (full) 
        {
            printf("Congratulations, you have filled the board with no 4-in-a-rows!\n");
            for (int i = 0; i < num_rows; i++) 
            {
                for (int j = 0; j < num_cols; j++) 
                {
                    printf("%c ", board[i][j]);
                }
                printf("\n");
            }
            break;
        }
    }
}
int solve(const char *initial_state, int num_rows, int num_cols, int *num_x, int *num_o)
{
    initialize_board(initial_state, num_rows, num_cols);

    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            if (board[i][j] != '-' && board[i][j] != 'x' && board[i][j] != 'o')
            {
                return INITIAL_BOARD_INVALID_CHARACTERS;
            }
        }
    }

    *num_x = 0;
    *num_o = 0;

    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            if (board[i][j] == 'x')
            {
                (*num_x)++;
                if (check_win_direction(num_rows, num_cols, i, j))
                {
                    return INITIAL_BOARD_FOUR_IN_A_ROW;
                }
            }
            else if (board[i][j] == 'o')
            {
                (*num_o)++;
                if (check_win_direction(num_rows, num_cols, i, j))
                {
                    return INITIAL_BOARD_FOUR_IN_A_ROW;
                }
            }
        }
    }

    bool made_a_move = true;
    while (made_a_move)
    {
        made_a_move = false;
        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_cols; j++)
            {
                if (board[i][j] == '-')
                {
                    board[i][j] = 'x';
                    (*num_x)++;
                    if (check_win_direction(num_rows, num_cols, i, j))
                    {
                        board[i][j] = 'o';
                        (*num_x)--; 
                        (*num_o)++;
                        made_a_move = true;
                        if (check_win_direction(num_rows, num_cols, i, j))
                        {
                            return INITIAL_BOARD_NO_SOLUTION;
                        }
                    }
                    else
                    {
                        board[i][j] = 'o';
                        (*num_x)--; 
                        (*num_o)++;
                        if (check_win_direction(num_rows, num_cols, i, j))
                        {
                            board[i][j] = 'x';
                            (*num_o)--; 
                            (*num_x)++;
                            made_a_move = true;
                            if (check_win_direction(num_rows, num_cols, i, j))
                            {
                                return INITIAL_BOARD_NO_SOLUTION;
                            }
                        }
                        else
                        {
                           
                            board[i][j] = '-';
                            (*num_o)--; 
                        }
                    }
                }
            }
        }
    }

    bool board_full = true;
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            if (board[i][j] == '-')
            {
                board_full = false;
                break;
            }
        }
        if (!board_full) break;
    }

    if (board_full)
    {
        return FOUND_SOLUTION; 
    }

    return HEURISTICS_FAILED; 
}
char* generate_medium(const char *final_state, int num_rows, int num_cols)
{
    static char medium_board[NUM_ROWS * NUM_COLS + 1];  
    char board_copy[NUM_ROWS][NUM_COLS];  
    char test_board[NUM_ROWS * NUM_COLS + 1];  

    int index = 0;
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            board_copy[i][j] = final_state[index++];
        }
    }

    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            char original_token = board_copy[i][j];
            if (original_token == 'x' || original_token == 'o')
            {
                board_copy[i][j] = '-';

                int test_index = 0;
                for (int x = 0; x < num_rows; x++)
                {
                    for (int y = 0; y < num_cols; y++)
                    {
                        test_board[test_index++] = board_copy[x][y];
                    }
                }
                test_board[test_index] = '\0';  

                int num_x, num_o;
                if (solve(test_board, num_rows, num_cols, &num_x, &num_o) != FOUND_SOLUTION)
                {
                    board_copy[i][j] = original_token;  
                }
            }
        }
    }

    index = 0;
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            medium_board[index++] = board_copy[i][j];
        }
    }
    medium_board[index] = '\0';  

    return medium_board;
}