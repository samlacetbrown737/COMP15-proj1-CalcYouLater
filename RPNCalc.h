/*
 * RPNCalc.h
 * 
 * Comp 15 HW 3
 * Sam Lacet-Brown
 * Oct 2020
 *
 *
 */

#ifndef __RPNCALC_H__
#define __RPNCALC_H__

#include <iostream>
#include <vector>
#include <string>
#include "Datum.h"
#include "DatumStack.h"
using namespace std;

class RPNCalc
{
    public:
        RPNCalc();
        ~RPNCalc();
        void run();
    private:
        DatumStack data;
        void doCommands(istream &input);
        void parseCommands(string command);
        void ifEval(string falseCase, string trueCase, bool test);
        int stackSize();
        void test();  
        void print();
        void numAdd(string num);
        void boolAdd(string set);
        void clear();
        void notMod();
        void assess(string oper);
        void compare(string oper);
        void drop();
        void swap();
        void dup();
        string parseRString(istream &input);
        Datum rstring(istream &input);
        void exec();
        void file();
        void ifCheck();
};

#endif
