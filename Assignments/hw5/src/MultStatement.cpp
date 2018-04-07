// MultStatement.cpp:
#include "MultStatement.h"
#include <sstream>
#include <iostream>
using namespace std;

MultStatement::MultStatement(std::string variableName, std::string var2)
  : m_variableName( variableName ), m_var2( var2 ) {}

MultStatement::~MultStatement() {}

void MultStatement::execute(ProgramState * state, ostream &outf) {
  outf << ""; // only used to get rid of the unused variable warning (suggested by Cote & a CP).

  int toMult;

  // check whether a VAR or a VAL has been passed in
  if (isupper(m_var2[0]))
    toMult = state->getVar(m_var2);
  else {
    std::stringstream ss;
    ss << m_var2;
    ss >> toMult;
  }

  state->updateVar(m_variableName, state->getVar(m_variableName) * toMult);
	state->updateCounter(1);
}