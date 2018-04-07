// DivStatement.cpp:
#include "DivStatement.h"
#include <sstream>

using namespace std;

DivStatement::DivStatement(std::string variableName, std::string var2)
  : m_variableName( variableName ), m_var2( var2 ) {}

DivStatement::~DivStatement() {}

void DivStatement::execute(ProgramState * state, ostream &outf) {
  outf << ""; // only used to get rid of the unused variable warning (suggested by Cote & a CP).
  // check whether vars exist
  int toDiv;

  // check whether a VAR or a VAL has been passed in
  if (isupper(m_var2[0]))
    toDiv = state->getVar(m_var2);
  else {
    std::stringstream ss;
    ss << m_var2;
    ss >> toDiv;
  }

  if (toDiv == 0)
    throw "Divide by zero exception";

  state->updateVar(m_variableName, state->getVar(m_variableName) / toDiv);
	state->updateCounter(1);
}