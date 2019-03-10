//********************************************************************
//
// Bao Pham
// Operating Systems
// Programming Project #2: Fibonacci sequence generator
// Spring 2018
// Instructor: Dr. Dulal C. Kar
//
//********************************************************************

/**************************************************
 *
 * Includes and Defines
 *
 * ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>

using namespace std;

/**************************************************
 *
 * Declarations
 *
 * ***********************************************/
/* Global vector holding Fibonacci sequence*/
long *fib = nullptr;
/* fibonacci function */
void *fibonacci(void *);
/* last position of fibonacci number generated */
int n;

/**************************************************
 *
 * Main Function
 *
 * ***********************************************/
int main(int argc, char *argv[])
{
    /* local variables */
    pthread_t tid;
    pthread_attr_t attr;

    /* check for valid syntax
     2 agruments */
    if (argc != 2)
    {
        fprintf(stderr, "usage: ./fibonacci <integer value>\n");
        return -1;
    }

    /* check for valid input of n */
    for (int i = 0; argv[1][i]; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            fprintf(stderr, "Non negative integer only!\n");
            return -1;
        }
    }

    /* check the range of n 
    system can only support integer <= 92 (long type) */
    if (n > 92)
        fprintf(stderr, "Integer in range [0,92] only!\n");

    n = atoi(argv[1]); // set n
    fib = new long[n + 1]; // set size of the array holding the fibonacci series

    pthread_attr_init(&attr);                              // get default atrribute
    pthread_create(&tid, &attr, fibonacci, nullptr); // child thread handling fibonacci function
    pthread_join(tid, NULL);                               // wait for child thread to exit

    /* parent thread print the fibonacci sequence after child thread finish */
    for (int i = 0; i <= n; i++)
        printf("fib%d = %ld\n", i, fib[i]);

    delete[] fib; // deallocate the array fib

    return 0;
}

//********************************************************************
//
// fibonacci Function
//
// Generates Fibonacci sequence with n elements.
//
// Return Value
// ------------
// void*
//
// Value Parameters
// ----------------
// NONE
//
// Reference Parameters
// --------------------
// void*
//
// Local Variables
// ---------------
// last		    int		    Hold value of n as integer
//
//*******************************************************************
void *fibonacci(void*)
{
    /* Assign fibonacci sequence to array fib */
    fib[0] = 0;
    if (n > 0) //prevent buffer overflow if n < 1
        fib[1] = 1;
    for (int i = 2; i <= n; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
    pthread_exit(NULL);
}
