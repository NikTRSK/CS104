// ProgramState.h
//
// CS 104 / Spring 2016
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a Facile program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * A map, as explained by the problem writeup.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED

#include "stackint.h"
#include <map>
#include <string>
#include <vector>

class ProgramState
{
public:
	ProgramState(int numLines);

  // updates the value of the program counter by the specified lines
  void updateCounter(int skipLines);
  // set the counter to thhe specified line
  void setCounter(int lineNum);
  // returns the current value of the counter
  int getCounter();
  // set counter to end
  void updateCounterToEnd();
  // get the size of the program
  int getEnd();
  // updates the value of a variable. If the value doesn't exist it cretes it
  void updateVar(std::string varName, int val);
  // gets the value of a variable by string name. If var doesn't exist returns 0
  int getVar(std::string varName);
  // returns a map of all variables
  std::map<std::string, int> & getAllVars();

  // Subroutine handlers
  void callSubroutine(int jumpTo);
  // returns -1 if stack is empty. if not it returns the last item.
  int returnFromSubroutine();

  // HELPER FUNCTION: returns true if the subroutine stack is empty
  bool stackEmpty();


private:
	int m_numLines; // total size
  int currentLine; // the current line that is being executed. Counter variable
  std::map<std::string, int> variables; // stores the variables and the data for each
  StackInt subroutine; // holds the return statements and the stack values

};

#endif



