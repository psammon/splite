#include <iostream>
#include <string>
#include <fstream>
#include "User.h"

using namespace std;

    User::User(){
        username = "";
        distance = 9999;
        color = "white";
        visited = false;
    }
    User::User(string un){
        username = un;
        distance = 9999;
        color = "white";
        visited = false;
    }
    User::User(const User& other){
        username = other.username;
        friends = other.friends;
        distance = other.distance;
        color = other.color;
    }
    
    User::~User(){
	    username = "";
        distance = 9999;
        color = "white";
	    friends.clear();
    }
    
    User& User::operator=(const User& other){
	    if(this != &other){
		    username = other.username;
            friends = other.friends;
            distance = other.distance;
            color = other.color;
        }
	    return *this;
    }
    bool User::operator==(const User& rhs){
        return (this->username == rhs.username);
    }
    bool User::operator>(const User& rhs){
        return (this->username > rhs.username);
    }
    bool User::operator<(const User& rhs){
        return (this->username < rhs.username);
    }
    ostream& operator<<(ostream& os, const User& u){        
        os << u.username << endl;
        return os; 
    }

    void User::showFriends(){
        for(unsigned int i = 0; i < friends.size(); i++){
            cout << *friends[i];
        }
    }
    void User::addFriend(User& u){
        for(unsigned int i = 0; i < friends.size(); i++){
            if(*friends[i] == u){
                cout << "already friends" << endl;
                return;
            }
        }
   //     friends.resize(friends.size()+1);
        User* temp = &u;
        this->friends.push_back(temp);
        
    }
    void User::removeFriend(User& u){
        vector<User*>::iterator iter;
        for(iter = friends.begin(); iter != friends.end(); ){
            if(*(*iter) == u){
                iter = friends.erase(iter);
            } else{
                iter++;
            }
        }
    }
  /*  
int main()
{
    // Graph with 7 nodes and 6 edges.
    User pu("primary_user");
    User u1("user1");
    User u2("user2");
    User u3("user3");
    User u4("user4");
          
    // The Graph vector
    vector<User> g;
      
    pu.addFriend(u1);
    pu.addFriend(u2);
    pu.addFriend(u3);
    pu.addFriend(u4);
    u1.addFriend(u2);
    u2.addFriend(u3);
    pu.removeFriend(u3);
    pu.addFriend(u2);
  
    pu.showFriends();
  
    return 0;
}

*/
    
    


