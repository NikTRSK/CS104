// GotoStatement.cpp:
#include "GotoStatement.h"
using namespace std;

GotoStatement::GotoStatement(int val)
  : m_jumpTo( val ) {}

GotoStatement::~GotoStatement() {}

void GotoStatement::execute(ProgramState * state, ostream &outf) {
  // check for bad jumps
  if (m_jumpTo > state->getEnd() || m_jumpTo <= 0) {
    throw "Illegal jump instruction";
    return;
  }
  else
    state->setCounter(m_jumpTo);
}