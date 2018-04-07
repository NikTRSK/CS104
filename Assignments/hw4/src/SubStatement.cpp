// SubStatement.cpp:
#include "SubStatement.h"
#include <iostream>
using namespace std;

SubStatement::SubStatement(std::string variableName, std::string var2)
  : m_variableName( variableName ), m_var2( var2 ) {}

SubStatement::~SubStatement() {}

void SubStatement::execute(ProgramState * state, ostream &outf)
{
  // check whether vars exist
  int toSub;

  // check whether a VAR or a VAL has been passed in
  if ( !m_var2.find_first_not_of("0123456789") )
    toSub = state->getVar(m_var2);
  else
    toSub = atoi(m_var2.c_str());

  state->updateVar(m_variableName, state->getVar(m_variableName) - toSub);
	state->updateCounter(1);
}