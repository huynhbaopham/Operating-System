#ifndef HISTORY_H
#define HISTORY_H

#define SIZE 10

class History {
private:
    char *** items;
    int start;

public:
    History() {
        items = new char ** [SIZE];
        start = -1; //start position of reading
    }

    void add(char ** toks) {
        int size = len(toks);
        start += 1;
        start %= 10;
    }

private:
    int len(char ** toks) {
        int ii = 0;
        for (ii; toks[ii]!=NULL; ii++);
        return ii-1;
    }
}