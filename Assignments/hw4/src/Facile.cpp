// Facile.cpp
#include "LetStatement.h"
#include "EndStatement.h"
#include "PrintStatement.h"
#include "PrintAllStatement.h"
#include "AddStatement.h"
#include "SubStatement.h"
#include "MultStatement.h"
#include "DivStatement.h"
#include "GotoStatement.h"
#include "IfStatement.h"
#include "GoSubStatement.h"
#include "ReturnStatement.h"
#include "ProgramState.h"
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);

int main()
{
  cout << "Enter Facile program file name: ";
  string filename;
  getline(cin, filename);
  ifstream infile(filename.c_str());
  if (!infile)
  {
    cout << "Cannot open " << filename << "!" << endl;
    return 1;
  }
  interpretProgram(infile, cout);
}

void parseProgram(istream &inf, vector<Statement *> & program)
{
	program.push_back(NULL);
	
	string line;
	while( ! inf.eof() )
	{
		getline(inf, line);
		program.push_back( parseLine( line ) );
	}
}

Statement * parseLine(string line)
{
	Statement * statement;	
	stringstream ss;
	string type;
	string var;
	int val;

	ss << line;
	ss >> type;
	
	if ( type == "LET" ) {
		ss >> var;
		ss >> val;
		// Note:  Because the project spec states that we can assume the file
		//	  contains a syntactically legal Facile program, we know that
		//	  any line that begins with "LET" will be followed by a space
		//	  and then a variable and then an integer value.
		statement = new LetStatement(var, val);
	}
  else if ( type == "PRINT" ) {
    ss >> var;
    statement = new PrintStatement(var);
  }
  else if ( type == "PRINTALL" )
    statement = new PrintAllStatement();
  else if ( type == "ADD" ) {
    ss >> var;
    string var2;
    ss >> var2;
    statement = new AddStatement(var, var2);
  }
  else if ( type == "SUB" ) {
    ss >> var;
    string var2;
    ss >> var2;
    statement = new SubStatement(var, var2);
  }
  else if ( type == "MULT" ) {
    ss >> var;
    string var2;
    ss >> var2;
    statement = new MultStatement(var, var2);
  }
  else if ( type == "DIV" ) {
    ss >> var;
    string var2;
    ss >> var2;
    statement = new DivStatement(var, var2);
  }
  else if ( type == "GOTO" ) {
    ss >> val;
    statement = new GotoStatement(val);
  }
  else if ( type == "IF" ) {
    ss >> var;
    string op; ss >> op;
    ss >> val;
    string then; ss >> then;
    int lineNum; ss >> lineNum;
    statement = new IfStatement(var, op, val, lineNum);
  }
  else if ( type == "GOSUB" ) {
    ss >> val;
    statement = new GoSubStatement(val);
  }
  else if ( type == "RETURN" )
    statement = new ReturnStatement();
  else if ( type == "END" || type == "." )
    statement = new EndStatement();
	
	return statement;
}


void interpretProgram(istream& inf, ostream& outf)
{
	vector<Statement *> program; // holds all the statements
	parseProgram( inf, program ); // stores all the commands passed in.
  ProgramState * state = new ProgramState(program.size() - 1);
	
  int i = 1;
  while (i != state->getEnd()) {
    try {
      (program[i])->execute(state, cout);
      i = state->getCounter();
    }
    catch (const char* msg) {
      cerr << msg << endl;
      // deallocate memory before terminating eraly
      for (unsigned int i = 0; i < program.size(); i++)
        delete program[i];
      delete state;
      return;
    }
  }

  for (unsigned int i = 0; i < program.size(); i++)
    delete program[i];
  delete state;
}