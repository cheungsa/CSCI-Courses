#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
#include "crawlerpage.h"

CrawlerPage::CrawlerPage(WebPage* webpage, std::string path) : webpage(webpage), path(path) {

}

CrawlerPage::~CrawlerPage() {

}

// returns webpage
WebPage* CrawlerPage::getWebpage() {
	return webpage;
}

// returns path to webpage
std::string CrawlerPage::getPath() {
	return path;
}

