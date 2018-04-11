#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
#include "websearcheng.h"

WebSearchEng::WebSearchEng() {
	numWebpages = 0;
}

WebSearchEng::~WebSearchEng() {
	for (std::set<WebPage*>::iterator it = allWebpages.begin(); 
		it != allWebpages.end(); ++it)
	{
		delete *it;
	}	
	for (std::set<WebPage*>::iterator it2 = nonexistentWebpages.begin(); 
		it2 != nonexistentWebpages.end(); ++it2)
	{
		delete *it2;
	}
}

// Reads in the list of webpages in the index text file //
void WebSearchEng::addParsedIndexFile(std::string file, Parser* parser) {
	std::ifstream ifile;
	ifile.open(file.c_str());
	if (ifile.fail())
	{
		return;
	}
	std::string line;
	while (getline(ifile,line))
	{
		if (line.empty())
		{
			continue;
		}
		else
		{
			numWebpages++;
			WebPage* newWebpage = new WebPage(line);
			allWebpages.insert(newWebpage);
		}
	}
	ifile.close();
	std::set<WebPage*>::iterator it;
	for (it = allWebpages.begin(); it != allWebpages.end(); ++it)
	{
		addParsedPage(*it, parser);
	}	
}

// Parses each webpage in the index text file
void WebSearchEng::addParsedPage(WebPage* newWebpage, Parser* parser) {
	StringSet wordSet;
	StringSet linkSet;
	parser->parse(wordSet, linkSet, newWebpage->getFile());
	newWebpage->setWords(wordSet);
	newWebpage->setLinks(linkSet);

	// add outgoing links to new webpage's set
	std::set<std::string>::iterator outIt;
	for (outIt = linkSet.begin(); outIt != linkSet.end(); ++outIt)
	{
		bool pageExists = false; // checks if webpage exists in set of all webpages
		std::set<WebPage*>::iterator webIt;
		for (webIt = allWebpages.begin(); webIt != allWebpages.end(); ++webIt)
		{
			if (*outIt == (*webIt)->getFile())
			{
				newWebpage->addOLink(*webIt);
				pageExists = true;
			}
		}
		if (!pageExists) // for nonexistent page
		{
			WebPage* newOLink = new WebPage(*outIt);
			newWebpage->addOLink(newOLink);
			nonexistentWebpages.insert(newOLink);
		}
	}

	// add incoming links make to related webpages' sets
	std::set<std::string>::iterator inIt;
	for (inIt = linkSet.begin(); inIt != linkSet.end(); ++inIt)	
	{
		std::set<WebPage*>::iterator webIt;
		for (webIt = allWebpages.begin(); webIt != allWebpages.end(); ++webIt)
		{
			if (*inIt == (*webIt)->getFile())
			{
				(*webIt)->addILink(newWebpage);
			}	
		}		
	}

	// updating collection of word sets
	std::set<std::string>::iterator it;
	for (it = wordSet.begin(); it != wordSet.end(); ++it)
	{ 
		std::string lWord = ""; // string of word converted to lowercase
		for (unsigned int i = 0; i<(*it).length(); i++)
		{
			char c = (*it)[i];
			c = tolower(c);
			lWord += c;
		}
		std::map<std::string, WebPageSet>::iterator it2 = wordMap.find(lWord);
		if (it2 != wordMap.end()) // word exists, update word set
		{
			WebPageSet existingWebpage = wordMap[lWord];
			existingWebpage.insert(newWebpage);
			wordMap[lWord] = existingWebpage;
		}
		else // word doesn't exist, add word in
		{
			WebPageSet newWebpageSet;
			newWebpageSet.insert(newWebpage);
			wordMap.insert(make_pair(lWord, newWebpageSet));
		}
	}
}

// Returns specified webpage
WebPage* WebSearchEng::getWebpage(WebPage* web, std::string webpage) {
	std::set<WebPage*>::iterator it;
	for (it = allWebpages.begin(); it != allWebpages.end(); ++it)
	{
		if (webpage == (*it)->getFile())
		{
			web = *it;
			break;
		}
	}
	return web;
}

// Returns all webpages
WebPageSet& WebSearchEng::getWebpages() {
	return allWebpages;
}

// Returns all webpages that contain the given word
WebPageSet WebSearchEng::oneFunc(std::string word) {
	std::string lWord = ""; // string of word converted to lowercase
	for (unsigned int i = 0; i<word.length(); i++)
	{
		char c = word[i];
		c = tolower(c);
		lWord += c;
	}
	WebPageSet foundWebpage;
	std::map<std::string, WebPageSet>::iterator it = wordMap.find(lWord);
	if (it != wordMap.end())
	{
		foundWebpage = it->second;
		return foundWebpage;
	}	
	return foundWebpage;	
}

// Returns all webpages that contain all of the given words
WebPageSet WebSearchEng::andFunc(std::list<std::string> wordList) {
	WebPageSet compSet = allWebpages;
	std::list<std::string>::iterator it;
	for (it = wordList.begin(); it != wordList.end(); ++it)
	{
		compSet = oneFunc(*it).intersectSet(compSet);		
	}
	return compSet;
}

// Returns all webpages that contain at least one of the given words
WebPageSet WebSearchEng::orFunc(std::list<std::string> wordList) {
	WebPageSet compSet;
	std::list<std::string>::iterator it;
	for (it = wordList.begin(); it != wordList.end(); ++it)
	{
		compSet = oneFunc(*it).unionSet(compSet);		
	}
	return compSet;	
}

// Returns all webpages which have a link to the specified webpage
WebPageSet WebSearchEng::incomingFunc(std::string webpage) {
	WebPageSet compSet;
	std::set<WebPage*>::iterator it;
	for (it = allWebpages.begin(); it != allWebpages.end(); ++it)
	{
		if (webpage == (*it)->getFile())
		{
			compSet = (*it)->getILinks();
			break;
		}
	}
	return compSet;
}

// Returns all webpages which the specified webpage links to
WebPageSet WebSearchEng::outgoingFunc(std::string webpage) {
	WebPageSet compSet;
	std::set<WebPage*>::iterator it;
	for (it = allWebpages.begin(); it != allWebpages.end(); ++it)
	{
		if (webpage == (*it)->getFile())
		{
			compSet = (*it)->getOLinks();
			break;
		}
	}
	return compSet;	
}

// Returns number of webpages
int WebSearchEng::getNumWebpages() {
	return numWebpages;
}