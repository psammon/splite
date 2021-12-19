#include "Song.h"
#include "Parser.h"
#include "User.h"
#include "BSTree.h"
#include "BST.h"
#include "Heap.h"
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
#include <list>

using namespace std;


std::vector<std::string> getSongFilenames(std::string inputdir_name) {
	if (inputdir_name == "") return std::vector<std::string>();
	// cite - https://www.delftstack.com/howto/cpp/how-to-get-list-of-files-in-a-directory-cpp/
	DIR* dir;
	struct dirent* dir_entry;
	std::vector<std::string> filenames;
	if ((dir = opendir(inputdir_name.c_str())) != nullptr) {
		while ((dir_entry = readdir(dir)) != nullptr) {
			// only adding txt files.
			if (std::string(dir_entry->d_name).find(".txt") != std::string::npos) {
				filenames.push_back(dir_entry->d_name);
			}
		}
		closedir(dir);
	}
	return filenames;
}

void ResetEFN(User &s){
	queue<User*> q;

	s.visited = false;
	s.color = "white";
	s.distance = 0;
	
	User *sp = &s;
	q.push(sp);

	while(!q.empty()){
		User *u = q.front();
		q.pop();

	//	cout << *u;

		vector<User*>::iterator iter;
        for(iter = u->friends.begin(); iter != u->friends.end(); iter++){
			//cout << *(u->getFriends()[i]) << endl;
			if((*iter)->color == "black"){
				(*iter)->color = "white";
				(*iter)->distance = 9999;
				(*iter)->visited = false;

				q.push((*iter));
			}
		}
		u->color = "white";
	}

}


void UpdateEFN(int k, User &s){
	queue<User*> q;

	s.visited = true;
	s.color = "gray";
	s.distance = 0;
	
	User *sp = &s;
	q.push(sp);

	while(!q.empty()){
		User *u = q.front();
		q.pop();

		if(u->distance == k+1) return;

	//	cout << *u;

		vector<User*>::iterator iter;
        for(iter = u->friends.begin(); iter != u->friends.end(); iter++){
			//cout << *(u->getFriends()[i]) << endl;
			if((*iter)->color == "white"){
				(*iter)->color = "gray";
				(*iter)->distance = u->distance + 1;
				(*iter)->visited = true;

				q.push((*iter));
			}
		}
		u->color = "black";
	}

}


