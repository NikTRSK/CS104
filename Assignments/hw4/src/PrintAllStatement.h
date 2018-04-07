// PrintStatement.h
#ifndef PRINTALL_STATEMENT_INCLUDED
#define PRINTALL_STATEMENT_INCLUDED

#include "Statement.h"
#include <iostream>
#include <map>
#include <string>

class PrintAllStatement: public Statement
{
private:
	std::string m_variableName;
	
public:
	PrintAllStatement();
  virtual ~PrintAllStatement();
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif

