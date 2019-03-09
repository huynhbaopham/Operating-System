//********************************************************************
//
// Bao Pham
// Operating Systems
// Programming Project #2: Printing Words With sched_yield()
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
#include <string>
#include <sched.h>
#include <vector>

using namespace std;

/**************************************************
 *
 * Declarations
 *
 * ***********************************************/
/* Global variables*/
int size = 0; // hold the number of words in sentence
int ii = 0; // iterator
string* toks = nullptr; // string array hold flag's contains, to pass to vow and con functions
string vowels = "AEUIOaeuio";
/* vow function prints words starting with vowel */
void* vow (void*);
/* con function prints words starting with consonants */
void* con (void*);
/* find fuction return true if find a character from delim char array */


/**************************************************
 *
 * Main Function
 *
 * ***********************************************/
int main(int argc, char *argv[])
{
    /* local variables */
    pthread_t tid[2];
    pthread_attr_t attr;
    
   // get size of vector flag
    size = argc - 1;

    if (size > 0) // convert vector flag to string array tok
    {
        toks = new string[size];
        for (int i = 1; i <= size; i++)
            toks[i-1] = argv[i];
    }
    else // terminate the program if user input nothing
    {    // or input only delimiters but no word
        fprintf(stderr,"error: No word found!\n");
        return -1;
    }
    
    /* Thread */
    pthread_attr_init(&attr); // get default atrribute
    pthread_create (&tid[1], &attr, con, nullptr); // child thread handling
    pthread_create (&tid[0], &attr, vow, nullptr); // child thread handling
    
    /* wait for both threads exit to exit program */
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    
    delete [] toks; // deallocate tok before exit
    return 0;
    
}


//********************************************************************
//
// vow Function
//
// This function search through the input sentence and print valid 
// words starting with vowel.
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
// word		    string		Contains each word in Toks
// isValidWord	bool		True/False if the word starts with letter
// startWithVow	bool		True/False if the word starts with vowel
//
//*******************************************************************
void* vow (void*)
{
    /* Local variables */
    string word; // flag hold word to be executed
    bool isValidWord, startWithVowel;
    while (ii<size)
    {
        word = toks[ii]; // convert toks[ii] to string
        isValidWord = isalpha(word[0]);
        startWithVowel = vowels.find(word[0])!=string::npos;
        if (!isValidWord) // limit within alphabet character
        {
            fprintf (stderr, "* %s: Not a world!\n", word.c_str());
            ii++; // increase iterator to skip the invalid world, prevent deadlock
        }
        //else if (isValidWord && !startWithVowel);
            //sched_yield(); // if not, yield to the other thread 
        if (startWithVowel)// not a valid world
        {
            printf ("vow: %s\n", word.c_str()); // if 1st character is a vowel
            ii++;
        }
    }
    pthread_exit(NULL);
}


//********************************************************************
//
// con Function
//
// This function search through the input sentence and print valid 
// words starting with consonant.
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
// word		    string		Contains each word in Toks
// isValidWord	bool		True/False if the word starts with letter
// startWithCon	bool		True/False if the word starts with con
//
//*******************************************************************
void* con (void*)
{
    /* Assign fibonacci sequence to array fib */
    string word;
    bool isValidWord, startWithCon;
    while (ii < size)
    {
        word = toks[ii];
        isValidWord = isalpha(word[0]);
        startWithCon = vowels.find(word[0])==string::npos;
        if (isValidWord && startWithCon) // limit within alphabet character
        {                               // move to next word if starts with vowel
            printf ("con: %s\n", word.c_str()); // print out if starts with consonant
            ii++;
        }
        //else // not start with consonant
            //sched_yield();
        /* we don't need to a branch for not a valid word, because the vow() function would increase 
        the iterator ii by one already. If we have it here, they would be redundancy and skip a word
        sometimes */
    }
    pthread_exit(NULL);
}
