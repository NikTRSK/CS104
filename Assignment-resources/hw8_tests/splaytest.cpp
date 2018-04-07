#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <map>
#include <vector>
#include <string>
#include <sstream>

#include "../hw8_sol/splaytree.h" // Change to include the student's splaytree implementation.

// This should be changed to the name of the class that the student uses for
// their splay tree. 
#define SPLAY_TREE SplayTree

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
		std::cerr << "Usage: ./splaytest input_file splay_output verify_output" << std::endl;
		std::cerr << "OR: ./splaytest seed num_words splay_output verify_output" << std::endl;
		return -1;
	}

	// Get the input arguments based on what kind of options were used. The input can either
	// be from a file with preset words, or the words can be randomly generated here
	// within the test executable. 
	char* splayOutput;
	char* verifyOutput;
	std::vector<std::string> wordVector;
	int seed{ std::atoi(argv[1]) };
	if(seed == 0)
	{
		ReadFile(argv[1], wordVector);
		splayOutput = argv[2];
		verifyOutput = argv[3];
	}
	else
	{
		srand(seed);
		int numWords{ std::atoi(argv[2]) };
		GenerateWords(numWords, wordVector);
		splayOutput = argv[3];
		verifyOutput = argv[4];
	}

	// The two data structures: the student's splay tree and
	// the verification map that holds the true values. 
	std::map<std::string, int> verify;
	SPLAY_TREE st;

	// Add the elements into the splay tree and the verify map.
	for(auto iter = wordVector.begin(); iter != wordVector.end(); ++iter)
	{
		// Add the element into the splay tree.
		st.add(*iter);

		// Add the element into the map and keep track of the number of times 
		// each element has been inserted. 
		auto find = verify.find(ToLower(*iter));
		if(find == verify.end())
		{
			verify.insert(std::make_pair(ToLower(*iter), 1));
		}
		else
		{
			find->second += 1;
		}
	}

	// Print out each of the map and the splay tree to output files. 
	std::ofstream verifyOut{ verifyOutput };
	ReportAllMap(verifyOut, verify);
	std::ofstream splayOut{ splayOutput };
	st.reportAll(splayOut);

	verifyOut.close();
	splayOut.close();

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