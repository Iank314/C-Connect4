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
#define INITIAL_BOARD_NO_SOLUTION -4



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

bool check_four_in_a_row(int row, int col, char piece, int num_rows, int num_cols) 
{
    int count = 0;
    for (int j = 0; j < num_cols; j++) 
    {
        if (board[row][j] == piece) count++;
        else count = 0;
        if (count == 4) return true;
    }

    count = 0;
    for (int i = 0; i < num_rows; i++) 
    {
        if (board[i][col] == piece) count++;
        else count = 0;
        if (count == 4) return true;
    }

    count = 0;
    for (int i = -3; i <= 3; i++) 
    {
        if (row + i >= 0 && row + i < num_rows && col + i >= 0 && col + i < num_cols) 
        {
            if (board[row + i][col + i] == piece) count++;
            else count = 0;
            if (count == 4) return true;
        }
    }

    count = 0;
    for (int i = -3; i <= 3; i++) 
    {
        if (row + i >= 0 && row + i < num_rows && col - i >= 0 && col - i < num_cols) 
        {
            if (board[row + i][col - i] == piece) count++;
            else count = 0;
            if (count == 4) return true;
        }
    }

    return false;
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

        if (check_four_in_a_row(row, col, piece, num_rows, num_cols)) 
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
bool check_four_in_a_diagonal(int row, int col, char piece, int num_rows, int num_cols)
{
    int count = 0;

    for (int i = -3; i <= 3; i++)
    {
        if (row + i >= 0 && row + i < num_rows && col + i >= 0 && col + i < num_cols)
        {
            if (board[row + i][col + i] == piece)
            {
                count++;
                if (count == 4)
                {
                    return true;
                }
            }
            else
            {
                count = 0;
            }
        }
    }

    count = 0;
    for (int i = -3; i <= 3; i++)
    {
        if (row + i >= 0 && row + i < num_rows && col - i >= 0 && col - i < num_cols)
        {
            if (board[row + i][col - i] == piece)
            {
                count++;
                if (count == 4)
                {
                    return true;
                }
            }
            else
            {
                count = 0;
            }
        }
    }

    return false;
}
int solve(const char *initial_state, int num_rows, int num_cols, int *num_x, int *num_o)
{
    int state_length = strlen(initial_state);
    if (state_length != num_rows * num_cols)
    {
        return INITIAL_BOARD_INVALID_CHARACTERS;
    }

    initialize_board(initial_state, num_rows, num_cols);

    *num_x = 0;
    *num_o = 0;
    bool four_in_a_row_found = false;
    
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            if (board[i][j] == 'x')
            {
                (*num_x)++;
                if (check_four_in_a_row(i, j, 'x', num_rows, num_cols) || check_four_in_a_diagonal(i, j, 'x', num_rows, num_cols))
                {
                    four_in_a_row_found = true;
                }
            }
            else if (board[i][j] == 'o')
            {
                (*num_o)++;
                if (check_four_in_a_row(i, j, 'o', num_rows, num_cols) || check_four_in_a_diagonal(i, j, 'o', num_rows, num_cols))
                {
                    four_in_a_row_found = true;
                }
            }
            else if (board[i][j] != '-')
            {
                return INITIAL_BOARD_INVALID_CHARACTERS;
            }
        }
    }

    if (four_in_a_row_found)
    {
        return INITIAL_BOARD_FOUR_IN_A_ROW;
    }

    bool changed;
    do
    {
        changed = false;

        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_cols; j++)
            {
                if (board[i][j] == '-')
                {
                    board[i][j] = 'x';
                    if (check_four_in_a_row(i, j, 'x', num_rows, num_cols) || check_four_in_a_diagonal(i, j, 'x', num_rows, num_cols))
                    {
                        board[i][j] = 'o';
                        (*num_o)++;
                        changed = true;
                    }
                    else
                    {
                        board[i][j] = 'o';
                        if (check_four_in_a_row(i, j, 'o', num_rows, num_cols) || check_four_in_a_diagonal(i, j, 'o', num_rows, num_cols))
                        {
                            board[i][j] = 'x';
                            (*num_x)++;
                            changed = true;
                        }
                        else
                        {
                            board[i][j] = '-';
                        }
                    }
                }
            }
        }
    } while (changed);

    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            if (board[i][j] == '-')
            {
                return HEURISTICS_FAILED;
            }
        }
    }

    return FOUND_SOLUTION;
}
char* generate_medium(const char *final_state, int num_rows, int num_cols)
{
    char board_copy[NUM_ROWS][NUM_COLS];
    char *medium_board = (char*)malloc((num_rows * num_cols + 1) * sizeof(char));

    if (medium_board == NULL)
     {
        return NULL;
    }

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

                char test_board[num_rows * num_cols + 1];
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