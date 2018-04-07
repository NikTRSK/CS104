// GoSubStatement.cpp:
#include "GoSubStatement.h"
using namespace std;

GoSubStatement::GoSubStatement(int lineNum)
  :m_jumpTo( lineNum ) {}

GoSubStatement::~GoSubStatement() {}

void GoSubStatement::execute(ProgramState * state, ostream &outf) {
  if (m_jumpTo > state->getEnd() || m_jumpTo <= 0) {
    throw "Illegal jump instruction";
    return;
  }
  else {
    state->callSubroutine(state->getCounter());
    state->setCounter(m_jumpTo);
  }
}