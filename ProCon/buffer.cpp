/**************************************************
 *
 * Bao Pham
 * Project 3 - COSC 3346
 * buffer.cpp - buffer class definition
 *
 * ************************************************/


/**************************************************
 *
 * Includes and Defines
 *
 * ***********************************************/
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include "buffer.h"

using namespace std;

/**************************************************
 *
 * Constructor
 * Initializes all variables
 *
 * ************************************************/
buffer::buffer ()
{
    // initial all items in buffer is -1
    for (int i = 0; i < size; i++)
        item[i] = -1;
    // positions of producer and consumer
    pin = 0;
    pout = 0;
    count = 0; // number of items in buffer at the time
    nfull = 0; // number of time the buffer full
    nempty = 0; // number of time the buffer empty, doesn't count when the buffer is initialied.
    total_produced = 0; // total number of items produced
    total_consumed = 0; // total number of items consumed
    sem_init(&mutex, 0, 1); // mutex semaphore
    sem_init(&full, 0, 0); // full semaphore
    sem_init(&empty, 0, size); // empty semaphore
    // indicate the buffer initialized
    printf("Starting thread...\n");
    printstatus();
}

/**************************************************
 *
 * Insert function
 * Takes an integer
 * and return 1 if succeed, 0 if buffer full
 *
 * ************************************************/
int buffer::insert_item(int push)
{
    sem_wait(&mutex); // lock mutex
    int flag = 0; // set flag
    // checking buffer status
    if (count == size) // if full
    {
        cout << "All buffers full.  Producer "<< pthread_self() << " waits.\n\n";
    }
    else // if not full
    {
        sem_wait(&empty); // update empty semaphore
        item[pin] = push; // insert push to buffer
        pin = (pin + 1) % size; // update producer position
        count++; // update buffer status
        nfull += (count==5);// check if full and update
        total_produced++; // update total items produced
        flag = 1; // set flag
        // print out thread's action
        cout << "Producer " << pthread_self() <<" writes " << push << endl;
        // print current buffer status
        printstatus();
        
        sem_post(&full); // update full semaphore
    }
    sem_post(&mutex); // release mutex

    return flag;
    
}

/**************************************************
 *
 * Remove function
 * Remove an item from buffer
 * and return 1 if succeed, 0 if buffer full
 *
 * ************************************************/
int buffer::remove_item()
{
    sem_wait(&mutex); // lock mutex
    int flag = 0; // set flag
    // check if buffer empty
    if (count == 0) // if empty
    {
        cout << "All buffers empty.  Consumer " << pthread_self() << " waits.\n\n";
    }
    else // if not empty
    {
        int pop; // will hold the item removed from buffer
        sem_wait(&full); // update full semaphore
        
        pop = item[pout]; // copy item to pop
        item[pout] = -1; // remove item
        pout = (pout+1) % size; // update consumer position
        count--; // update buffer status
        nempty += (count == 0); // check if empty, update nempty
        total_consumed++; // update total number consumed
        flag = 1; // set flag
        // print out thread's action
        cout << "Consumer " << pthread_self() << " reads ";
        // check and display if number is prime
        if (prime (pop))
            printf("%d   * * * PRIME * * *\n", pop);
        else
            printf("%d   * * * NONPRIME * * *\n", pop);
        // display buffer current status
        printstatus();
        sem_post(&empty); // update empty semaphore
    }
    
    sem_post(&mutex); // release mutex
    
    return flag;
    
}

/**************************************************
 *
 * Prime function
 * Check if the number is prime
 *
 * ************************************************/
bool buffer::prime (int num)
{
    if (num < 2)
        return false;
    for (int i = 2; i < sqrt(num); i++)
    {
        if ((num % i) == 0)
            return false;
    }
    return true;
}

/**************************************************
 *
 * Printstatus function
 * Display buffer current status
 *
 * ************************************************/
void buffer::printstatus()
{
    // number of occupied spaces
    printf("(buffers occupied: %d)\n", count);
    printf("buffers:  ");
    // display all spaces in buffer
    for(int i = 0; i < size; ++i)
        printf("%*d", 5, item[i]);
    // seperator
    printf("\n          ");
    for(int i = 0; i < size; ++i)
        printf(" ----");
    // read (R) and write (W) position
    printf("\n           ");
    if (pin >= pout)
    {
        for(int i = 0; i < pout; ++i)
            printf("     ");
        printf (" R");
        for(int i = 0; i < pin-pout; ++i)
            printf("     ");
        printf ("W");
    }
    else
    {
        for(int i = 0; i < pin; ++i)
            printf("     ");
        printf (" W");
        for(int i = 0; i < pout-pin; ++i)
            printf("     ");
        printf ("R");
    }

    printf("\n\n");
}

/**************************************************
 *
 * Printstatistic function
 * Display buffer summarized statistics
 *
 * ************************************************/
void buffer::printstatistic ()
{
    printf("Number Of Items Remaining in Buffer:  %d\n", count);
    printf("Number Of Times Buffer Was Full:      %d\n", nfull);
    printf("Number Of Times Buffer Was Empty:     %d\n", nempty);
}

/**************************************************
 *
 * Printproduced function
 * Display total number of items produced
 *
 * ************************************************/
void buffer::printproduced ()
{
    printf("Total Number of Items Produced:       %d\n", total_produced);
}

/**************************************************
 *
 * Printconsumed function
 * Display total number of items consumed
 *
 * ************************************************/
void buffer::printconsumed()
{
    printf("Total Number of Items Consumed:       %d\n", total_consumed);
}

/**************************************************
 *
 * Getsize function
 * Return size of buffer
 *
 * ************************************************/
int buffer::getsize()
{
    return size;
}
