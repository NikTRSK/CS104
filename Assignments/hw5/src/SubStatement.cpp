// SubStatement.cpp:
#include "SubStatement.h"
#include <iostream>
#include <sstream>
using namespace std;

SubStatement::SubStatement(std::string variableName, std::string var2)
  : m_variableName( variableName ), m_var2( var2 ) {}

SubStatement::~SubStatement() {}

void SubStatement::execute(ProgramState * state, ostream &outf) {
  outf << ""; // only used to get rid of the unused variable warning (suggested by Cote & a CP).
  // check whether vars exist
  int toSub;

  // check whether a VAR or a VAL has been passed in
  if (isupper(m_var2[0]))
    toSub = state->getVar(m_var2);
  else {
    std::stringstream ss;
    ss << m_var2;
    ss >> toSub;
  }

  state->updateVar(m_variableName, state->getVar(m_variableName) - toSub);
	state->updateCounter(1);
}