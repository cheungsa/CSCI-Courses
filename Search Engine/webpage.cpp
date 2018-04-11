#include <iostream>
#include <fstream>
#include <cctype>
#include <stdio.h>
#include "setutility.h"
#include "webpage.h"
#include "mdparser.h"

WebPage::WebPage() {

}

WebPage::~WebPage() {

}

WebPage::WebPage(std::string file) {
	filename = file;
	pagerank = 1;
	numILinks = 0;
	numOLinks = 0;
	foundWebpage = false;
	MDParser parsed;
	parsed.parse(words, links, filename);
}

// sets filename of webpage
void WebPage::setFile(std::string file) {
	filename = file;
}

// returns filename of webpage 
std::string WebPage::getFile() const {
	return filename;
}

// updates set with input words
void WebPage::setWords(const StringSet& w) {
	StringSet wordSet;
	std::set<std::string>::iterator it1;
	std::set<std::string>::iterator it2;
	for (it1 = words.begin(); it1 != words.end(); ++it1)
	{
		wordSet.insert(*it1);
	}
	for (it2 = w.begin(); it2 != w.end(); ++it2)
	{
		if (wordSet.find(*it2) == wordSet.end())
		{
			wordSet.insert(*it2);
		}
	}
	words = wordSet;
}

// updates set with input links
void WebPage::setLinks(const StringSet& l) {
	StringSet linkSet;
	std::set<std::string>::iterator it1;
	std::set<std::string>::iterator it2;
	for (it1 = links.begin(); it1 != links.end(); ++it1)
	{
		linkSet.insert(*it1);
	}

	for (it2 = l.begin(); it2 != l.end(); ++it2)
	{
		if (linkSet.find(*it2) == linkSet.end())
		{
			linkSet.insert(*it2);
		}
	}
	links = linkSet;
}

// returns all unique, parsed words of webpage 
StringSet WebPage::getWords() const {
	return words;
} 

// displays contents of the specified webpage
StringSet WebPage::getLinks() const {
	return links;
}

// adds a page with a link to the specified webpage
void WebPage::addILink(WebPage* web) {
	numILinks++;
	iWebpage.insert(web);
} 

// returns all pages that link to the specified webpage
WebPageSet WebPage::getILinks() const {
	return iWebpage;
}

// returns the number of incoming links to the webpage
int WebPage::getNumILinks() {
	return numILinks;
}

// adds a page which the specified webpage links to 
void WebPage::addOLink(WebPage* web) {
	numOLinks++;
	oWebpage.insert(web);
}

// returns all pages which the specified webpage links to
WebPageSet WebPage::getOLinks() const {
	return oWebpage;
}

// sets the number of outgoing links from the webpage
void WebPage::setNumOLinks(int num) {
	numOLinks = num;
}

// returns the number of outgoing links from the webpage
int WebPage::getNumOLinks() {
	return numOLinks;
}

// sets the webpage as found
void WebPage::pageFound(bool f) {
	foundWebpage = f;
}

// returns whether the webpage is found
bool WebPage::getFound() {
	return foundWebpage;
}

// sets page rank of webpage
void WebPage::setPageRank(double rank) {
	pagerank = rank;
}

// gets page rank
double WebPage::getPageRank() const {
	return pagerank;
}

// returns contents of webpage
std::ostream & operator<< (std::ostream & os, const WebPage& web) {
	std::ifstream ifile;
	std::string line;
	std::string text;
	ifile.open(web.getFile().c_str());
	if (ifile.fail())
	{
		return os;
	}
	else if (ifile.peek() == std::ifstream::traits_type::eof())
	{
		return os;
	}
	else
	{
		os << "\n";
	}
	while (getline(ifile, line))
	{
		for (unsigned int i=0; i<line.length(); i++)
		{
			if (line[i] == '(')
			{
				while (line[i] != ')')
				{
					i++;
				}
			}
			else if (isspace(line[i]))
			{
				os << " ";
			}
			else
			{
				os << line[i];
			}
		}
		os << "\n";
		if (!ifile.eof())
		{

		}
	}
	ifile.close();
	return os;
}