#include <stdlib.h>
#include <stdio.h>


/*Partners:  wshen15, mcasper3
 * Intro paragraph: One of the errors is at main line 18 and 23, we should change the return value to 1 because -1 is the wrong return value
 * Another error is at main line 26, the semicolon is missing at the end of the statement, creating compile errors
 * An error at semiprime is at is_prime, they flipped return 0 and 1 and that made the is_prime method dysfunctional. 
 * Another error is at print semiprimes, in the loop, k is suppoed to be i/j instead of i%j, creating errors when running numbers
 * Another error at print semiprimes is in the loop as well, they are missing a line of code to set ret=1, and missing a break point at the end made the program printing values multiple times. 
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
			ret=1;
			break;
                    }
                }
            }
        }

    }
     printf("\n");
    return ret;

}
