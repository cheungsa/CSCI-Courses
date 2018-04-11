#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <list>
#include <stdio.h>
#include <cctype>
#include "webpage.h"
#include "setutility.h"
#include "mdparser.h"
#include "crawlersearch.h"

using namespace std;

// converts string to lowercase
string toLower(string str);
// displays results of webpage search
void displaySearch(set<WebPage*>& searchResults, ofstream& os); 
// checks if line is single word search command
bool singleWordCheck(string line); 
// checks for empty file
bool isEmpty(std::ifstream& ifile); 
// parses configuration file for index and output files
void parseConfigFile(string ifile, string& index, string& output);

bool isEmpty(std::ifstream& ifile)
{
    return ifile.peek() == std::ifstream::traits_type::eof();
}

string toLower(string str) {
	string lstr = "";
	for (unsigned int i=0; i<str.length(); i++)
	{
		char c = str[i];
		c = tolower(c);
		lstr += c;
	}
	return lstr;
}

void displaySearch(set<WebPage*>& searchResults, ofstream& os) {
	int matches = searchResults.size(); // number of matched files
	string results = ""; // to avoid outputting duplicates
	set<WebPage*>::iterator it1;
	for (it1 = searchResults.begin(); it1 != searchResults.end(); ++it1)
	{
  		size_t found = results.find((*it1)->getFile());		
  		if (found != std::string::npos)
  		{
  			matches--;
  		}
  		results = results + (*it1)->getFile() + " ";
	}
	if (matches == 0)
	{
		os << matches;
		return;
	}
	os << matches << "\n";
	int count = 0;
	results = ""; // to avoid outputting duplicates
	set<WebPage*>::iterator it2;
	for (it2 = searchResults.begin(); it2 != searchResults.end(); ++it2)
	{
  		size_t found = results.find((*it2)->getFile());		
  		if (found == std::string::npos)
  		{
  			count++;
  			os << (*it2)->getFile();
  			if (count != matches)
  			{
  				os << "\n";
  			}
  		}
  		results = results + (*it2)->getFile() + " ";
	}
}

bool singleWordCheck(string line)
{
	bool validWord = true; // check if command is 'single word'
	for (unsigned int i=0; i<line.length(); i++)
	{
		if (isspace(line[i]))
		{
			validWord = false;
			break;
		}
	}
	return validWord;
}

void parseConfigFile(string config, string& index, string& output)
{
	ifstream ifile;
	ifile.open(config.c_str());
	if (ifile.fail())
	{
		return;
	}
	string line;
	while (getline(ifile,line))
	{	
		size_t foundIndex = line.find("INDEX_FILE");
		size_t foundOutput = line.find("OUTPUT_FILE");
		if (foundIndex != std::string::npos)
		{
			for (size_t i = foundIndex+10; i < line.length(); i++)
			{
				if (line[i] == '#')
				{
					break;
				}
				else if (isspace(line[i]) || line[i] == '=')
				{
					continue;
				}
				else
				{
					index += line[i];
				}
			}
		}
		else if (foundOutput != std::string::npos)
		{
			for (size_t i = foundOutput+11; i < line.length(); i++)
			{
				if (line[i] == '#')
				{
					break;
				}
				else if (isspace(line[i]) || line[i] == '=')
				{
					continue;
				}
				else
				{
					output += line[i];
				}
			}
		}
		else
		{
			continue;
		}
	}
}

int main (int argc, char* argv[]) {
	string inputFile;
	if (argc < 2)
	{
		inputFile = "config.txt";
	}
	else
	{
		inputFile = argv[1];
	}
	string indexFile = "";
	string outputFile = "";
	parseConfigFile(inputFile, indexFile, outputFile);

	string input = indexFile;
	ofstream output(outputFile.c_str());
	string path;

	CrawlerSearch crawler;
	Parser* parser = new MDParser();
	crawler.addParsedIndexFile(indexFile, parser, path);
	crawler.populateFile(output);

	output.close();

	return 0;
}