###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Sam Lacet-Brown



##
## Put your variables and rules here.  You can use previous Makefiles
## as examples, and you can refer to the "make" documentation on the
## course Reference page.
##  --- Delete this comment and put appropriate comments in ---
CXX      = clang++
CXXFLAGS = -g3  -std=c++11 -Wall -Wextra  -Wpedantic -Wshadow
LDFLAGS  = -g3


INCLUDES = $(shell echo *.h)
EXECS    = CalcYouLater

# Students will need to add other .o files 
CalcYouLater: main.o DatumStack.o RPNCalc.o Datum.o
	${CXX} ${LDFLAGS} $^ -o $@

testDatumStack: testDatumStack.o DatumStack.o RPNCalc.o Datum.o
	${CXX} ${LDFLAGS} $^ -o $@

%.o: %.cpp ${INCLUDES}
	${CXX} ${CXXFLAGS} -c -o $@ $<

.PHONY: clean
clean:
	rm -f ${EXECS} *.o *.dSYM./

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
