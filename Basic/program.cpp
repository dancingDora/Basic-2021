/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
#include <map>

using namespace std;

Program::Program() {

}

Program::~Program() {
    // Replace this stub with your own code
}

void Program::clear() {
    mp.clear();
}

void Program::addSourceLine(int lineNumber, string line) {
        mp[lineNumber] = line;
}

void Program::removeSourceLine(int lineNumber) {
    mp.erase(lineNumber);
}

string Program::getSourceLine(int lineNumber) {
   return mp[lineNumber];
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    mp1[lineNumber]=stmt;
}

Statement *Program::getParsedStatement(int lineNumber) {
    return NULL;  // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
    if(mp.empty())return -1;
    auto it=mp.begin();
    int i=it->first;
    return i;
}

int Program::getNextLineNumber(int lineNumber) {
    auto it=mp.upper_bound(lineNumber);
    if(it==mp.end())return -1;
    return it->first;
}
