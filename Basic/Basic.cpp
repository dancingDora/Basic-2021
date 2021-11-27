/*
 * File: Basic.cpp
 * ---------------
 * This file is the starter project for the BASIC interpreter.
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"

using namespace std;


/* Function prototypes */

void processLine(string line, Program &program, EvalState &state);

/* Main program */

int main() {
    EvalState state;
    Program program;
    while (true) {
        try {
            string input = getLine();
            if (input.empty())
                continue;
            processLine(input, program, state);
        } catch (ErrorException &ex) {
            cout  << ex.getMessage() << endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version of
 * implementation, the program reads a line, parses it as an expression,
 * and then prints the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program &program, EvalState &state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    string tmp;
    tmp = scanner.nextToken();
    if (tmp[0] >= '0' && tmp[0] <= '9') {
        int lineNumber = stoi(tmp);
        Statement *stmt;
        string tmp1 = scanner.nextToken();
        if (tmp1 == "REM") {
            stmt = new REM();
        };
        if (tmp1 == "PRINT") {
            stmt = new PRINT(scanner);
        };
        if (tmp1 == "GOTO") {
            stmt = new GOTO(scanner);
        };
        if (tmp1 == "INPUT") {
            stmt = new INPUT(scanner);
        };
        if (tmp1 == "LET") {
            stmt = new LET(scanner);
        };
        if (tmp1 == "IF") {
            stmt = new IF(scanner);
        };
        if (tmp1 == "END") {
            stmt = new END();
        };
        if(tmp1==""){
            program.removeSourceLine(lineNumber);
            return;
        }
        program.setParsedStatement(lineNumber, stmt);
        program.addSourceLine(lineNumber, line);
    };
    if (tmp == "LET") {
        Statement *stmt = new LET(scanner);
        stmt->execute(state);
    };
    if (tmp == "PRINT") {
        Statement *stmt = new PRINT(scanner);
        stmt->execute(state);
    };
    if (tmp == "INPUT") {
        Statement *stmt = new INPUT(scanner);
        stmt->execute(state);
    };
    if (tmp == "RUN") {
        for (state.lineNum = program.getFirstLineNumber(); state.lineNum != -1;) {
            Statement *stmt = program.getParsedStatement(state.lineNum);
            state.lineNum = program.getNextLineNumber(state.lineNum);
            stmt->execute(state);
            if(state.lineNum!=-1&&!program.count(state.lineNum)){
                cout<<"LINE NUMBER ERROR"<<endl;
                state.lineNum=-1;
            }
        }
    };
    if (tmp == "LIST") {
        for (int num = program.getFirstLineNumber(); num != -1; num = program.getNextLineNumber(num)) {
            cout << program.getSourceLine(num) << endl;
        }
    };
    if (tmp == "CLEAR") {
        program.clear();
        state.clear();
    };
    if (tmp == "QUIT") exit(0);
}

