#ifndef _USER_H_
#define _USER_H_
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

class User {
    private:
        string username;
        
        
    public:
        User();
        User(string);
        User(const User& other);
        ~User();
        User& operator=(const User& other);
        bool operator==(const User& rhs);
        bool operator>(const User& rhs);
        bool operator<(const User& rhs);
        friend ostream& operator<<(ostream& os, const User& song);

        vector<User*> friends;
        int distance;
        string color;
        bool visited;
        
        int getDistance(){return distance;};
        void setDistance(int d){distance = d;};
        string getColor(){return color;};
        void setColor(string c){color = c;}; 
        string getUsername(){return username;};
        void setUsername(string u){username = u;};
        vector<User*> &getFriends(){return friends;};
        bool isVisisted(){return visited;};
        void setVisited(bool v){visited = v;};

        void showFriends();
        void addFriend(User& u);
        void removeFriend(User& u);

};
#endif
