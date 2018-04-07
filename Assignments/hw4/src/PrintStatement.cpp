// PrintStatement.cpp
#include "PrintStatement.h"

PrintStatement::PrintStatement(std::string variableName)
	: m_variableName( variableName ) {}

PrintStatement::~PrintStatement() {}

void PrintStatement::execute(ProgramState * state, std::ostream &outf) {
  std::cout << state->getVar(m_variableName) << std::endl;

  state->updateCounter(1);
}


