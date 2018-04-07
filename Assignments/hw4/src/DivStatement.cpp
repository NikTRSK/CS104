// DivStatement.cpp:
#include "DivStatement.h"

using namespace std;

DivStatement::DivStatement(std::string variableName, std::string var2)
  : m_variableName( variableName ), m_var2( var2 ) {}

DivStatement::~DivStatement() {}

void DivStatement::execute(ProgramState * state, ostream &outf) {
  // check whether vars exist
  int toDiv;

  // check whether a VAR or a VAL has been passed in
  if ( !m_var2.find_first_not_of("0123456789") )
    toDiv = state->getVar(m_var2);
  else
    toDiv = atoi(m_var2.c_str());

  if (toDiv == 0)
    throw "Divide by zero exception";

  state->updateVar(m_variableName, state->getVar(m_variableName) / toDiv);
	state->updateCounter(1);
}