/* Abstract class for parsing contents of webpages in certain */
/* formats such as HTML or MD */
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "setutility.h"

class Parser {
public:
	virtual ~Parser() {};

	// parses a file and returns all unique words and links according to
	// the parsing file formats
	virtual void parse(StringSet& words, StringSet& links, std::string file) = 0;
};

#endif