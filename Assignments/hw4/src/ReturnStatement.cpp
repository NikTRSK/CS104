// ReturnStatement.cpp:
#include "ReturnStatement.h"
using namespace std;

ReturnStatement::ReturnStatement() {}

ReturnStatement::~ReturnStatement() {}

// The ReturnStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void ReturnStatement::execute(ProgramState * state, ostream &outf) {
  int endSubroutine = state->returnFromSubroutine();
  if (endSubroutine == -1)
    state->updateCounterToEnd();
  else
    state->setCounter(endSubroutine + 1);
}