/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "../StanfordCPPLib/simpio.h"

using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
    /* Empty */
}

Statement::~Statement() {
    /* Empty */
}

REM::REM() {};

void REM::execute(EvalState &state) {

};

GOTO::GOTO(TokenScanner &scanner) {
    string tmp;
    tmp = scanner.nextToken();
    num = stoi(tmp);
};

void GOTO::execute(EvalState &state) {
    state.lineNum = num;
}

LET::LET(TokenScanner &scanner) {
    name = scanner.nextToken();
    scanner.nextToken();
    exp = parseExp(scanner);
    if (name == "LET")cout << "SYNTAX ERROR" << endl;
}

void LET::execute(EvalState &state) {
    state.setValue(name, exp->eval(state));
};

INPUT::INPUT(TokenScanner &scanner) {
    name = scanner.nextToken();
};

void INPUT::execute(EvalState &state) {
    cout << " ? ";
    string tmp1;
    int tmp;
    tmp1 = getLine();
    if (((tmp1[0] < '0' || tmp1[0] > '9') && tmp1[0] != '-') ||
        (tmp1.length() > 1 && (tmp1[1] < '0' || tmp1[1] > '9'))) {
        cout << "INVALID NUMBER" << endl;
        execute(state);
    } else {
        tmp = stoi(tmp1);
        state.setValue(name, tmp);
    }
};

END::END() {};

void END::execute(EvalState &state) {
    state.lineNum = -1;
};

IF::IF(TokenScanner &scanner) {
    exp_l = readE(scanner);
    cmp = scanner.nextToken();
    exp_r = readE(scanner);
    scanner.nextToken();
    string tmp;
    tmp = scanner.nextToken();
    n = stoi(tmp);
};

void IF::execute(EvalState &state) {
    int int_l = exp_l->eval(state);
    int int_r = exp_r->eval(state);
    bool flag = 0;
    if (cmp == ">") {
        if (int_l > int_r)flag = 1;
    }
    if (cmp == "<") {
        if (int_l < int_r)flag = 1;
    }
    if (cmp == "=") {
        if (int_l == int_r)flag = 1;
    }
    if (flag == 1) state.lineNum = n;
};

PRINT::PRINT(TokenScanner &scanner) {
    exp = parseExp(scanner);
}

void PRINT::execute(EvalState &state) {
    cout << exp->eval(state) << endl;
};

