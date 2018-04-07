#include "facile.h"

facile::facile(std::ifstream &inputFile) {
  interpretProgram(inputFile);
}

facile::~facile() {
  for (unsigned int i = 0; i < program.size(); i++)
    delete program[i];
  delete state;
}

void facile::parseProgram(std::istream &inf, std::vector<Statement *> & program)
{
  program.push_back(NULL);
  
  std::string line;
  while(!inf.eof()) {
    getline(inf, line);
    program.push_back( parseLine(line) );
  }
}

Statement * facile::parseLine(std::string line) {
  std::stringstream ss;
  std::string type;
  std::string var;
  int val;

  ss << line;
  ss >> type;
  
  if ( type == "LET" ) {
    ss >> var;
    ss >> val;
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
    std::string var2;
    ss >> var2;
    statement = new AddStatement(var, var2);
  }
  else if ( type == "SUB" ) {
    ss >> var;
    std::string var2;
    ss >> var2;
    statement = new SubStatement(var, var2);
  }
  else if ( type == "MULT" ) {
    ss >> var;
    std::string var2;
    ss >> var2;
    statement = new MultStatement(var, var2);
  }
  else if ( type == "DIV" ) {
    ss >> var;
    std::string var2;
    ss >> var2;
    statement = new DivStatement(var, var2);
  }
  else if ( type == "GOTO" ) {
    ss >> val;
    statement = new GotoStatement(val);
  }
  else if ( type == "IF" ) {
    ss >> var;
    std::string op; ss >> op;
    ss >> val;
    std::string then; ss >> then;
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


void facile::interpretProgram(std::istream& inf) {
  parseProgram(inf, program); // stores all the commands passed in.
  state = new ProgramState(program.size() - 1);
}

void facile::executeInstruction(int instructionNumber) {
  // takes into account for the program starting at line 1
  if (instructionNumber < state->getEnd() || instructionNumber > 0) {
    program[instructionNumber]->execute(state, std::cout);
  }
  else
    return;
}

int facile::currentInstruction() {
  return state->getCounter();
}

std::map<std::string, int> & facile::getAllVars() {
  return state->getAllVars();
}

bool facile::inSubroutine() {
  return state->stackEmpty();
}

void facile::initFacile() {
  state->setCounter(1);

// empty the call stack. In case the program terminates before the stack is emptied
  while (!state->stackEmpty())
    state->returnFromSubroutine();
}