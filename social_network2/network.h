/**************************************************************************
 * File name : network.h
 * Author    : Sarah Cheung
 * Email     : cheungsa@usc.edu
 * Date      : 4/25/17
 * Purpose   : Network class contains all the Users and implements the menu
               options
**************************************************************************/

#ifndef NETWORK_H
#define NETWORK_H
#include "user.h"
#include <vector>
#include <string>

class Network {
 public:
  Network(); // constructor
  ~Network(); // destructor
  int read_friends(const char* filename); // read users from file
  int write_friends(const char* filename); // write users to file
  void add_user(std::string username, int yr, int zipcode); // add user
  int add_connection(std::string name1, std::string name2); // make friends
  int remove_connection(std::string name1, std::string name2); // delete f
  int get_id(std::string username); // accept user name and return user ID
  vector<User>* getconnections(); // pointer access to vector
  
  vector<int> shortest_path(int from, int to); // find shortest path
  vector<vector<int> > groups(); // find disjointed groups
  vector<int> suggest_friends(int who, int& score); // suggest 'strong' f
  void bfs(int start); // call bfs
  void clearbfs(); // clear bfs depth and predecessor
  vector<int> groupsbfs(int start); // adjust bfs for disjointed groups

 private:
  vector<User> connections; // vector to contain friend and user connections  
};

#endif
