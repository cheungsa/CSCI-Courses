/* Class to perform actual search logic: stores all the webpages and */
/* index data, and performs the search operations */
#ifndef CRAWLERPAGE_H
#define CRAWLERPAGE_H

#include <string>
#include <list>
#include <map>
#include "setutility.h"
#include "webpage.h"

class CrawlerPage {
public:
	CrawlerPage(WebPage* web, std::string path);
	~CrawlerPage();
	WebPage* getWebpage(); // returns webpage
	std::string getPath(); // returns path to webpage

private:	
	WebPage* webpage;
	std::string path;
};

#endif