#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
// Intro Paragraph: For this mp, I made methods to solve a sudoku
// First, I made methods to check if values are in row or column or in the 3x3 box
// and then I made a helper methods to check if everything is filled up
// and then, I used those helper methods to make a recursive solving method. 
// Partners: wshen15, mcasper3
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Loop through every row to check if given value matches the value at the row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  for(int j=0;j<9;j++)
    {
        if(sudoku[i][j]==val)
        {
            return 1;
        }
    }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Loop through every column to check if given value matches the value at the column
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  for(int i=0;i<9;i++)
    {
        if(sudoku[i][j]==val)
        {
            return 1;
        }
    }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Get the start row and column of the current 3x3 zone and then loop through column and rows to find if anything matches
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  int row=(i/3)*3;//start row
  int col=(j/3)*3;//start column
    for(int a=row; a<row+3; a++)
    {
        for(int b=col; b<col+3; b++)
        {
            if(sudoku[a][b]==val)
            {
                return 1;
            }
        }
    }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Check if value is valid by calling previous three helper methods
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if((is_val_in_row(val, i, sudoku)==1)||(is_val_in_col(val, j, sudoku)==1)||(is_val_in_3x3_zone(val, i, j, sudoku)==1))
    {
        return 0;
    }
  return 1;
  // END TODO
}

//boolean function to check if everything is filled up
//loop through everything and check if there are any zeros
bool isDone(int sudoku[9][9])
{
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      if(sudoku[i][j]==0)
      {
        return false;
      }
    }
  }
  return true;
}

// Procedure: solve_sudoku
// main method to solve the sudoku. 
// if everything filled up, return 1 and sudoku is solved
// else, loop through everything and find zeros, break out of the loop first, and then solve for the current spot
// recursively calling solve sudoku until everything is done
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int row,col;
  if(isDone(sudoku))
  {
    return 1;
  }
  else
  {
    for(int i=0;i<9;i++)
    {
      for(int j=0;j<9;j++)
      {
        if(sudoku[i][j]==0)
        {
          row=i;
          col=j;
          break;
        }
      }
    }
  }

  for(int i=1;i<=9;i++)
  {
    if(is_val_valid(i, row, col, sudoku))
    {
      sudoku[row][col]=i;
     if(solve_sudoku(sudoku))
     {
       return 1;
     }
        sudoku[row][col]=0;
    }
  }

  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





