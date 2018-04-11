/* Class to perform actual search logic: stores all the webpages and */
/* index data, and performs the search operations */
#ifndef WEBSEARCHENG_H
#define WEBSEARCHENG_H

#include <string>
#include <list>
#include <map>
#include "setutility.h"
#include "webpage.h"
#include "parser.h"

class WebSearchEng {
public:
	WebSearchEng();
	~WebSearchEng();

	// Reads the list of webpages in the index text file
	void addParsedIndexFile(std::string ifile, Parser* parser);

	// Parses each webpage in the index text file
	void addParsedPage(WebPage*, Parser* parser);

	// Returns specified webpage
	WebPage* getWebpage(WebPage* web, std::string webpage);

	// Returns all webpages
	WebPageSet& getWebpages();

	// Returns all webpages that contain the given word
	WebPageSet oneFunc(std::string word);

	// Returns all webpages that contain all of the given words
	WebPageSet andFunc(std::list<std::string> wordList);

	// Returns all webpages that contain at least one of the given words
	WebPageSet orFunc(std::list<std::string> wordList);

	// Returns all webpages which have a link to the specified webpage
	WebPageSet incomingFunc(std::string webpage);

	// Returns all webpages which the specified webpage links to
	WebPageSet outgoingFunc(std::string webpage);

	// Returns number of webpages
	int getNumWebpages();

private:
	WebPageSet allWebpages;
	WebPageSet nonexistentWebpages;
	std::map<std::string, WebPageSet> wordMap;
	std::map<std::string, WebPageSet> linkMap;
	int numWebpages;
};

#endif