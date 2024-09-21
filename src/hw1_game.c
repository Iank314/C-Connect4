#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "hw1.h"

#define NUM_ROWS 20
#define NUM_COLS 20

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

void print_board(int num_rows, int num_cols) 
{
    for (int i = 0; i < num_rows; i++) 
    {
        for (int j = 0; j < num_cols; j++) 
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
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
        print_board(num_rows, num_cols);
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
                if (board[i][j] == '-') 
                {
                    full = false;
                    break;
                }
            }
        }
        if (full) 
        {
            printf("Congratulations, you have filled the board with no 4-in-a-rows!\n");
            print_board(num_rows, num_cols);
            break;
        }
    }
}

int main(int argc, char **argv) 
{
    assert(argc == 4);

    int num_rows = (int)strtoul(argv[1], NULL, 10);
    int num_cols = (int)strtoul(argv[2], NULL, 10);

    assert(num_rows <= NUM_ROWS && num_cols <= NUM_COLS);

    initialize_board(argv[3], num_rows, num_cols);
    play_game(num_rows, num_cols);

    return 0;
}
