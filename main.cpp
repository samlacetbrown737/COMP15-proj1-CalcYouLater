/* 
 * main.cpp
 * 
 * Comp 15 Proj 1
 * Sam Lacet-Brown
 * Oct 2020
 *
 * Holds testing functions and  calls RPNCalc constructor
 *
 */

#include <iostream>
#include <string>
#include <vector>

#include "Datum.h"
#include "DatumStack.h"
#include "RPNCalc.h"

using namespace std;

void startCalc() {
    RPNCalc *calc = new RPNCalc();
    calc->run(); 
    delete calc;
}

int main(int argc, char *argv[]) {
    startCalc();
}

