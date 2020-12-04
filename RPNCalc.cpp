/* 
 * RPNCalc.cpp
 * 
 * Comp 15 Proj 1
 * Sam Lacet-Brown
 * Oct 2020
 *
 * The RPNCalc class holds the DatumStack and processes all commands
 *
 */

#include "Datum.h"
#include "DatumStack.h"
#include "RPNCalc.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

//default constructor
RPNCalc::RPNCalc() {

}

//deconstructor
RPNCalc::~RPNCalc() {

}

/* run
 *    Purpose: Starts accepting input from cin
 *    Parameters: none
 *    Returns: none
 */
void RPNCalc::run() {
    doCommands(cin);
    cerr << "Thank you for using CalcYouLater.\n";
}

/* run
 *    Purpose: Processes commands from given stream, 
 *    checks if data is quit/eof, an int, or an rstring,
 *    passes it along if it's something else
 *    Parameters: istream to process commands from
 *    Returns: none
 *    Notes: processes command one more time if eof, ends if quit
 */
void RPNCalc::doCommands(istream &input) {
    string command;
    bool isNum;
    input >> command;
    int run = 1;
    while (run != -1 && command != "quit") {
        isNum = true;
        for(int i = 0; i < command.length(); i++) {
            if (isdigit(command[i]) == false) {
                isNum = false;
            }
        }
        if(isNum) {
            numAdd(command);
        } else if (command == "{") {
            data.push(rstring(input));
        }
         else {
            parseCommands(command);
        }
        input >> command;
        if(run == 0){
            run = -1;
        }
        else if(input.eof()) {
            run = 0;
        }
    }
}

/* parseCommands
 *    Purpose: Runs the proper function based on the given command
 *    Parameters: string of given instruction
 *    Returns: none
 */
void RPNCalc::parseCommands(string command) {
    if (command == "#t"|| command == "#f") {
        boolAdd(command);
    } else if (command == "not") {
        notMod();
    } else if (command == "print") {
        print();
    } else if (command == "clear") {
        clear();
    } else if (command == "drop") {
        drop();
    } else if (command == "dup") {
        dup();
    } else if(command == "swap") {
        swap();
    } else if (command == "+" || command == "-" || command == "*" ||
        command == "/" || command == "mod") {
        assess(command);
    } else if (command == "<" || command == ">" || command == "<=" ||
        command == ">=" || command == "==") {
        compare(command);
    } else if (command  == "exec") {
        exec();
    } else if(command == "file") {
        file();
    } else if (command == "if") {
        ifCheck();
    } else {
        if(command != "}") {
            cerr << command << ": unimplemented";
        }
    }
}

/* print
 *    Purpose: 
 *    Parameters: none
 *    Returns: none
 */
void RPNCalc::print() {
    if(stackSize() != 0) {
        cout << data.top().toString() << endl;
    }
}

/* numAdd
 *    Purpose: 
 *    Parameters: a string that constains only an integer
 *    Returns: none
 */
void RPNCalc::numAdd(string num) {
    int number = stoi(num);
    try {
        data.push(Datum(number));
    } catch (const std::invalid_argument& ia) {
       cerr << "Error: empty_stack\n";
    }
}

/* boolAdd
 *    Purpose: 
 *    Parameters: a string that indicates which bool to add
 *    Returns: none
 */
void RPNCalc::boolAdd(string set) {
    if(set == "#t") {
        data.push(Datum(true));
    } else if(set == "#f") {
        data.push(Datum(false));
    }

}

/* clear
 *    Purpose: 
 *    Parameters: none
 *    Returns: none
 */
void RPNCalc::clear() {
    data.clear();
}

/* notMod
 *    Purpose: 
 *    Parameters: none
 *    Returns: none
 */
