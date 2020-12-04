#include "Datum.h"
#include "DatumStack.h"
#include "RPNCalc.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

string parseRString(istream &input) {
     string x;
     stringstream ss;
     ss << "{";
    while(!(x == "}")) {    
       ss << x;
       ss << " ";
       input >> x;
    }
    ss << "}";
    x = ss.str();
    return x;
}