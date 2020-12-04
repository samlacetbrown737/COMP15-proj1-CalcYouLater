/* 
 * testDatumStack.cpp
 * 
 * Comp 15 Proj 1
 * Sam Lacet-Brown
 * Oct 2020
 *
 *
 */

#include <iostream>
#include <string>
#include <vector>

#include "Datum.h"
#include "DatumStack.h"
#include "RPNCalc.h"

using namespace std;
/* main
 *    Purpose: Tests the functions of the DatumStack
 *    Parameters: none
 *    Returns: none
 */
int main(int argc, char *argv[]) {
    DatumStack *data = new DatumStack();
    cout << "empty? " << data->isEmpty() << endl;
    cout << "size? " << data->size() << endl;
    data->push(Datum(3));
    data->push(Datum(7));
    data->push(Datum(5));
    cout << "empty? " << data->isEmpty() << endl;
    data->pop();
    cout << "size? " << data->size() << endl;
    cout << "top " << data->top().toString() << endl;
    data->clear();
    cout << "empty? " << data->isEmpty() << endl;
    Datum arr[3] = { Datum(4), Datum(2), Datum(6) };
    DatumStack *data2 = new DatumStack(arr, 3);
    cout << "top " << data2->top().toString() << endl;
    data2->pop();
    cout << "top " << data2->top().toString() << endl;
    data2->pop();
    cout << "top " << data2->top().toString() << endl;
    delete data;
    delete data2;
}