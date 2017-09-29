/**************************************************************************
 * File name : social_network.cpp
 * Author    : Sarah Cheung
 * Email     : cheungsa@usc.edu
 * Date      : 4/25/17
 * Purpose   : Presents various menu options and features of a basic social 
               network of a single user
**************************************************************************/

#include "network.h"
#include "user.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
   Network snetwork; // construct social network
   
   if (argc != 2)
   {
      cout << "Invalid amount of inputs" << endl;
            
   }
   else
   {
      snetwork.read_friends(argv[1]);
   }
   string f1, f2, l1, l2; // first names and last names
   int option, year, zip;
   bool menu = true;
   
   while (menu)
   {
      cout << "Option 1: Add a User" << endl;
      cout << "Option 2: Add Friends" << endl;
      cout << "Option 3: Remove Friends" << endl;
      cout << "Option 4: Print Users" << endl;
      cout << "Option 5: List Friends" << endl;
      cout << "Option 6: Write to File" << endl;
      cout << "Option 7: Distance between Users" << endl;
      cout << "Option 8: List Disjoint Sets of Users" << endl;
      cout << "Option 9: Suggest Friends" << endl;
      cout << "Input any other number to exit program" << endl;
   
      cin >> option;

      // Option 1: add a user
      if (option == 1)
      {
         // read user name, birth year, and zip code
         cin >> f1 >> l1 >> year >> zip;
         snetwork.add_user(f1 + " " + l1, year, zip);
      }
   
      // Option 2: add a friend connection
      else if (option == 2)
      {
         // read two usernames to make friends
         cin >> f1 >> l1 >> f2 >> l2;
         snetwork.add_connection(f1 + " " + l1, f2 + " " + l2);
         // if user does not exist, print error message and continue
         if (snetwork.add_connection(f1 + " " + l1, f2 + " " + l2) == -1)
			{
				cout << "User does not exist" << endl;
				continue;
		   }
      }
      
      // Option 3: remove friend connection
      else if (option == 3)
      {
         // read two usernames to remove friends
         cin >> f1 >> l1 >> f2 >> l2;
         snetwork.remove_connection(f1 + " " + l1, f2 + " " + l2);
      
         // if user doesn't exist/users aren't friends, print error
         if(snetwork.remove_connection(f1 + " " + l1, f2 + " " + l2) == -1)
				cout << "User does not exist or users are not friends" << endl;
      }
      
      // Option 4: print users
      else if (option == 4)
      {
         cout << "ID      Name            Year    Zip" << endl;
         cout << 
            "==========================================================="
              << endl;
         // print list of users and their info in table format
         for (int i = 0; i < (*snetwork.getconnections()).size(); i++) 
         {
            cout << left 
            << setw(8) << (*snetwork.getconnections())[i].getid() 
            << setw(16) << (*snetwork.getconnections())[i].getname() 
            << setw(8) << (*snetwork.getconnections())[i].getyear()
            << setw(6) << (*snetwork.getconnections())[i].getzip() 
            << endl;
         }
         cout << endl;
      }     
   
      // Option 5: list friends
      else if (option == 5)
      {
         // print all the friends of user and their info in table format
         string selected;
         string selectF;
         string selectL;
      
         cin >> selectF >> selectL;

         selected = selectF + " " + selectL;
         int selectLoc = -1;
      
         for (int i=0; i < (*snetwork.getconnections()).size(); i++)
         {
            if ((*snetwork.getconnections())[i].getname() == selected)
            {
               selectLoc = i;
            }
         }
      
         // if user does not exist, print error message and continue
         if (selectLoc == -1)
         {
            cout << "User does not exist" << endl;
            continue;
         }
      
         int listSize = 
            (*(*snetwork.getconnections())[selectLoc].getfriends()).size();
         cout << "ID      Name            Year    Zip" << endl;
         cout << 
            "==========================================================="
              << endl;
         // print list of users and their info in table format
         for (int k = 0; k<listSize; k++) 
         {
            int temp = 
               (*(*snetwork.getconnections())[selectLoc].getfriends())[k];
               
            cout << left 
            << setw(8) << (*snetwork.getconnections())[temp].getid() 
            << setw(16) << (*snetwork.getconnections())[temp].getname() 
            << setw(8) << (*snetwork.getconnections())[temp].getyear()
            << setw(6) << (*snetwork.getconnections())[temp].getzip() 
            << endl;
         }
      }

      // Option 6: write to file
      else if (option == 6)
      {
         // write user database to filename in same format as input file
         string filename;
         cin >> filename;
         const char* writeto = filename.c_str();
         snetwork.write_friends(writeto);
      }

      // Option 7: distance between users
      else if (option == 7)
      {
         cin >> f1 >> l1 >> f2 >> l2;
         
         // get id's of users and store them into indexes
         int group1 = snetwork.get_id(f1 + " " + l1);
         int group2 = snetwork.get_id(f2 + " " + l2);
         
         // store shortest path between two users into a vector
         vector<int> path = snetwork.shortest_path(group1, group2);
         // if there is not a path present between two specified users
         if (path.size() != 1 || (f1 + " " + l1) == (f2 + " " + l2))
         {
            cout << "Distance: " << path.size()-1 << endl;
            for (int i=0; i<path.size(); i++)
            {
               cout << (*snetwork.getconnections())[path[i]].getname();
               if (i != path.size()-1)
               {
                  cout << " -> "; 
               }
            }
            cout << endl;            
         }
         else
         {
            cout << "None" << endl;
         }
      }
      
      // Option 8: disjoint sets
      else if (option == 8)
      {
         // compute how many disjoint sets of users are present in network
         // disjoint set - group of users isolated from other users
         // call groups function and store path into groups vector
         vector<vector<int> > groups = snetwork.groups();
         
         // output list of sets and the Users in each set
         for (int i=0; i<groups.size(); i++)
         {
            cout << "Set " << i+1 << " => ";
            for (int j=0; j<groups[i].size(); j++)
            {
               cout << (*snetwork.getconnections())[groups[i][j]].getname();
               if (j != groups[i].size()-1)
               {
                  cout << ", ";
               }
            }
            cout << endl;
         }                
      }                 
      
      // Option 9: friend suggestions
      else if (option == 9)
      {
         // compute list of users who are most likely suggestions for the
         // specified user to add as a friend      
         // 'strong' candidates are those who are at a relational distance
         // of 2 from the specified user        
         // score of potential new friend = number of common friends they 
         // would share with the specified user        
         // display all candidates with highest score (print score as well)
         
         int score = -1; // initialize score
         
         string suggestF_f, suggestF_l;
         cin >> suggestF_f >> suggestF_l;         
         
         // get id of current suggested user
         int id = snetwork.get_id(suggestF_f + " " + suggestF_l);
         
         // call suggest friends function and store into vector
         vector<int> suggestions = snetwork.suggest_friends(id, score);
         
         // if there are possible candidates
         if (suggestions.size() != 0)
         {
            cout << "The suggested friend(s) is/are: " << endl;
            for (int i=0; i<suggestions.size(); i++)
            {
               cout << "   " 
               << (*snetwork.getconnections())[suggestions[i]].getname()
               << setw(4) << '\t' << "Score:  " << score << endl;
            }           
         } 
         // if there are no possible cadidates
         else
         {
            cout << "None" << endl;
         }
      }
   
      // Exit program on any invalid command number (ex: -1, 7, 8, etc)
      else
      {
         menu = false;
      }
   }
   
   return 0;
}

