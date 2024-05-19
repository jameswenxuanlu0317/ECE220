#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
//Intro Paragraph: In this mp, I created a maze, printed the maze, and figured out a way to solve the maze using DFS recursively
//Partners: mcasper3, wshen15


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
maze_t *maze=malloc(sizeof(maze_t));    //creating new maze
FILE *reader = fopen(fileName, "r");    //get the reader
if(reader == NULL)      
{
    return NULL;                        //return null if reader reads null
}
fscanf(reader, "%d", &maze->width);
fscanf(reader, "%d", &maze->height);    //read the width and then height
fgetc(reader);
maze->cells = (char **)malloc(maze->height*sizeof(char*));  
int r, c;                               //row and column variables
for(r=0; r< maze->height; r++)
{
    *(maze->cells+r)=(char *)malloc(maze->width*sizeof(char));
}
for(r=0;r<maze->height;r++)
{
    for(c=0;c<maze->width;c++)
    {
        char curr;
        curr= getc(reader);
        if(curr=='S')
        {
            maze->startColumn=c;
            maze->startRow=r;       //set start row and start column if current character is 'S'
        }
        else if(curr=='E')
        {
            maze->endColumn=c;
            maze->endRow=r;         //set end row and end column if current character is 'E'
        }
        maze->cells[r][c]=curr;     //Set current cell equal to current character
    }
    getc(reader);
}
fclose(reader);
return maze;                        //return the maze created
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int i;
    for(i=0;i<maze->height;i++)
    {
        free(*(maze->cells+i));     //free the cells
    }
    free(maze->cells);
    free(maze);                     //free the maze
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i,j;
    for(i=0;i<maze->height;i++)
    {
        for(j=0;j<maze->width;j++)
        {
            printf("%c", maze->cells[i][j]);    //print out each cell in the maze
        }
        printf("%s\n", "");                     //new line after each row
    }

}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeDFS(maze_t * maze, int col, int row)
{
    if(col<0||row<0||col>=maze->width||row>=maze->height)   //if out of bounds, return 0
        return 0;
    
    if(maze->cells[row][col]!=' ' && maze->cells[row][col] != 'S' && maze->cells[row][col]!='E')   
        return 0;                   

    if(row==maze->endRow && col==maze->endColumn)
    {
        maze->cells[maze->startRow][maze->startColumn]= 'S';    //if start column and start row cell equals 'S', return 1
        return 1;
    }

    maze->cells[row][col]= '*';                                 //set the cell equals '*'

    if(solveMazeDFS(maze, col-1, row))                          
        return 1;
    
    if(solveMazeDFS(maze, col+1, row))
        return 1;    

    if(solveMazeDFS(maze, col, row-1))
        return 1;

    if(solveMazeDFS(maze, col, row+1))                          //trust the recursion to check the neighbor cells
        return 1;

    maze->cells[row][col]= '~';                                 //set the cell equals '~'

    return 0;
}
