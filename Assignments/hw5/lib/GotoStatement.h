// GotoStatement.h
#ifndef GOTO_STATEMENT_INCLUDED
#define GOTO_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"
#include <iostream>
#include <stdexcept>

class GotoStatement: public Statement
{
private:
	int m_jumpTo;

public:
  GotoStatement(int val);
  virtual ~GotoStatement();

	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif



