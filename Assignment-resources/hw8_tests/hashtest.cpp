#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "hashtable_sol.h" 

#include "../hw8_sol/hashtable.h" // Change to point to the student's solution header file.

// This should be changed to the name of the class that the student uses for
// their hashtable. 
#define HASH_TABLE HashTable

std::string ToLower(const std::string& word);
std::string GenerateRandomString(int numCharacters);
void ReadFile(char* file, std::vector<std::string>& wordVector);
void GenerateWords(int numWords, std::vector<std::string>& wordVector);
void ReportAllMap(std::ostream& output, const std::map<std::string, int>& verify);

int main(int argc, char* argv[])
{
	// Show two different usages. 
	if(argc < 4)
	{
		std::cerr << "Usage: ./hashtest input_file hash_output verify_output" << std::endl;
		std::cerr << "OR: ./hashtest seed num_words hash_output verify_output" << std::endl;
		return -1;
	}

	// Get the input arguments based on what kind of options were used. The input can either
	// be from a file with preset words, or the words can be randomly generated here
	// within the test executable. 
	char* hashOutput;
	char* verifyOutput;
	std::vector<std::string> wordVector;
	int seed{ std::atoi(argv[1]) };
	if(seed == 0)
	{
		ReadFile(argv[1], wordVector);
		hashOutput = argv[2];
		verifyOutput = argv[3];
	}
	else
	{
		srand(seed);
		int numWords{ std::atoi(argv[2]) };
		GenerateWords(numWords, wordVector);
		hashOutput = argv[3];
		verifyOutput = argv[4];
	}

	// The two data structures: the student's splay tree and
	// the verification map that holds the true values. 
	HashTableSol verify;
	HASH_TABLE st;

	// Add the elements into the splay tree and the verify map.
	for(auto iter = wordVector.begin(); iter != wordVector.end(); ++iter)
	{
		// Add the element into the splay tree.
		st.add(*iter);

		// Add the element into the solution hash table.
		verify.add_sol(*iter);
	}

	// Print out each of the map and the splay tree to output files. 
	std::ofstream verifyOut{ verifyOutput };
	verify.reportAll_sol(verifyOut);
	std::ofstream hashOut{ hashOutput };
	st.reportAll(hashOut);

	verifyOut.close();
	hashOut.close();

	return 0;
}

void ReadFile(char* file, std::vector<std::string>& wordVector)
{
	std::ifstream inputFile{ file };
	if(inputFile.is_open())
	{
		std::string line;
		while(std::getline(inputFile, line))
		{
			std::stringstream ss{ line };
			while(ss >> line)
			{
				wordVector.push_back(line);
			}
		}
	}
	inputFile.close();
}

std::string ToLower(const std::string& word)
{
	std::string temp{ word };
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	return temp;
}

void ReportAllMap(std::ostream& output, const std::map<std::string, int>& verify)
{
	for(auto iter = verify.begin(); iter != verify.end(); ++iter)
	{
		output << iter->first << " " << iter->second << std::endl;
	}
}

std::string GenerateRandomString(int numCharacters)
{
	int characters = 0;
	std::string returnString = "";
	while(characters < numCharacters)
	{
		returnString += static_cast<char>(rand() % 26 + 'a');
		++characters;
	}
	return returnString;
}

void GenerateWords(int numWords, std::vector<std::string>& wordVector)
{
	for(int i = 0; i < numWords; ++i)
	{
		wordVector.push_back(GenerateRandomString(rand() % 27 + 1));
	}
}