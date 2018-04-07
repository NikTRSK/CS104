// MultStatement.h
#ifndef MULT_STATEMENT_INCLUDED
#define MULT_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"
#include <stdlib.h>     /* atoi */
#include <iostream>

class MultStatement: public Statement
{
private:
	std::string m_variableName;
  std::string m_var2;

public:
  MultStatement(std::string variableName, std::string var2);
  virtual ~MultStatement();

	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif



