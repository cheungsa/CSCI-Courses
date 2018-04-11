/* Classes to allow user to use set intersection and set union operations */
/* on two different sets: set<string> and set<Webpage*> */
#include <iostream>
#include <set>
#include <string>
#include "webpage.h"

#ifndef SETUTILITY_H 
#define SETUTILITY_H

class WebPage; // to avoid redefinition errors

template<class T>
class SetUtility : public std::set<T> {
public:
  SetUtility();
  void printSet();
  SetUtility<T> intersectSet(const SetUtility<T>& other);
  SetUtility<T> unionSet(const SetUtility<T>& other);

};

template<class T>
SetUtility<T>::SetUtility() {}

template<class T>
void SetUtility<T>::printSet() {
	typename std::set<T>::iterator it;
	for (it = this->begin(); it != this->end(); ++it)
	{
		std::cout << *it << std::endl;
	}	
}

template<class T>
SetUtility<T> SetUtility<T>::intersectSet(const SetUtility<T>& other) {
	SetUtility<T> TSet;
	typename std::set<T>::iterator it;
	for (it = this->begin(); it != this->end(); ++it)
	{
		if (other.find(*it) != other.end())
		{
			TSet.insert(*it);
		}
	}
	return TSet;
}

template<class T>
SetUtility<T> SetUtility<T>::unionSet(const SetUtility<T>& other) {
	SetUtility<T> TSet;
	typename std::set<T>::iterator it1;
	typename std::set<T>::iterator it2;
	for (it1 = other.begin(); it1 != other.end(); ++it1)
	{
		TSet.insert(*it1);
	}
	for (it2 = this->begin(); it2 != this->end(); ++it2)
	{
		TSet.insert(*it2);
	}
	return TSet;
}

typedef SetUtility<std::string> StringSet;
typedef SetUtility<WebPage*> WebPageSet;
#endif