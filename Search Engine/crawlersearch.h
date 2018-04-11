#ifndef CRAWLERSEARCH_H
#define CRAWLERSEARCH_H

#include <iostream>
#include <string>
#include <map>
#include <list>
#include "webpage.h"
#include "mdparser.h"
#include "setutility.h"
#include "crawlerpage.h"

class CrawlerSearch {
public:
	CrawlerSearch();
	~CrawlerSearch();
	void addParsedIndexFile(std::string file, Parser* parser, std::string path);
  	void addParsedPage(std::string file, Parser* parser, std::string path);
  	void populateFile(std::ostream &out);

private:
	std::string path;
	std::list<CrawlerPage*> discoveredPages;
	std::map<std::string, WebPage*> links;
};

#endif 