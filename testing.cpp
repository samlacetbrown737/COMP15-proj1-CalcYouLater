/* 
 * testing.cpp
 * 
 * Comp 15 Proj 1
 * Sam Lacet-Brown
 * Oct 2020
 *
 * Holds all the testing functions that rely  on functions  which
 * are now private
 *
 */

/* addTests
 *    Purpose: Tests adding datum to the stack and manipulating them
 *    Parameters: none
 *    Returns: none
 */
void addTests() {
    RPNCalc *calc = new RPNCalc();
    calc->numAdd("3");
    calc->print();
    calc->boolAdd("#t");
    calc->print();
    calc->notMod();
    calc->print();
    cout << "size" << calc->stackSize() << endl;
    calc->drop();
    calc->print();
    calc->clear();
    calc->print();
    cout << "size" << calc->stackSize() << endl;
    calc->numAdd("7");
    calc->numAdd("3");
    calc->print();
    calc->swap();
    calc->print();
    calc->dup();
    calc->drop();
    calc->print();
    delete calc;
}

/* parserTests
 *    Purpose: Tests pushing rstrings
 *    Parameters: none
 *    Returns: none
 */
void parserTest() {
    RPNCalc *calc = new RPNCalc();
    cout << "Testing parser" << endl;
    cout << "Enter an RString ending in }" << endl;
    cout << "{ ";
    calc->rstring(cin);
    calc->print();
    delete calc;
}

/* opTests
 *    Purpose: Tests all the operators (+, -, *, /, mod)
 *    Parameters: none
 *    Returns: none
 */
void opTests() {
    RPNCalc *calc = new RPNCalc();
    calc->numAdd("3");
    calc->numAdd("4");
    calc->print();
    calc->assess("+");
    calc->print();
    calc->numAdd("5");
    calc->assess("-");
    calc->print();
    calc->numAdd("3");
    calc->assess("*");
    calc->print();
    calc->numAdd("2");
    calc->assess("/");
    calc->print();
    calc->numAdd("2");
    calc->assess("mod");
    calc->print();
    delete calc;
}

/* compTests
 *    Purpose: Tests all the comparison functions
 *    Parameters: none
 *    Returns: none
 */
void compTests() {
    RPNCalc *calc = new RPNCalc();
    calc->numAdd("1");
    calc->numAdd("6");
    calc->compare("<");
    calc->print();
    calc->numAdd("2");
    calc->numAdd("2");
    calc->compare("==");
    calc->print();
    calc->numAdd("4");
    calc->numAdd("3");
    calc->compare("<");
    calc->print();
    calc->boolAdd("#f");
    calc->compare("==");
    calc->print();
    delete calc;
}