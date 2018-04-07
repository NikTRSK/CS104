#include "stackint.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>	/*atoi*/

using namespace std;

void parseLine(string&, StackInt&, const char *, const int);
// returns true if char found in array list, false otherwise
bool checkValid(const char, const char *, const int);

	// define types. I know global = BAD!!! But makes the program more readable. And
	// Aaron Cheney said it was ok on Piazza
	const int OPEN_PAREN = -1;
	const int CLOSED_PAREN = -2;
	const int PLUS = -11;
	const int MULTIPLY = -12;
	const int SFT_LEFT = -21;
	const int SFT_RIGHT = -22;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Missing input file.\n./h3p5_arith input_file.txt\n";
		return -1;
	}

	ifstream input(argv[1]);	// load up the file with the commands
	
	// create the stack
	StackInt* parser = new StackInt;
	// define string for input
	string equation;

	// define characters for checking valid input
	const int n = 17;
	const char validChars [n] = {'(', ')', '+', '*', '<', '>', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' '};

	while (getline(input, equation)) {
		parseLine(equation, *parser, validChars, n);
		while(!parser->empty()) {
			cout << parser->top() << endl;
			parser->pop();
		}
	}

	input.close();
	delete parser;

	return 0;
}

// if the expression is valid the stack is left with one item (result)
void parseLine(string& line, StackInt& stack, const char * array, const int n) {
	int val1 = -999;
	int val2 = -999;
	int operation = -1000;
	int openParen = 0, closedParen = 0;

	// if we pass in an empty line, just skip
	if (line.length() == 1)
		return;

	for(unsigned int i = 0; i < line.length() - 1; i++) {

		// check for invalid characters
		if (!checkValid(line[i], array, n)) {
			cerr << "Malformed" << endl;
			while(!stack.empty())
				stack.pop();
			return;
		}

	if (line[i] == '+' || line[i] == '*' || line[i] == '<' || line[i] == '>'
				|| line[i] == '(' || line[i] == ' ') {
			if (line[i] == '+')
				stack.push(PLUS);
			else if (line[i] == '*')
				stack.push(MULTIPLY);
			else if (line[i] == '<')
				stack.push(SFT_LEFT);
			else if (line[i] == '>')
				stack.push(SFT_RIGHT);
			else if (line[i] == '(') {
				stack.push(OPEN_PAREN);
				openParen++;
			}
		}
		else if (isdigit(line[i])) {
			// check for 2 consecutive numbers without an operator in between (with parenthesis)
			if (!stack.empty() && stack.top() >= 0) {
				cerr << "Malformed" << endl;
				while(!stack.empty())
					stack.pop();
				return;
			}
			int digCnt = i;
			while(isdigit(line[digCnt]))
				digCnt++;
			stringstream ss;
			ss << line.substr(i, digCnt-i);
			int n;
			ss >> n;
			stack.push(n);
			i = digCnt-1;
			// handles case for valid expressions without parenthesis
			// 10; <10; <<>>>>>>50
			if (openParen == 0 && closedParen == 0) {
				if (i == line.length() - 2) {
					if (stack.top() >= 0) {
						n = stack.top();
						stack.pop();

						// check for 2 consecutive numbers without an operator in between
						if (!stack.empty() && stack.top() >= 0) {
							cerr << "Malformed" << endl;
							while(!stack.empty())
								stack.pop();
							return;
						}

						while (!stack.empty()) {
							if (stack.top() == SFT_RIGHT) {
								n /= 2;
								stack.pop();
							}
							else if (stack.top() == SFT_LEFT) {
								n *= 2;
								stack.pop();
							}
						}
					}
					stack.push(n);
					return;
				}
			}
		}
		else if (line[i] == ')') {
			// check for empty parenthesis
			if (stack.top() == OPEN_PAREN || (stack.top() == PLUS || (stack.top() == MULTIPLY))) {
				cerr << "Malformed" << endl;
				while(!stack.empty())
					stack.pop();
				return;		
			}

			stack.push(CLOSED_PAREN);
			val1 = val2 = -999;
			operation = -1000;
			closedParen++;
			
			while (!stack.empty()) {
				// handle case for bit shift, since it takes most presense
				if (stack.top() == SFT_RIGHT || stack.top() == SFT_LEFT) {
					if (val1 >= 0 && val2 < 0) {
						if (stack.top() == SFT_RIGHT)
							val1 /= 2;
						else if (stack.top() == SFT_LEFT)
							val1 *= 2;

						stack.pop();
					}
					else if (val1 >= 0 && val2 >= 0) {
						if (stack.top() == SFT_RIGHT)
							val2 /= 2;
						else if (stack.top() == SFT_LEFT)
							val2 *= 2;

						stack.pop();
					}
					// error for invalid precedence
					if (!stack.empty() && stack.top() >= 0) {
						cerr << "Malformed" << endl;
						while(!stack.empty())
							stack.pop();
						return;			
					}
				}
				else if (stack.top() >= 0) {
					if (val1 == -999) {
						val1 = stack.top();
						stack.pop();
					}
					else if (val2 == -999) {
						val2 = stack.top();
						stack.pop();
					}
				}
				else if (val1 >= 0 && val2 >= 0 && operation > -1000) {
					if (operation == PLUS) {
						val2 += val1;
						// error checking for mixing operators
						if (stack.top() == MULTIPLY) {
							cerr << "Malformed" << endl;
							while(!stack.empty())
								stack.pop();
							return;							
						}
					}
					if (operation == MULTIPLY) {
						val2 *= val1;
						// error checking for mixing operators
						if (stack.top() == PLUS) {
							cerr << "Malformed" << endl;
							while(!stack.empty())
								stack.pop();
							return;							
						}
					}
					stack.push(val2);
					val1 = val2 = -999;
					operation = -1000;
				}
				else if (stack.top() < CLOSED_PAREN && operation == -1000) {
					if (stack.top() == PLUS)
						operation = PLUS;
					else if (stack.top() == MULTIPLY)
						operation = MULTIPLY;

					stack.pop();
					// check for ( operator
					if (!stack.empty() && (stack.top() == OPEN_PAREN || stack.top() < CLOSED_PAREN)) {
						cerr << "Malformed" << endl;
						while(!stack.empty())
							stack.pop();
						return;
					}
				}
				else {
					if (stack.top() == OPEN_PAREN) {
						stack.pop();
						if (!stack.empty() && (stack.top() > CLOSED_PAREN)) {
							stack.push(val1);
							val1 = val2 = -999;
							operation = -1000;
							break;
						}
						else if (!stack.empty() && stack.top() <-10 && (stack.top() != SFT_LEFT && stack.top() != SFT_RIGHT)) {
							stack.push(val1);
							val1 = val2 = -999;
							operation = -1000;
							break;
						}
						else if (!stack.empty() && stack.top() == OPEN_PAREN) {
							stack.push(OPEN_PAREN);
							break;
						}				
					}
					else
						stack.pop();
				}
			}
			if (val2 == -999 && val1 >= 0)
				stack.push(val1);
		}
	}
	// check for parenthesis mismatch
	if ((openParen != closedParen || closedParen == 0) && (stack.top() != OPEN_PAREN)) {
		cerr << "Malformed" << endl;
		while(!stack.empty())
			stack.pop();
		return;
	}
}

bool checkValid(const char c, const char * array, const int size) {
	for (int i = 0; i < size; i++) {
		if (array[i] == c)
			return true;
	}
	return false;
}