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
#include "websearcheng.h"
#include "pagerank.h"

using namespace std;

// converts string to lowercase
string toLower(string str);
// displays results of webpage search
void displaySearch(set<WebPage*>& searchResults, ofstream& os); 
// checks if line is single word search command
bool singleWordCheck(string line); 
// checks for empty file
bool isEmpty(std::ifstream& ifile); 
// parses configuration file for index, query, and output files and parameters
void parseConfigFile(string config, string& index, string& query, string& output, double& epsilon, int& steps);
// builds the index of links from the index file
void buildIndex(string inputFile, string outputFile, list<string> links);
// parses links in file
void parse(string file, list<string>& outLinks, set<string>& links);

bool isEmpty(std::ifstream& ifile)
{
    return ifile.peek() == std::ifstream::traits_type::eof();
}

string toLower(string str) 
{
	string lstr = "";
	for (unsigned int i=0; i<str.length(); i++)
	{
		char c = str[i];
		c = tolower(c);
		lstr += c;
	}
	return lstr;
}

void displaySearch(set<WebPage*>& searchResults, ofstream& os) 
{
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

void parseConfigFile(string config, string& index, string& query, string& output, double& epsilon, int& steps)
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
		size_t foundQuery = line.find("QUERY_FILE");
		size_t foundOutput = line.find("OUTPUT_FILE");
		size_t foundEpsilon = line.find("RESTART_PROBABILITY");
		size_t foundT = line.find("STEP_NUMBER");
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
		else if (foundQuery != std::string::npos)
		{
			for (size_t i = foundQuery+10; i < line.length(); i++)
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
					query += line[i];
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
		else if (foundEpsilon != std::string::npos)
		{
			string strEpsilon = "";
			for (size_t i = foundEpsilon+19; i < line.length(); i++)
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
					strEpsilon += line[i];
				}
			}
			epsilon = std::stod(strEpsilon);
		}
		else if (foundT != std::string::npos)
		{
			string strStep = "";
			for (size_t i = foundT+11; i < line.length(); i++)
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
					strStep += line[i];
				}
			}
			steps = std::stoi(strStep);
		}
		else
		{
			continue;
		}
	}
}

void buildIndex(string inputFile, string outputFile, list<string> links)
{
	ifstream ifile;
	ifile.open(inputFile.c_str());
	if (ifile.fail())
	{
		return;
	}
	string line;
	set<string> setLinks;
	list<string> outLinks;

	while (getline(ifile,line))
	{
		if (setLinks.find(line) != setLinks.end())
		{
			continue;
		}
		else
		{
			outLinks.push_back(line);
			setLinks.insert(line);
			parse(line, outLinks, setLinks);
		}
	}

	ofstream ofile;
	ofile.open(outputFile.c_str());
	for (list<string>::iterator it = outLinks.begin(); it != outLinks.end(); ++it)
	{
		ofile << *it << "\n";
	}
	ifile.close();
	ofile.close();
}

void parse(string file, list<string>& outLinks, set<string>& links)
{
	ifstream ifile;
	ifile.open(file.c_str());
	if (ifile.fail())
	{
		return;
	}
	string line;
	while (getline(ifile,line))
	{
		std::string currLink;
		for (unsigned int i=0; i<line.length(); i++)
		{
			if (line[i] == '(') // link to file
			{
				i++;
				while (line[i] != ')')
				{
					currLink += line[i];
					i++;
				}
				if (links.find(currLink) != links.end())
				{
					continue;
				}
				else
				{
					outLinks.push_back(currLink);
					links.insert(currLink);
					parse(currLink, outLinks, links);
				}
				currLink = "";
			}	
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
	string indexFile, queryFile, outputFile;
	double epsilon = 0.0;
	int steps = 0;

	parseConfigFile(inputFile, indexFile, queryFile, outputFile, epsilon, steps);

	list<string> allLinks;
	buildIndex(inputFile, outputFile, allLinks);	

	ifstream query(queryFile.c_str());
	ofstream output(outputFile.c_str());

	// initialize search engine and parse all webpages
	WebSearchEng search;
	Parser* parsedPage = new MDParser();
	search.addParsedIndexFile(indexFile, parsedPage);

	// initialize search engine with page rank
	PageRank searchPR(indexFile, epsilon, steps);

	// read query file and perform searches
	int count = 0;
	string line;
	while (getline(query, line))
	{
		if (count > 0)
		{
			output << "\n";
		}
		string command = "";
		stringstream ss;
		ss << line;
		ss >> command;
		WebPageSet searchResults;
		list<string> queryWords;

		if (command.empty()) // empty line
		{
			continue;
		}
		// returns pages that contain the given word
		else if (singleWordCheck(line))
		{
			searchResults = search.oneFunc(command);
			searchPR.setSearchResults(searchResults);
			searchPR.displayResults(output);
		}
		// returns pages that contain all of the given words
		else if (command == "AND")
		{
			string currWord;
			while (ss >> currWord)
			{
				queryWords.push_back(currWord);
			}
			searchResults = search.andFunc(queryWords);
			searchPR.setSearchResults(searchResults);
			searchPR.displayResults(output);
		}
		// returns all the pages that contain at least one of the given words
		else if (command == "OR")
		{
			string currWord;
			while (ss >> currWord)
			{
				queryWords.push_back(currWord);
			}
			searchResults = search.orFunc(queryWords);
			searchPR.setSearchResults(searchResults);
			searchPR.displayResults(output);
		}
		// prints contents of specified webpage
		else if (command == "PRINT")
		{
			string currPage;
			ss >> currPage;
			
			// check if file is valid
			std::ifstream ifile;
			ifile.open(currPage.c_str());
			if (ifile.fail())
			{
				output << "Invalid query";
			}
			else
			{
				output << currPage;
				WebPage searchWebpage = WebPage(currPage);
				output << searchWebpage;
			}
		}
		// returns all the pages which have a link to the specified webpage
		else if (command == "INCOMING")
		{
			string currPage;
			ss >> currPage;

			// check if file is valid
			std::ifstream ifile;
			ifile.open(currPage.c_str());
			if (ifile.fail())
			{
				output << "Invalid query";
			}		
			else
			{
				searchResults = search.incomingFunc(currPage);
				displaySearch(searchResults, output);
			}
		}
		// returns all the pages which the specified webpage links to
		else if (command == "OUTGOING")
		{
			string currPage;
			ss >> currPage;

			// check if file is valid
			std::ifstream ifile;
			ifile.open(currPage.c_str());
			if (ifile.fail())
			{
				output << "Invalid query";
			}
			else
			{
				searchResults = search.outgoingFunc(currPage);
				displaySearch(searchResults, output);		
			}
		}
		else
		{
			output << "Invalid query";
		}
		count++;
	}

	delete parsedPage;
	return 0;
}