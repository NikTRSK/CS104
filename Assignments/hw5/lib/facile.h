#ifndef FACILE_H
#define FACILE_H

#include "LetStatement.h"
#include "EndStatement.h"
#include "PrintStatement.h"
#include "PrintAllStatement.h"
#include "AddStatement.h"
#include "SubStatement.h"
#include "MultStatement.h"
#include "DivStatement.h"
#include "GotoStatement.h"
#include "IfStatement.h"
#include "GoSubStatement.h"
#include "ReturnStatement.h"
#include "ProgramState.h"
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <utility>

class facile {
  public:
    facile(std::ifstream &inputFile);
    ~facile();
    void parseProgram(std::istream& inf, std::vector<Statement *> & program);
    Statement * parseLine(std::string line);
    void interpretProgram(std::istream& inf);
    void executeInstruction(int instructionNumber);
    int currentInstruction();
    std::map<std::string, int> & getAllVars();
    bool inSubroutine();
    // initializes facile to the beginning of execution (line 1)
    void initFacile();

  private:
    std::vector<Statement *> program;
    ProgramState * state;
    Statement * statement;

    std::vector<int> breakpoints;
};

#endif