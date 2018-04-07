// SubStatement.h
#ifndef SUB_STATEMENT_INCLUDED
#define SUB_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"
#include <stdlib.h>     /* atoi */

class SubStatement: public Statement
{
private:
	std::string m_variableName;
  std::string m_var2;

public:
  SubStatement(std::string variableName, std::string var2);
  virtual ~SubStatement();

	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif



