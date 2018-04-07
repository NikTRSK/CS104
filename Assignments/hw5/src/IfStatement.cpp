// IfStatement.cpp:
#include "IfStatement.h"
#include <iostream>
using namespace std;

IfStatement::IfStatement(std::string var, std::string op, int val, int lineNum)
  : m_var( var ), m_op( op ), m_val( val ), m_jumpTo( lineNum ) {}

IfStatement::~IfStatement() {}

void IfStatement::execute(ProgramState * state, ostream &outf) {
  outf << ""; // only used to get rid of the unused variable warning (suggested by Cote & a CP).
  
  int val1 = state->getVar(m_var);
  int val2 = m_val;
  bool compRes = false;
  
  // relational comparisson  
  if (m_op == "<")
      compRes = val1 < val2;
  if (m_op == "<=")
      compRes = val1 <= val2;
  if (m_op == ">")
      compRes = val1 > val2;
  if (m_op == ">=")
      compRes = val1 >= val2;
  if (m_op == "=")
      compRes = val1 == val2;
  if (m_op == "<>")
      compRes = val1 != val2;

  if (compRes) {
    if (m_jumpTo > state->getEnd() || m_jumpTo <= 0) {
      throw "Illegal jump instruction";
      return;
    }
    state->setCounter(m_jumpTo);
  }
  else
    state->updateCounter(1);
}