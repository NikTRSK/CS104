// MultStatement.cpp:
#include "MultStatement.h"
using namespace std;

MultStatement::MultStatement(std::string variableName, std::string var2)
  : m_variableName( variableName ), m_var2( var2 ) {}

MultStatement::~MultStatement() {}

void MultStatement::execute(ProgramState * state, ostream &outf) {
  int toMult;

  // check whether a VAR or a VAL has been passed in
  if ( !m_var2.find_first_not_of("0123456789") )
    toMult = state->getVar(m_var2);
  else
    toMult = atoi(m_var2.c_str());

  state->updateVar(m_variableName, state->getVar(m_variableName) * toMult);
	state->updateCounter(1);
}