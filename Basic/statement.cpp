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

}

LET::LET(TokenScanner &scanner) {
    name = scanner.nextToken();
    scanner.nextToken();
    exp = parseExp(scanner);
}

void LET::execute(EvalState &state) {};

INPUT::INPUT(TokenScanner &scanner) {
    name = scanner.nextToken();
};

void INPUT::execute(EvalState &state) {};

END::END() {};

void END::execute(EvalState &state) {};

IF::IF(TokenScanner &scanner) {
    exp_l = readE(scanner);
    cmp = scanner.nextToken();
    exp_r = readE(scanner);
    scanner.nextToken();
    string tmp;
    tmp = scanner.nextToken();
    n = stoi(tmp);
};

void IF::execute(EvalState &state) {};

PRINT::PRINT(TokenScanner &scanner) {
    exp = parseExp(scanner);
}

void PRINT::execute(EvalState &state) {};

