#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include "setutility.h"
#include "webpage.h"
#include "mdparser.h"
#include "websearcheng.h"
#include "pagerank.h"
#include <string>

using namespace std;

PageRank::PageRank(std::string index, double myEpsilon, int mySteps)
{
	epsilon = myEpsilon;
	steps = mySteps;
	counter = 0;

	parsedPage = new MDParser();
	searcheng.addParsedIndexFile(index, parsedPage);
}

PageRank::~PageRank() {
	delete parsedPage;
}

void PageRank::displayResults(std::ofstream& os) {
	PageRankComp PRcomp;

	// push webpages into lists
	WebPageSet holdWebpages = results;
	WebPageSet pushWebpages = results;

	std::set<WebPage*>::iterator it;
	for (it = holdWebpages.begin(); it != holdWebpages.end(); ++it) 
	{
		WebPageSet inLinks;
		inLinks = (*it)->getILinks();
		if ((*it)->getNumILinks() != 0) 
		{
			std::set<WebPage*>::iterator it2;
			for (it2 = inLinks.begin(); it2 != inLinks.end(); ++it2) 
			{
				pushWebpages.insert(*it2);
			}
		}
		WebPageSet outLinks;
		outLinks = (*it)->getOLinks();
		if ((*it)->getNumOLinks() != 0) 
		{
			std::set<WebPage*>::iterator it2;
			for (it2 = outLinks.begin(); it2 != outLinks.end(); ++it2) 
			{
				pushWebpages.insert(*it2);
			}
			outLinks.clear();
			inLinks.clear();
		}
	}
	std::set<WebPage*>::iterator it3;
	for (it3 = pushWebpages.begin(); it3 != pushWebpages.end(); ++it3) 
	{
		linkList.push_back(*it3);
	}
	
	setAllPageRank(linkList);

	linkList.sort(PRcomp);

	// display results
	os << linkList.size();
	if (linkList.size() != 0)
	{
		os << "\n";
	}
	int count = 0;
	std::list<WebPage*>::iterator it4;
	for (it4 = linkList.begin(); it4 != linkList.end(); it4++) 
	{			
		//std::cout << "File '" << (*it4)->getFile() << "' : " << (*it4)->getPageRank() << std::endl;
		os << (*it4)->getFile();
		if (count != (int)linkList.size()-1)
		{
			os << "\n";
			count++;
		}
	}
}


void PageRank::setAllPageRank(std::list<WebPage*> rank) {	
	std::list<WebPage*>::iterator it;
	for (it = rank.begin(); it != rank.end(); ++it) 
	{
		bool foundWebpage = false;
		(*it)->setPageRank(double(1.0/(searcheng.getNumWebpages())));
		WebPageSet outLinks = (*it)->getOLinks();
		
		std::set<WebPage*>::iterator it2;
		for (it2 = outLinks.begin(); it2 != outLinks.end(); ++it2) 
		{
			if ((*it2)->getFile() == (*it)->getFile())
			{
				foundWebpage = true;
			}			
		}
		if (!foundWebpage) 
		{
			(*it)->pageFound(true);
		}
	}
	iterateStepsPageRank(rank);
}

void PageRank::iterateStepsPageRank(std::list<WebPage*> rank) {
	std::list<WebPage*> webpageList = rank;
	counter++;
	std::list<WebPage*>::iterator it;
	for (it = webpageList.begin(); it != webpageList.end(); ++it) 
	{
		WebPageSet inLinks = (*it)->getILinks();
		double sum = 0.0;
		if (!((*it)->getFound())) 
		{
			sum = (*it)->getPageRank()/(double((*it)->getNumOLinks()));
		}
		else 
		{
			sum = (*it)->getPageRank()/(double((*it)->getNumOLinks()+1.0));
		}
		
		if ((*it)->getNumILinks() > 0) 
		{
			std::set<WebPage*>::iterator it3;
			for (it3 = inLinks.begin(); it3 != inLinks.end(); ++it3) 
			{
				std::list<WebPage*>::iterator it4;
				for (it4 = rank.begin(); it4 != rank.end(); ++it4) 
				{
					if ((*it4)->getFile() == (*it3)->getFile() &&
						((*it)->getFile() != (*it3)->getFile())) 
					{
						if (!((*it3)->getFound())) 
						{
							sum += ((*it3)->getPageRank())/(double((*it3)->getNumOLinks()));
						}
						else 
						{
							sum += ((*it3)->getPageRank())/(double((*it3)->getNumOLinks()+1.0));	
						}
					}
				}
			}
		}

		std::list<WebPage*>::iterator it2;
		for (it2 = rank.begin(); it2 != rank.end(); ++it2) 
		{
			if ((*it)->getFile() == (*it2)->getFile()) 
			{			
				(*it2)->setPageRank((double((1.0-epsilon)*sum))+(double(epsilon/rank.size())));
			}
		}
	}
	if (counter > steps)
	{
		return;
	} 
	else
	{
		iterateStepsPageRank(rank);
	}	
}

void PageRank::setSearchResults(WebPageSet resultSet) {
	results = resultSet;
}