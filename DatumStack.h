/*
 * DatumStack.h
 * 
 * Comp 15 HW 3
 * Sam Lacet-Brown
 * Oct 2020
 *
 *
 */

#ifndef __DATUMSTACK_H__
#define __DATUMSTACK_H__
 
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Datum.h"
using namespace std;

class DatumStack
{
    public:
        DatumStack();
        DatumStack(Datum datum_vector[], int size);
        ~DatumStack(); 
        bool isEmpty();
        void clear();
        int size();
        Datum top();
        void pop();
        void push(Datum);
        
    private:
        vector<Datum> datum_vector;
        int len;
        void print();
};

#endif