void RPNCalc::notMod() {
    if(!data.top().isBool()) {
        cerr << "Error: datum_not_bool\n";
    }
    else if(data.top().getBool() == true) {
        try {
            data.pop();
        } catch (const std::runtime_error& e) {
            cerr << "Error: empty_stack\n";
        }
        boolAdd("#f");
    } else {
        try {
            data.pop();
        } catch (const std::runtime_error& e) {
            cerr << "Error: empty_stack\n";
        }
        boolAdd("#t");
    }
   
}

/* assess
 *    Purpose: 
 *    Parameters: a string that indicates which operation to perform
 *    Returns: none
 */
void RPNCalc::assess(string oper) {
    int firstDigit;
    int secDigit;
    int result = true;
    try {
        if(data.top().isInt()) {
            secDigit = data.top().getInt();
            try {
                data.pop();
            } catch (const std::runtime_error& e) {
                cerr << "Error: empty_stack\n";
            }
            if(data.top().isInt()) {
                firstDigit = data.top().getInt();
                try {
                    data.pop();
                } catch (const std::runtime_error& e) {
                    cerr << "Error: empty_stack\n";
                }
                if(oper == "+") {
                    result = firstDigit + secDigit;
                } else if(oper == "-") {
                    result = firstDigit - secDigit;
                } else if (oper == "*") {
                    result = firstDigit * secDigit;
                } else if(oper == "/") {
                    result = firstDigit / secDigit;
                } else if (oper == "mod") {
                    result = firstDigit % secDigit;
                }
                numAdd(to_string(result));
            } else {
                cerr << "Error: datum_not_int\n";
            }
        } else {
            cerr << "Error: datum_not_int\n";
        }
    } catch (const std::runtime_error& e) {
            cerr << "Error: empty_stack\n";
    }
}

/* compare
 *    Purpose: 
 *    Parameters: a string that indicates which comparison to perform
 *    Returns: none
 */
void RPNCalc::compare(string oper) {
    int firstDigit;
    int secDigit;
    bool result = true;
    if(oper == "==") {
        Datum firstDatum = data.top();
        try {
            data.pop();
        } catch (const std::runtime_error& e) {
            cerr << "Error: empty_stack\n";
        }
        Datum secondDatum = data.top();
        try {
            data.pop();
        } catch (const std::runtime_error& e) {
            cerr << "Error: empty_stack\n";
        }
        result = firstDatum == secondDatum;
        string resultStr;
        if(result) {
            resultStr = "#t";
        } else {
            resultStr = "#f";
        }
        boolAdd(resultStr);
    } else {
        try {
            if(data.top().isInt()) {
                secDigit = data.top().getInt();
                try {
                    data.pop();
                } catch (const std::runtime_error& e) {
                    cerr << "Error: empty_stack\n";
                }
                if(data.top().isInt()) {
                    firstDigit = data.top().getInt();
                    try {
                        data.pop();
                    } catch (const std::runtime_error& e) {
                        cerr << "Error: empty_stack\n";
                    }
                    if(oper == "<") {
                        result = firstDigit < secDigit;
                    } else if(oper == ">") {
                        result = firstDigit > secDigit;
                    } else if (oper == "<=") {
                        result = firstDigit <= secDigit;
                    } else if(oper == ">=") {
                        result = firstDigit / secDigit;
                    }
                    string resultStr;
                    if(result) {
                        resultStr = "#t";
                    } else {
                        resultStr = "#f";
                    }
                    boolAdd(resultStr);
                } else {
                    cerr << "Error: datum_not_int\n";
                }
            } else {
                cerr << "Error: datum_not_int\n";
            }
        } catch (const std::runtime_error& e) {
            cerr << "Error: empty_stack\n";
        }
    }
}

/* drop
 *    Purpose: 
 *    Parameters: none
 *    Returns: none
 */
void RPNCalc::drop() {
    try {
        data.pop();
    } catch (const std::runtime_error& e) {
        cerr << "Error: empty_stack\n";
    }
}

/* swap
 *    Purpose: 
 *    Parameters: none
 *    Returns: none
 */
