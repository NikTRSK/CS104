// AddStatement.cpp:
#include "AddStatement.h"
using namespace std;

AddStatement::AddStatement(std::string variableName, std::string var2)
  : m_variableName( variableName ), m_var2( var2 ) {}

AddStatement::~AddStatement() {}

void AddStatement::execute(ProgramState * state, ostream &outf) {
  // check whether vars exist
  int toAdd;

  // check whether a VAR or a VAL has been passed in
  if ( !m_var2.find_first_not_of("0123456789") )
    toAdd = state->getVar(m_var2);
  else
    toAdd = atoi(m_var2.c_str());

  state->updateVar(m_variableName, state->getVar(m_variableName) + toAdd);
	state->updateCounter(1);
}