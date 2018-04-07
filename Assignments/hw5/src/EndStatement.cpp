// LetStatement.cpp:
#include "EndStatement.h"
using namespace std;

EndStatement::EndStatement() {}

EndStatement::~EndStatement() {}

void EndStatement::execute(ProgramState * state, ostream &outf) {
	outf << ""; // only used to get rid of the unused variable warning (suggested by Cote & a CP).
  state->updateCounterToEnd();
}