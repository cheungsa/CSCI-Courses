#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
#include "crawlersearch.h"

CrawlerSearch::CrawlerSearch() {

}

CrawlerSearch::~CrawlerSearch() {

}

// adds parsed webpage to file
void CrawlerSearch::addParsedIndexFile(std::string file, Parser* parser, std::string path) {
	std::ifstream ifile;
	ifile.open(file.c_str());
	if (ifile.fail())
	{
		return;
	}
	std::string filename;
	while (getline(ifile,filename))
	{
		if (filename.empty())
		{
			continue;
		}
		else
		{
			addParsedPage(filename, parser, path);
		}
	}
	ifile.close();
}

// parses webpage
void CrawlerSearch::addParsedPage(std::string file, Parser* parser, std::string path) {
	std::map<std::string, WebPage*>::iterator it;
	it = links.find(file);
	if (it == links.end()) // webpage has not been visited
	{
		std::ifstream ifile;
		ifile.open(file.c_str());
		if (!ifile.fail())
		{
			WebPage* newWebpage = new WebPage(file);
			links[file] = newWebpage;
			std::string updatePath = path + "/" + newWebpage->getFile();
			SetUtility<std::string> links;
			SetUtility<std::string> words;
			parser->parse(words, links, file);
			newWebpage->setLinks(links);
			newWebpage->setWords(words);
			CrawlerPage* cPage = new CrawlerPage(newWebpage, updatePath);
			discoveredPages.push_back(cPage);
			std::set<std::string>::iterator it2;
			for (it2 = links.begin(); it2 != links.end(); ++it2)
			{
				addParsedPage((*it2), parser, updatePath);
			}
		}
		ifile.close();
	}
	else // webpage has been visited
	{
		return;
	}
}

// populates file with discovered webpages
void CrawlerSearch::populateFile(std::ostream &out) {
	int count = 0;
	std::list<CrawlerPage*>::iterator it;
	for (it = discoveredPages.begin(); it != discoveredPages.end(); ++it)
	{
		out << (*it)->getWebpage()->getFile();
		if (count != (int)discoveredPages.size()-1)
		{
			out << "\n";
			count++;
		}
	}
}