void RPNCalc::swap() {
    Datum first = data.top();
    try {
        data.pop();
        Datum second = data.top();
        data.pop();
        data.push(first);
        data.push(second);
    } catch (const std::runtime_error& e) {
        cerr << "Error: empty_stack\n";
    }
}

/* drop
 *    Purpose: 
 *    Parameters: none
 *    Returns: none
 */
void RPNCalc::dup() {
    try {
        data.push(Datum(data.top()));
    } catch (const std::runtime_error& e) {
        cerr << "Error: empty_stack\n";
    }
}


Datum RPNCalc::rstring(istream &input) {
    string x = "";
    stringstream ss;
    ss << "{";
    while(!(x == "}")) {    
       if(x=="{") {
            ss << rstring(input).toString();
            ss << " ";
            input >> x;
       } else {
            ss << x;
            ss << " ";
            input >> x;
        }
    }
    ss << "}";
    x = ss.str();
    return Datum(x);
}

/* exec
 *    Purpose: run all the commands within the rstring 
 *    Parameters: none
 *    Returns: none
 */
void RPNCalc::exec() {
    try {
        if(data.top().isRString()) {
            string commands;
            commands = data.top().toString();
            try {
                data.pop();
            } catch (const std::runtime_error& e) {
                cerr << "Error: empty_stack\n";
            }
            commands = commands.substr(2, commands.length()-4);
            stringstream inBracket;
            inBracket << commands;
            doCommands(inBracket);
        } 
    } catch (const std::runtime_error& e) {
            cerr << "Error: empty_stack\n";
    }
}

/* file
 *    Purpose: open the file with the name of the last rstring
 *    and run it's contents
 *    Parameters: none
 *    Returns: none
 */
void RPNCalc::file() {
    try {
        if(data.top().isRString()) {
            string filename = data.top().toString();
            string line;
            try {
                data.pop();
            } catch (const std::runtime_error& e) {
                cerr << "Error: empty_stack\n";
            }
            filename = filename.substr(2, filename.length()-4);
            ifstream inputs(filename);
            if(inputs.is_open()) {
                doCommands(inputs);
                inputs.close();
            }
        }
    } catch (const std::runtime_error& e) {
        cerr << "Error: empty_stack\n";
    }
}

/* ifCheck
 *    Purpose: see if the stack has what it needs to run an if test
 *    and pop all the elements involved
 *    Parameters: none
 *    Returns: none
 */
void RPNCalc::ifCheck() {
    string falseCase;
    string trueCase;
    bool cond;
    try {
        if(data.top().isRString()) {
            falseCase = data.top().toString();
            try {
                data.pop();
            } catch (const std::runtime_error& e) {
                cerr << "Error: empty_stack\n";
            }
            if(data.top().isRString()) {
                trueCase = data.top().toString();
                try {
                    data.pop();
                } catch (const std::runtime_error& e) {
                    cerr << "Error: empty_stack\n";
                }
                if(data.top().isBool()) {
                    cond = data.top().getBool();
                    try {
                        data.pop();
                    } catch (const std::runtime_error& e) {
                        cerr << "Error: empty_stack\n";
                    }
                    ifEval(falseCase, trueCase, cond);
                } else {
                    cerr << "Error: expected boolean in if test\n";
                }
            } else {
                cerr << "Error: expected rstring in if branch\n";
            }
        } 
    } catch (const std::runtime_error& e) {
            cerr << "Error: empty_stack\n";
    }
}

/* ifEval
 *    Purpose: run the first rstring if the boolean is false, the second if not
 *    Parameters: two rstrings and a boolean
 *    Returns: none
 */
void RPNCalc::ifEval(string falseCase, string trueCase, bool test) {
    if(test) {
        data.push(Datum(trueCase));
        exec();
    } else {
        data.push(Datum(falseCase));
        exec();
    }
}

/* stackSize
 *    Purpose: determine how many elements are in the DatumStack
 *    Parameters: none
 *    Returns: an int equal to the number of Datum in the stack
 */
int RPNCalc::stackSize() {
    return data.size();
}