// IfStatement.h
#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"
#include <map>
#include <stdexcept>

class IfStatement: public Statement
{
private:
  std::string m_var;
  std::string m_op;
	int m_val;
  int m_jumpTo;

public:
  IfStatement(std::string var, std::string op, int val, int lineNum);
  virtual ~IfStatement();

	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif



