/*
 * Intro paragraph:
 * In this mp, I will implement three methods for the game of life: countLiveNeighbor, updateBoard, and aliveStable
 * In countLiveNeighbor, I will be counting the number of cells alive that is next to the current row and col, if neighbor cells are 1, then increment the counter. Return the final answer once done with everything
 * In update board, I will update the game board to the next step. I will make a copy of the board, count amount of live neighbors, update the copy and copy it to the original board
 * Int aliveStable, I will update the game board first and then compare it to the original board. If both boards matched, it will return 1, else it returns a 0
 * Partners: wshen15, mcasper3
 *
 *
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
  int ans=0;
  for(int i=row-1;i<=row+1;i++)
    {
      if((i>=0)&&(i<boardRowSize))
	{
	  for(int j=col-1;j<=col+1;j++)
	    {
	      if((j>=0)&&(j<boardColSize))
		{
		  if((i!=row)||(j!=col))//skip current row col
		    {
		      ans+= *(board+(i*boardColSize)+j);//update the counter
		    }
		}
	    }
	}
    }
  return ans;//return the counter
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
  int liveNeighbors=0;
  int size=boardRowSize*boardColSize;//total amount of elements
  int boardCopy[size];//create a copy board
  for(int i=0;i<size;i++)
    {
      boardCopy[i]= *(board+i);//copy everything
    }
  for(int j=0;j<boardRowSize;j++)
    {
      for(int k=0;k<boardColSize;k++)
	{
	  liveNeighbors=countLiveNeighbor(board, boardRowSize, boardColSize, j, k);//get the number of live neighbors
	  if(liveNeighbors==3)
	    {
	      boardCopy[j*boardColSize+k]=1;//set the board to 1 if number of live neighbors is 3
	    }
	  else if(liveNeighbors<2 || liveNeighbors>3)
	    {
	      boardCopy[j*boardColSize+k]=0;//other wise set it to 0 if number of live neighbors are less than 2 or greater than 3
	    }
	}
    }
  for(int i=0;i<boardRowSize;i++)
    {
      for(int j=0;j<boardColSize;j++)
	{
	  *(board+i*boardColSize+j)=boardCopy[i*boardColSize+j];//copy the copy board to the original board, finish the update
	}
    }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
  
  int size=boardRowSize*boardColSize;
  int new[size];//create a new board
for(int i=0;i<size;i++)
    {
      new[i]= *(board+i);
    }
 updateBoard(new, boardRowSize, boardColSize);//update the board to the new board
for(int i=0;i<size;i++)
  {
    if(*(board+i)!=new[i])
      {
	return 0;//if new board and original board don't match, return 0
      }
  }
 return 1;//otherwise return 1
}

				
				
			

