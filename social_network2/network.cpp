/**************************************************************************
 * File name : network.cpp
 * Author    : Sarah Cheung
 * Email     : cheungsa@usc.edu
 * Date      : 4/25/17
 * Purpose   : Models a basic social network of a single user, providing 
               their information and friend suggestions
**************************************************************************/

#include <iostream>
#include "network.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>

using namespace std;

// constructor
Network::Network()
{

} 

// destructor
Network::~Network()
{

}

// read users from file
int Network::read_friends(const char *filename)
{
   ifstream in_file(filename);
   
   // return -1 if fail
   if (in_file.fail())
   {
      return -1;
   }
   
   int total, currId, currYear, currZip, currLoc;
   string currName1, currName2;
   
   in_file >> total; // total number of users
   
   for (int i=0; i<total; i++)
   {
      // read user info
      in_file >> currId >> currName1 >> currName2 >> currYear >> currZip;
      
      // ignore whitespace
      in_file.ignore();
      
      // combine first and last names into a single string
      string currName = currName1 + " " + currName2;
      
      // add user to friend vector
      connections.push_back(User(currId, currName, currYear, currZip));
      
      // get line of id friend connections a user has
      string friendId;
      getline(in_file, friendId);
      stringstream line(friendId);
      
      // while not fail, read id's of users and add them to network
      while (line)
      {
         line >> currLoc;
         if (line.fail())
         {
            break;
         }
         else
         {
            connections[i].add_friend(currLoc);
         }
      }
   }   
   // return 0 if success
   return 0;
}

// write users to file
int Network::write_friends(const char *filename)
{
   ofstream out_file(filename);
   
   // return -1 if fail
   if (out_file.fail())
   {
      return -1;
   }
   
   // total number of users
   out_file << connections.size() << endl;
   
   // writes out all user info
   for (int i=0; i<connections.size(); i++)
   { 
      out_file << connections[i].getid() << endl; // write id
      out_file << "\t" << connections[i].getname() << endl; // write name
      out_file << "\t" << connections[i].getyear() << endl; // write birth year
      out_file << "\t" << connections[i].getzip() << endl; // write zipcode
      out_file << "\t";      
      // write friend connections
      for (int k=0; k < (*connections[i].getfriends()).size(); k++)
      {
         out_file << (*connections[i].getfriends())[k] << " ";
      }
      out_file << endl;
   }
   
   // return 0 if success
   return 0;
}

// add a User to the Network database
void Network::add_user(string username, int yr, int zipcode)
{
   connections.push_back(User(connections.size(), username, yr, zipcode)); 
}

// create friend connections between users
int Network::add_connection(string name1, string name2)
{
   // accept two strings - first name and last name
   int user1 = -1;
   int user2 = -1;
   for (int i=0; i<connections.size(); i++)
   {
      if (name1 == connections[i].getname())
      {
         user1 = connections[i].getid();
      }
      else if (name2 == connections[i].getname())
      {
         user2 = connections[i].getid();
      }
   }
   
   // return 0 if success
   if (user1 != -1 && user2 != -1)
   {
      connections[user1].add_friend(user2);
      connections[user2].add_friend(user1);
      return 0;
   }
   // return -1 if fail (self-connection)
   else
   {
      return -1;
   } 
}

// delete friend connections between users
int Network::remove_connection(string name1, string name2)
{
   // accept two strings - first name and last name
   int user1 = -1;
   int user2 = -1;
   for (int i=0; i<connections.size(); i++)
   {
      if (name1 == connections[i].getname())
      {
         user1 = connections[i].getid();
      }
      else if (name2 == connections[i].getname())
      {
         user2 = connections[i].getid();
      }
   }
 
   // return 0 if success
   if (user1 != -1 && user2 != -1)
   {
      connections[user1].delete_friend(user2);
      connections[user2].delete_friend(user1);
      return 0;
   }
   // return -1 if fail (self-connection)
   else
   {
      return -1;
   } 
}

// accept user name and return user ID
int Network::get_id(string username)
{
   for (int i=0; i<connections.size(); i++)
   {
      // if username in list matches given name, return user id
      if (username == connections[i].getname())
      {
         return connections[i].getid();
      }
   }
   // return -1 if fail
   return -1;
}

// return vector containing list of friend connections
vector<User>* Network::getconnections()
{
   return &connections;
}

