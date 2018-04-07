// LetStatement.cpp:
#include "LetStatement.h"
#include <iostream>
using namespace std;

LetStatement::LetStatement(std::string variableName, int value)
	: m_variableName( variableName ), m_value( value ) {}

LetStatement::~LetStatement() {}

void LetStatement::execute(ProgramState * state, ostream &outf) {
  state->updateVar(m_variableName, m_value);
	state->updateCounter(1);
}