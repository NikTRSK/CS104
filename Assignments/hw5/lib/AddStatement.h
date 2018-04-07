// AddStatement.h
#ifndef ADD_STATEMENT_INCLUDED
#define ADD_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"
#include <stdlib.h>     /* atoi */
#include <iostream>

class AddStatement: public Statement
{
private:
	std::string m_variableName;
  std::string m_var2;

public:
  AddStatement(std::string variableName, std::string var2);
  virtual ~AddStatement();

	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif



