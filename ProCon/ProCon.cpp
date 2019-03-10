/**************************************************
 *
 * Bao Pham
 * Project 3 - COSC 3346
 * osproj3.cpp - main program
 *
 * ************************************************/


/**************************************************
 *
 * Includes and Defines
 *
 * ***********************************************/
#include <stdlib.h>
#include <cctype>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "buffer.h"
#include <semaphore.h>

using namespace std;

/**************************************************
 *
 * Declarations
 *
 * ***********************************************/
// buffer object
buffer item;
// holds data from user inputs
int input[5];
// indicators for input[]
const int main_sleep = 0, pro_sleep = 1, con_sleep = 2, pro_num = 3, con_num = 4;

// array holding the numbers of successful insert/remove of each thread
int * produced = nullptr;
int * consumed = nullptr;

// thread producer and consumer functions
void* producer (void*);
void* consumer (void*);
// function displays all statistic when program ends
void Statistics ();

/**************************************************
 *
 * Main Function
 *
 * ***********************************************/
int main(int argc, char *argv[])
{
    // hold user request yes/no on printing statistics.
    bool display;
    
    /* validates user inputs */
    // too many/less arguments
    if (argc != 7)
    {
        printf("Error: Too many/less arguments.\n");
        return -1;
    }
    
    // arguments must be digits
    for (int i = 1; i <=5; i ++)
    {
        for (int j = 0; argv[i][j] != '\0'; j++)
        {
            if (!isdigit(argv[i][j]))
            {
                printf("Error: Invalid argument(s). Must be integer.\n");
                return -1;
            }
        }
        input[i-1] = atoi(argv[i]);
    }
    
    // last argument should start with Y/y or N/n
    if (toupper(argv[6][0])=='N')
    {
        display = false;
    }
    else if (toupper(argv[6][0])=='Y')
    {
        display = true;
    }
    else
    {
        printf("Error: Invalid argument (6th): Yes or No.\n");
        return -1;
    }

    // initial the sizes of produced and consumed array
    produced = new int[input[pro_num]];
    consumed = new int[input[con_num]];
    
    // initial all consumers and producers threads
    pthread_t pro_tid[input[pro_num]], con_tid[input[con_num]];
    pthread_attr_t pro_attr, con_attr;
    
    pthread_attr_init(&pro_attr); // get default atrribute
    pthread_attr_init(&con_attr); // get default atrribute

    // Run all producer thread(s)
    for (int i = 0;  i < input[pro_num]; i++)
    {
        if (pthread_create (&pro_tid[i], &pro_attr, producer, (void*) (produced+i))!=0)
            perror("pthread_create"); // check error creating producer threads
    }

    // Run all consumer thread(s)
    for (int i = 0;  i < input[con_num]; i++)
    {
        if (pthread_create (&con_tid[i], &con_attr, consumer, (void*) (consumed+i))!=0)
            perror("pthread_create"); // check error creating consumer threads
    }
    
    // Put main thread to sleep
    if (sleep(input[main_sleep])!=0)
        perror("Main thread was interupted while sleeping"); // check if main thread was interupted while sleeping
    
    // Join all producer and consumer threads
    // producer
    for (int i = 0;  i < input[pro_num]; i++)
    {
        if (pthread_cancel(pro_tid[i])!=0)
            perror("pthread_cancel");
    }
    // consumer
    for (int i = 0;  i < input[con_num]; i++)
    {
        if (pthread_cancel(con_tid[i])!=0)
            perror("pthread_cancel");
    }
    // Display statistic if requested
    if (display)
    {
        Statistics();
    }
    // exit
    return 0;
}

/**************************************************
 *
 * Producer Function
 *
 * ***********************************************/
void* producer (void* n)
{
    //initial limit at 1000
    int push = 1000;
    while(true)
    {
        // put this procuder thread to sleep
        if (sleep(input[pro_sleep])!=0)
            perror("Producer thread was interupted while sleeping"); // check if this thread was interupted while sleeping
        // insert a random integer to buffer and update produced count if succeed
        (*(int*)n) += item.insert_item(rand()%push);
    }
}

/**************************************************
 *
 * Consumer Function
 *
 * ***********************************************/
void* consumer (void* n)
{
    while (true) {
        // put this consumer thread to sleep
        if (sleep(input[con_sleep])!=0)
            perror("Consumer thread was interupted while sleeping"); // check if this thread was interupted while sleeping
        // remove a number from buffer and update consumed count if succeed
        (*(int*)n) += item.remove_item();
    }
}

/**************************************************
 *
 * Statistic Function
 * Display statistics
 *
 * ***********************************************/
void Statistics ()
{
    // Display initial statistics
    printf("\nPRODUCER / CONSUMER SIMULATION COMPLETE\n");
    printf("=======================================\n");
    printf("Simulation Time:                      %d\n", input[main_sleep]);
    if (input[pro_sleep]>input[con_sleep])
        printf("Maximum Thread Sleep Time:            %d\n", input[pro_sleep]);
    else
        printf("Maximum Thread Sleep Time:            %d\n", input[con_sleep]);
    printf("Number of Producer Threads:           %d\n", input[pro_num]);
    printf("Number of Consumer Threads:           %d\n", input[con_num]);
    printf("Size of Buffer:                       %d\n\n", item.getsize());
    
    // Display total number of successfull items produced.
    item.printproduced();
    // Display number of items produced by each thread.
    for (int i = 0; i < input[pro_num]; i++)
    {
        printf("\tThread %d:                     %d\n", i+1, produced[i]);
    }
    printf("\n");
    
    // Display total number of successfull items consumed.
    item.printconsumed();
    // Display number of items consumed by each thread.
    for (int i = 0; i < input[con_num]; i++)
    {
        printf("\tThread %d:                     %d\n", i+input[pro_num]+1, consumed[i]);
    }
    printf("\n");
    
    // Display summarized data about buffer.
    item.printstatistic();
}
