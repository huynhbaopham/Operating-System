###########################################################
#
# Simple Makefile
# Producer - Consumer
#
###########################################################

.SUFFIXES: .h .cpp .o

ProCon: buffer.o ProCon.o
	g++ buffer.o ProCon.o -lpthread -std=c++11 -o osproj3

ProCon.o: ProCon.cpp buffer.h
	g++ -c ProCon.cpp buffer.h -lpthread -std=c++11

buffer.o: buffer.cpp buffer.h
	g++ -c buffer.cpp buffer.h -lpthread -std=c++11

clean:
	/bin/rm -f *.o *.gch ProCon


