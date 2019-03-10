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
#ifndef BUFFER_H
#define BUFFER_H

#include <semaphore.h>


/**************************************************
 *
 * Class Buffer Declaration
 *
 * ***********************************************/
class buffer {
    /* private variables and function */
private:
    static const int size = 5; // buffer size
    int item[size]; // array holds items in buffer
    int pin, pout, // producer and consumer position
        count, // number of occupied spaces
        nfull, nempty, // number of times that buffer are full/empty
        total_produced, total_consumed; // total number of items produced/consumed
    // semaphores
    sem_t mutex;
    sem_t full;
    sem_t empty;
    // private function prime check
    bool prime (int);
    
    /* public member function */
public:
    buffer (); // constructor
    int insert_item(int); // insert item to buffer
    int remove_item(); // remover item from buffer
    void printstatus(); // print buffer current status
    void printstatistic(); // print summarized data of buffer
    void printproduced(); // print total number of items produced
    void printconsumed(); // print total number of items consumed
    static int getsize (); // return buffer size
};

#endif