// a shortest path starting at user "from" and ending at user "to"
vector<int> Network::shortest_path(int from, int to)
{
   // check users aren't the same
   if (to == from)
   {
      vector<int> headUser;
      headUser.push_back(from);
      return headUser;
   }
   
   // begin bfs search, starting with head User
   bfs(from); 
   User tail = connections[to]; // tail, or second, User
   vector<int> path; // vector to hold path
   vector<int> reversePath; // vector to hold path in reverse
   
   // go through tail user to head user, adding users to path vector
   while (tail.depth > 0)
   {
      path.push_back(tail.getid());
      tail = connections[tail.predecessor];
   }   
   if (path.size() > 0)
   {
      path.push_back(tail.getid()); // add next user
   }
   
   // reverse path
   for (int i=0; i<path.size(); i++)
   {
      reversePath.push_back(path[path.size()-i-1]);
   }

   clearbfs();
   return reversePath;   

   // if no path exists, return empty vector
   
}

// a list of the components of the network
vector<vector<int> > Network::groups()
{
   // double vector to hold all disjointed groups
   vector<vector<int> > allGroups;
   // call groupbfs for each member in the groups
   allGroups.push_back(groupsbfs(0));
   
   // check for users not visited
   for (int i=0; i<connections.size(); i++)
   {
      if (connections[i].depth == -1)
      {
         allGroups.push_back(groupsbfs(i)); // add to double vector
      }
   }
   
   clearbfs();
   return allGroups; 
}

// suggested friends with highest score for this user
// fills in "score" at the given pointer
vector<int> Network::suggest_friends(int who, int& score)
{   
   bfs(who); // call bfs for chosen user
   for (int i=0; i<connections.size(); i++)
   {
      // if users aren't friends
      if (connections[i].depth == 2)
      {
         for (int j=0; j<(*connections[who].getfriends()).size(); j++)
         {
            for (int k=0; k<(*connections[i].getfriends()).size(); k++)
            {
               if ((*connections[who].getfriends())[j] == 
                  (*connections[i].getfriends())[k])
               {
                  // increment score for user for every mutual friend
                  connections[i].score++;
               }
            }
         }   
      }
   }   
   // initialize highest score and update it from connections
   int highscore = -1;
   for (int i=0; i<connections.size(); i++)
   {
      if (connections[i].score > highscore)
      {
         highscore = connections[i].score;
      }
   }
      
   // vector to hold suggestions for friends
   vector<int> suggestion;
   // add friends with the highest scores to the vector
   for (int i=0; i<connections.size(); i++)
   {
      if (connections[i].score == highscore)
      {
         suggestion.push_back(connections[i].getid());
      }
   }
   score = highscore;
   clearbfs();
   return suggestion;
}

// call bfs
void Network::bfs(int start)
{
   deque<User> connectSearch; // hold depth for connections
   connections[start].depth = 0; // initialize dept
   
   // add start depth of connections vector to search queue
   connectSearch.push_back(connections[start]);
   // while queue is not empty
   while (connectSearch.size() != 0)
   {
      User head = connectSearch[0]; // initialize head
      connectSearch.pop_front(); 
      
      // go through the next 'head' users
      for (int i=0; i<(*head.getfriends()).size(); i++)
      {
         // if depth is not visited
         if (connections[(*head.getfriends())[i]].depth == -1)
         {
            // set predecessor to head's id and move on
            connections[(*head.getfriends())[i]].predecessor = head.getid();
            connections[(*head.getfriends())[i]].depth = head.depth+1;
            
            // add to search queue
            connectSearch.push_back(connections[(*head.getfriends())[i]]);
         }
      }
   }
}

// clear bfs depth and predecessor
void Network::clearbfs()
{
    for (int i=0; i<connections.size(); i++)
    {
       connections[i].depth = -1;
       connections[i].predecessor = -1;    
    }
}

// adjust bfs for disjointed groups
vector<int> Network::groupsbfs(int start)
{
   // add id of visited user to returned vector, which represents a set 
   vector<int> currGroup; // vector to hold groups
   deque<User> currSearch; // search queue   
   connections[start].depth = 0;
   currSearch.push_back(connections[start]);
   currGroup.push_back(start);
   
   while (currSearch.size() != 0)
   {
      User headUser = currSearch[0];
      currSearch.pop_front();
      
      for (int i=0; i<(*headUser.getfriends()).size(); i++)
      {
         if (connections[(*headUser.getfriends())[i]].depth == -1)
         {
            connections[(*headUser.getfriends())[i]].predecessor = 
            headUser.getid();
            connections[(*headUser.getfriends())[i]].depth = 
            headUser.depth+1;
            currSearch.push_back(connections[(*headUser.getfriends())[i]]);
            currGroup.push_back((*headUser.getfriends())[i]);
         }
      }
   } 
    return currGroup;
}
