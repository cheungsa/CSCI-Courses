/**************************************************************************
 * File name : user.cpp
 * Author    : Sarah Cheung
 * Email     : cheungsa@usc.edu
 * Date      : 4/25/17
 * Purpose   : Models a single user and their information
**************************************************************************/

#include <iostream>
#include "user.h"
#include <fstream>
#include <sstream>

using namespace std;

// constructor - read new user and their info
User::User(int uId, string uName, int uYear, int uZip)
{
   id = uId;
   name = uName;
   year = uYear;
   zip = uZip;
   
   depth = -1;
   predecessor = -1;
   score = 0;   
   set_member = "";
} 

// destructor
User::~User()
{

}

// accept ID of a user to add as a friend
void User::add_friend(int fId)
{
/*
   bool added = false;
   for (int i=0; i<friends.size(); i++)
   {
      if (fId == friends[i])
      {
         added = true;
      }
   }   
   if (!added)
   {
      friends.push_back(fId);
   }
*/
   for (int i=0; i<friends.size(); i++)
   {
      if (fId == friends[i])
      {
         return;
      }
   }   
   friends.push_back(fId);   
}

// accept ID of a user to delete as a friend
void User::delete_friend(int fId)
{     
   for (int i=0; i<friends.size(); i++)
   {
      // if friend ID provided is not in list of friends, do nothing
      if (fId != friends[i])
      {
         continue;   
      }      
      else
      {
         friends.erase(friends.begin()+i);
      }
   }
}

// get id of user
int User::getid()
{
   return id;
} 

// get name of user
string User::getname()
{
   return name;
}

// get birth year of user
int User::getyear()
{
   return year;
}

// get zip code of user  
int User::getzip()
{
   return zip;
}

// pointer vector to friend list, get list of friends the user has
vector<int>* User::getfriends()
{
   return &friends;
}