int main(int argc, char* argv[]) {
	std::string inputdir_name;

	//Graph of Users
	//BST and Heap for system
	//BST for primary user
	//Primary user

	if (argc != 2) {
		std::cout << "error: invalid number of commandline arguments" << std::endl;
		exit(1);
	}

	inputdir_name = argv[1];
	vector<string> song_files = getSongFilenames(inputdir_name);
	vector<Song> system(100); //TO-DO: change to heap + BST
	vector<std::string>::iterator iter;
	Heap heap;
	BST<string, Song*>* sysBST = new BST<string, Song*>();
	
	for(iter = song_files.begin(); iter != song_files.end(); iter++){
		Song s;
		stringstream input_filepath;
		input_filepath << inputdir_name << "/" << *iter;
		s.readSongInfo(input_filepath.str());
		cout << s;
		system.push_back(s);
		heap.insert(&system[system.size()-1]);
		sysBST->AddLeaf(system[system.size() - 1].getTitle(), &system[system.size() - 1]);
	}


//============================================================================================
//instantiate parser arguments
	std::string line;
    string op;
    string arg1;
    string arg2;
    string arg3;

	BSTree<string>* primLib = new BSTree<string>();	
	//BSTree<Song*>* sysBST = new BSTree<Song*>();
	User primary_user("primary_user");
	BSTree<User> *g = new BSTree<User>();
	int K = 1;
	g->AddLeaf(primary_user);	


	

	//loop user input while operation is not exit
    while(op.compare("exit") != 0) {
		//------------------------------------------
		getline(cin, line);
        Parser command(line);
        op = command.getOperation();
        arg1 = command.getArg1();
        arg2 = command.getArg2();
		arg3 = command.getArg3();
		//------------------------------------------


		if(op == "add" && arg1 == "user"){
		//instantiate user with username arg2 and add vertex to graph
	//	if(g->returnNodeValue(primary_user).color == "black")
	//		ResetEFN(k, g->returnNodeValue(primary_user));
		User u(arg2);
		g->AddLeaf(u);

		} else if (op == "friend"){
		//create edge between users <username1>(arg1) <username2>(arg2)
	//	if(g->returnNodeValue(primary_user).color == "black")
	//		ResetEFN(K, g->returnNodeValue(primary_user));
		User u1(arg1), u2(arg2);
		if(g->search(u1) != NULL && g->search(u2) != NULL){
            g->returnNodeValue(u1).addFriend(g->returnNodeValue(u2));
            g->returnNodeValue(u2).addFriend(g->returnNodeValue(u1));
        }
        else{
            cout << "Either one of or both of the inputted users do not exist\n";
        }
		} else if (op == "unfriend"){
		//delete edge between two users with names arg1 and arg2
		//if(g->returnNodeValue(primary_user).color == "black")
		//	ResetEFN(K, g->returnNodeValue(primary_user));
		User u1(arg1), u2(arg2);
		if(g->search(u1) != NULL && g->search(u2) != NULL){
			g->returnNodeValue(u1).removeFriend(g->returnNodeValue(u2));
			g->returnNodeValue(u2).removeFriend(g->returnNodeValue(u1));
		}
		else{
			cout << "Either one of or both of the inputted users do not exist\n";
		}

		} else if (op == "listen"){//listen <username> <song title> [<n>]
		
		UpdateEFN(K, g->returnNodeValue(primary_user));

		User u(arg1);
		if(g->search(u) != NULL){
			if(g->returnNodeValue(u).color == "black"){//if user with <user name> is in EFN after update
				int foundIndex;
		//TODO
		//search for song in system library bst and insert heap index into found index
		//
				Song find;
				find.setTitle(arg2);
				if(sysBST->search(arg2) != NULL){
					foundIndex = sysBST->returnNodeValue(arg2)->getHeapIndex();
					heap.increaseKey(foundIndex, stoi(arg3));
				}
				else{
					cout << "This song doesn't exist in the system library\n";
				}
			} else {//user not in EFN:
				cout << "User isn't within EFN\n";

			}
		}
		else{
			cout << "User doesn't exist\n";
		}

		ResetEFN(g->returnNodeValue(primary_user));

		} else if (op == "set" && arg1 == "radius"){
		//Set K to arg2
		
		//ResetEFN(K, g->returnNodeValue(primary_user));
		K = stoi(arg2);

			
		} else if (op == "recommend"){
		//TODO
			for(int i = 0; i < stoi(arg1); i++){
				if(!heap.isEmpty()){
					Song max;
					max = *heap.extractMax();
					sysBST->removeNode(max.getTitle());
					primLib->AddLeaf(max.getTitle());
				}
			}
		} else if (op == "remove" && arg1 == "song"){
			Song s;
			string title;
			if(primLib->search(arg2) != NULL){
				title = primLib->search(arg2)->key;
				primLib->removeNode(title);
				s.setTitle(title);
				system.push_back(s);
				heap.insert(&system[system.size() - 1]);
				sysBST->AddLeaf(system[system.size() - 1].getTitle(), &system[system.size() - 1]);
			}
			else{
				cout << "This song doesn't exist in the primary users library.\n";
			}

			
		} else if (op == "show"){
			if(arg1 == "songs"){
				primLib->printInOrder();

			} else if(arg1 == "friends"){
				if(g->search(arg2) != NULL){
					g->returnNodeValue(arg2).showFriends();
				}
				else{
					cout << "User doesn't exist\n";
				}
			} else if(arg1 == "system"){
				heap.showSongs();

			} else {
				cout << "Bad Input: Use 'show songs' or 'show friends <username>' or 'show system'" << endl;
			}

		} else if (op == "exit"){
			delete sysBST;
			delete primLib;
			delete g;
			return 0;

		} else{
			cout << "bad command input" << endl;
		}

	}

}
