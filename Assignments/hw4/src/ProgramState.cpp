#include "ProgramState.h"

ProgramState::ProgramState(int numLines) {
	m_numLines = numLines;
  currentLine = 0; // initializes the first line.
}

void ProgramState::updateCounter(int skipLines) {
  currentLine += skipLines;
}

void ProgramState::setCounter(int lineNum) {
  currentLine = lineNum;;
}

int ProgramState::getCounter() {
  return currentLine;
}

void ProgramState::updateCounterToEnd() {
  currentLine = m_numLines;
}

int ProgramState::getEnd() {
  return m_numLines;
}

void ProgramState::updateVar(std::string varName, int val) {
  std::map<std::string, int>::iterator it;
  // find and update the key. If it doesn't exist create it.
  it = variables.find(varName);
  if (it != variables.end())
    it->second = val;
  else
    variables.insert(std::make_pair(varName, val));
}

int ProgramState::getVar(std::string varName) {
  std::map<std::string, int>::iterator it;
  
  it = variables.find(varName);
  if (it != variables.end())
    return it->second;
  else
    return 0;
}

std::map<std::string, int> & ProgramState::getAllVars() {
  return variables;
}

void ProgramState::callSubroutine(int jumpTo) {
  subroutine.push(jumpTo);
}

int ProgramState::returnFromSubroutine() {
  int returnLine = -1;
  if (!subroutine.empty()) { 
    returnLine = subroutine.top() + 1;
    subroutine.pop();
  }

  return returnLine;
}