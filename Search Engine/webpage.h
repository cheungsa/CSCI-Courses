/* Class to store all unique text words extracted and all the links identified*/
#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <iostream>
#include <string>
#include "setutility.h"

class WebPage {
public:
    WebPage();
    ~WebPage();
    WebPage(std::string file);

    // sets filename of webpage
    void setFile(std::string file);

    // returns filename of webpage 
    std::string getFile() const;

    // updates set with input words
    void setWords(const StringSet& w); 

    // updates set with input links
    void setLinks(const StringSet& l); 

    // returns all unique, parsed words of webpage 
    StringSet getWords() const; 

    // displays contents of the specified webpage
    StringSet getLinks() const;

    // adds a page with a link to the specified webpage
    void addILink(WebPage* web); 

    // returns all pages that link to the specified webpage
    WebPageSet getILinks() const;

    // returns the number of incoming links to the webpage
    int getNumILinks();

    // adds a page which the specified webpage links to 
    void addOLink(WebPage* web); 

    // returns all pages which the specified webpage links to
    WebPageSet getOLinks() const; 

    // sets the number of outgoing links from the webpage
    void setNumOLinks(int num);

    // returns the number of outgoing links from the webpage
    int getNumOLinks();

    // sets the webpage as found
    void pageFound(bool f);

    // returns whether the webpage is found
    bool getFound();

    // sets page rank of webpage
    void setPageRank(double rank);

    // gets page rank
    double getPageRank() const;

    // returns contents of webpage
    friend std::ostream & operator<< (std::ostream & os, const WebPage& web);

private:
    std::string filename;
    StringSet words;
    StringSet links;
    WebPageSet iWebpage;
    WebPageSet oWebpage;
    double pagerank;
    int numILinks;
    int numOLinks;
    bool foundWebpage;
};

#endif