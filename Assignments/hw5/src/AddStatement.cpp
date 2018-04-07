// AddStatement.cpp:
#include "AddStatement.h"
#include <sstream>
#include <ctype.h>
using namespace std;

AddStatement::AddStatement(std::string variableName, std::string var2)
  : m_variableName( variableName ), m_var2( var2 ) {}

AddStatement::~AddStatement() {}

void AddStatement::execute(ProgramState * state, ostream &outf) {
  outf << ""; // only used to get rid of the unused variable warning (suggested by Cote & a CP).
  // check whether vars exist
  int toAdd;

  // check whether a VAR or a VAL has been passed in
  if (isupper(m_var2[0]))
    toAdd = state->getVar(m_var2);
  else {
    std::stringstream ss;
    ss << m_var2;
    ss >> toAdd;
  }

  state->updateVar(m_variableName, state->getVar(m_variableName) + toAdd);
	state->updateCounter(1);
}