// GotoStatement.cpp:
#include "GotoStatement.h"
using namespace std;

GotoStatement::GotoStatement(int val)
  : m_jumpTo( val ) {}

GotoStatement::~GotoStatement() {}

void GotoStatement::execute(ProgramState * state, ostream &outf) {
  outf << ""; // only used to get rid of the unused variable warning (suggested by Cote & a CP).
  // check for bad jumps
  if (m_jumpTo > state->getEnd() || m_jumpTo <= 0) {
    throw "Illegal jump instruction";
    return;
  }
  else
    state->setCounter(m_jumpTo);
}