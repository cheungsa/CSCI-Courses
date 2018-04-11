#ifndef PAGERANK_H
#define PAGERANK_H

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <string>
#include <list>
#include <map>
#include "setutility.h"
#include "mdparser.h"
#include "webpage.h"
#include "websearcheng.h"

// Webpage comparisons based on page rank
struct PageRankComp {
    bool operator()(WebPage* lhs, WebPage* rhs) 
    { 
      return lhs->getPageRank() >= rhs->getPageRank(); 
    }
};

class PageRank 
{
public:
	PageRank(std::string index, double myEpsilon, int mySteps);
	~PageRank();
	void displayResults(std::ofstream& os);
	void setAllPageRank(std::list<WebPage*> rank);
	void iterateStepsPageRank(std::list<WebPage*> rank);
	void setSearchResults(WebPageSet resultSet);

private:
	int counter;
	WebSearchEng searcheng;
	WebPageSet results;	
	Parser* parsedPage;
	std::list<WebPage*> linkList;
	double epsilon;
	int steps;
};

#endif