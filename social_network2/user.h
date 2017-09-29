/**************************************************************************
 * File name : user.h
 * Author    : Sarah Cheung
 * Email     : cheungsa@usc.edu
 * Date      : 4/25/17
 * Purpose   : User class models a single user and their information
**************************************************************************/

#ifndef USER_H
#define USER_H
#include <string>
#include <vector>

using namespace std;

class User {
 public:
   User(int uId, string uName, int uYear, int uZip); // constructor
   ~User(); // destructor
   void add_friend(int fId); // add new user
   void delete_friend(int fId); // remove new user
   int getid(); // get id of user
   string getname(); // get name of user
   int getyear(); // get birth year of user
   int getzip(); // get zip code of user
   vector<int>* getfriends(); // pointer vector to friend list
   
   int depth; // distance between friends
   int predecessor; // previous user
   int score; // score of suggested friend
   string set_member; // suggested friend
   
 private:
   int id;
   string name;
   int year;
   int zip;
   vector<int> friends;
};

#endif
