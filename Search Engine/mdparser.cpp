#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include "mdparser.h"
#include "webpage.h"

void MDParser::parse(StringSet& words, StringSet& links, std::string file) {
	std::ifstream ifile;
	ifile.open(file.c_str());
	if (ifile.fail())
	{
		return;
	}
	std::string line;
	while (getline(ifile, line))
	{
		std::string currLine = line;
		std::string currWord;
		std::string currLink;
		for (unsigned int i=0; i<line.length(); i++)
		{
			if (isalnum(line[i])) // letter or digit
			{
				char c = tolower(currLine[i]);
				currWord = currWord + c;
				if (i == line.length()-1)
				{
					words.insert(currWord);
					currWord == "";
				}
			}
			else if (line[i] == '(') // link to file
			{
				i++;
				while (line[i] != ')')
				{
					currLink += line[i];
					i++;
				}
				links.insert(currLink);
				currLink = "";
			}
			else if (line[i] == '[') // anchor text
			{
				i++;
				while (line[i] != ']')
				{
					if (isalnum(line[i])) // letter or digit
					{
						currWord += line[i];
					}
					else // special character or space
					{
						words.insert(currWord);
						currWord = ""; // clearing current word
					}
					i++;
				}
			}
			else // special character or space
			{
				if (currWord.length() > 0)
				{
					//std::cout << "Inserting current word: " << currWord << std::endl;
					words.insert(currWord);
				}
				currWord = "";				
			}
		}
	}

	ifile.close();
}