/*      
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 * Intro Paragraph: This program generates randomized order of strings in an array and asks players to guess the order of the string.
 * Player will recieve different scores based on number of perfect matches and number of mismatches
 * If string is invalid, the program will return a invalid string. 
 * Partners: wshen15, mcasper3
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

int guess_number;
int max_score;
char solutions[4][10];
char* pool[] = {"Vader", "Padme", "R2-D2", "C-3PO", "Jabba", "Dooku", "Lando", "Snoke",};
/* Show guessing pool -- This function prints "pool" to stdout
 * INPUT: none
 * OUTPUT: none
 */
void print_pool() {
    printf("Valid term to guess:\n\t");
    for(int i = 0; i < 8 ; ++i) {
        printf("%s ", pool[i]);
    }
    printf("\n");
}

/*
 * is_valid -- This function checks whether a string is valid
 * INPUTS: str -- a string to be checked
 * OUTPUTS: none
 * RETURN VALUE: 0 if str is invalid, or 1 if str is valid
 * SIDE EFFECTS: none
 */
int is_valid(char* str) {
    int i = 0;
    if (str == NULL) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (strcmp(str, pool[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[]) {
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
    int seed;
    char post[2];
    if (sscanf (seed_str, "%d%1s", &seed, post) != 1) {
      printf("set_seed: invalid seed\n");//return the invalid string
      return 0;
      // your code here
    }
    else
      {
	srand(seed);//generate a random number
	return 1;
      }
    // your code here
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 *               The score should be initialized to -1.  
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game () {
    //your code here
  guess_number=1;//set guess number to 1
  max_score=-1;//set max score to -1
  for(int i=0;i<4;i++)
    {
      int x=rand()%8;//get random number b/w 0 and 7 4 times
      for(int j=0;j<10;j++)
	{
	  char c= *(pool[x]+j);
	  solutions[i][j]=c;//put the random string into solutions string 2 d array
	}
    }
  
  
  
}


int is_equal(char one[], char two[])//helper method, check if two elements in two string arrays are equal
{
  int i;
  for(i=0;one[i]!= '\0' && two[i] != '\0';i++)
    {
      if(one[i]!=two[i])
	{
	  return 0;
	}
    }
  return one[i]==two[i];
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 strings from pool). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: none
 * RETURN VALUE: 2 if guess string is valid and got all 4 perfect matches, or 1 if the guess string is valid, 
 *               or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[]) {
  char guess[4][10];
  char garbage[10];
  int guess_matched[4]={0,0,0,0};
  int solutions_matched[4]={0,0,0,0};
  int perf_match=0;
  int misp_match=0;
  int check=sscanf(guess_str, "%s%s%s%s%1s", guess[0], guess[1], guess[2], guess[3], garbage);
  if(check !=4)
    {
      printf("make_guess: invalid guess\n");
      return 0; //catches invalid input
    }
  for(int i=0;i<4;i++)
    {
      if(is_valid(guess[i])==0)
	{
	  printf("make_guess: invalid guess\n");
	  return 0;//catches invalid words
	}
      
    }
  for(int i=0; i<4; i++)
    {
      if(is_equal(guess[i],solutions[i]))
	{
	  guess_matched[i]=1;
	  solutions_matched[i]=1;
	  perf_match ++;//perfect match counter increments
	}
    }
  for(int i=0;i<4;i++)
    {
      if(guess_matched[i]==1)
	{
	  continue;
	}
      for(int j=0;j<4;j++)
	{
	  if(solutions_matched[j]==1)
	    {
	      continue;
	    }
	  if(is_equal(guess[i], solutions[j]))
	    {
	      guess_matched[i]=1;
	      solutions_matched[j]=1;
	      misp_match++;
	      break;
	    }
	}
    }
  int score=1000*perf_match+100*misp_match;//updates the score
  if(score>max_score)
    {
      max_score=score;//set max score to current score if current score is higher
    }
  printf("With guess %d, you get %d perfect matchs and %d misplaced matches.\nYour score is %d and current max score is %d.\n", guess_number, perf_match, misp_match, score, max_score);
  if(perf_match==4)
    {
      return 2;
    }
  guess_number++;//increment the guess numbers
  return 1;
}




