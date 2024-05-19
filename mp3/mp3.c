#include <stdio.h>
#include <stdlib.h>
//This program takes an input of row number and then print out the 
//corresponding pascal triangle
//Partners: wshen15, mcasper3
int main()
{
  int row;
  printf("Enter a row index: ");
  scanf("%d",&row);//get the input

  unsigned long ans, i, j;//initialize variables
  for(i=0;i<=row;i++)//outer loop
    {
      ans = 1;
      for(j=1;j<=i;j++)//inner loop
	{
	  ans=ans*(row+1-j)/j;//formula for pascal
	}
      printf("%lu ", ans);//print out the value
    }
  printf("\n");//print a new line
  return 0;//return 0 to end the program
	
}
