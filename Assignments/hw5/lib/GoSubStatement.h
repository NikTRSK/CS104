// GoSubStatement.h
#ifndef GOSUB_STATEMENT_INCLUDED
#define GOSUB_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"
#include <iostream>
#include <stdexcept>

class GoSubStatement: public Statement
{
private:
	int m_jumpTo;

public:
  GoSubStatement(int lineNum);
  virtual ~GoSubStatement();

	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif



