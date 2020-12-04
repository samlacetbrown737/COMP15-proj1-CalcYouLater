/*
 * DatumStack.cpp
 * 
 * Comp 15 Proj 1
 * Sam Lacet-Brown
 * Oct 2020
 *
 * The DatumStack class holds the vector of Datum
 * as well as all 
 *
 */

#include "Datum.h"
#include "DatumStack.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

//default constructor
DatumStack::DatumStack() {
    len = 0;
    vector<Datum> datum_vector;
} 

//array constructor
DatumStack::DatumStack(Datum datum_arr[], int size) {
    len = size;
    for(int i = 0;  i < size; i++) {
        push(datum_arr[i]);
    }
}

//deconstructor
DatumStack::~DatumStack() {
}

/* isEmpty
 *    Purpose: Determine if the stack is empty
 *    Parameters: none
 *    Returns: a boolean value correlating to if the stack is empty
 */
bool DatumStack::isEmpty() {
    if(size() == 0) {
        return true;
    }
    return false;
}

/* clear
 *    Purpose: Removes everything from the stack
 *    Parameters: none
 *    Returns: none
 */
void DatumStack::clear() {
    int startSize = size();
    if(!isEmpty()) {
        for (int i = 0; i < startSize; i++) {
            pop();
        }
    }
}

/* size
 *    Purpose: Determine the size of the stack
 *    Parameters: none
 *    Returns: an int equal to the length of the stack
 */
int DatumStack::size() {
    return len;
}

/* top
 *    Purpose: Get the top Datum in the stack
 *    Parameters: none
 *    Returns: A Datum
 */
Datum DatumStack::top() {
    if(len != 0) {
        return datum_vector.back();
    } else {
        throw runtime_error("empty_stack");
    }
}

/* pop
 *    Purpose: Remove the top element from the stack
 *    Parameters: none
 *    Returns: none
 */
void DatumStack::pop() {
    if(len != 0) {
        datum_vector.pop_back();
        len--;
    } else {
        throw runtime_error("empty_stack");
    }
}

/* push
 *    Purpose: Add given Datum to the top of the stack
 *    Parameters: none
 *    Returns: none
 */
void  DatumStack::push(Datum d) {
    len++;
    datum_vector.push_back(d);
}

//for testing only, empties stack
/* print
 *    Purpose: Prints and pops everything in the stack
 *    Parameters: none
 *    Returns: none
 */
void DatumStack::print() {
    cout << "[ ";
    int startSize = size();
    for (int i = 0; i < startSize; i++) {
        cout << top().toString() << ' ';
        pop();
    }
    cout << ']' << endl;
}