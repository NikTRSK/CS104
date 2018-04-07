// PrintStatement.cpp
#include "PrintAllStatement.h"

PrintAllStatement::PrintAllStatement() {}

PrintAllStatement::~PrintAllStatement() {}

void PrintAllStatement::execute(ProgramState * state, std::ostream &outf) {
  std::map<std::string, int>* variables = &state->getAllVars();
  std::map<std::string, int>::iterator it;
  // find and update the key. If it doesn't exist throw an exception.
  for (it = variables->begin(); it != variables->end(); it++)
    std::cout << it->first << " " << it->second << std::endl;

  state->updateCounter(1);
}


