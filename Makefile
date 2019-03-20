###########################################################
#
# Simple Makefile for HW 3
#
###########################################################
.SUFFIXES: .cpp

HW3: HW3.cpp
	g++ HW3.cpp -o HW3 -std=c++11

clean:
	/bin/rm -f *.o *~ core HW3