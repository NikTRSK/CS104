// DivStatement.h
#ifndef DIV_STATEMENT_INCLUDED
#define DIV_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"
#include <stdlib.h>     /* atoi */
#include <iostream>
#include <stdexcept>

class DivStatement: public Statement
{
private:
	std::string m_variableName;
  std::string m_var2;

public:
  DivStatement(std::string variableName, std::string var2);
  virtual ~DivStatement();

	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif



