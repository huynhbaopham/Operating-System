# Operating System
# Bao Pham
This contains all of the project I have done during the Operating System.
# Projects
## Shell
## Thread Scheduling
Two threads share the resources for printing words starting with vowels & consonants in order of user input.

Include 2 files:
1. VowCon.cpp
2. Makefile

Use Makefile to compile:
```terminal
$ make
```

To run:
```terminal
$ ./vc Your sentence containing any words you want!
```
## Fibonacci
Parent thread waiting for child thread to finish generating Fibinacci sequence before printing it out.

Include 2 files:
1. Fibonacci.cpp
2. Makefile

Use Makefile to compile:
```terminal
$ make
```

To run:
```terminal
$ ./fib n
```
> n is the total number of elements in the sequence

## Producer-Consumer
Using semaphore for solving Producer - Consumer problem.

Include 4 files:
1. buffer.cpp
2. buffer.h
3. ProCon.cpp
4. Makefile

Use Makefile to compile:
```terminal
$ make
```

To run:
```terminal
$ ./ProCon a1 a2 a3 a4 a5 b
```
where:
* a1 is the time main thread sleep
* a2 is the time producer sleep
* a3 is the time consumer sleep
* a4 is the producer number of threads
* a5 is the consumer number of threads
* b is Yes or No to request print statistics when program ends

## Banker
The banker algorithm is implemented using 2 different languages python and cpp. 

Include 4 files:
1. banker.cpp
2. Matrix.h
3. Makefile
4. banker.py

**banker.cpp**:

To compile: 
```terminal
$ make
```

To run: 
```terminal
$ ./banker infile.txt
```

**bankerpy.py**: run on python 3

To run: 
```terminal
$ python3 bankerpy.py infile.txt
```

# Note
*Please use them as a reference only.*
### end