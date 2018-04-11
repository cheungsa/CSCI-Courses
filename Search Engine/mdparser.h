/* Class for parsing contents of webpages in MD format */
#ifndef MDPARSER_H
#define MDPARSER_H

#include "parser.h"

class WebPage; // to avoid redefinition errors

class MDParser : public Parser {
public:
	virtual ~MDParser() {};

	// parses a file and returns all unique words and links according to
	// the parsing file formats
	virtual void parse(StringSet& words, StringSet& links, std::string file);
};

#endif