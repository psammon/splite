#include <iostream>
#include <string>
#include <fstream>
#include "Song.h"

using namespace std;

    Song::Song(){
        title = "";
	    playcount = 0;
    }
    Song::Song(const Song& other){
        title = other.title;
	    playcount = other.playcount;
    }
    Song& Song::operator=(const Song& other){
	    if(this != &other){
		    title = other.title;
        }
	    return *this;
    }
    int Song::getPlaycount(){
	return playcount;
    }
    bool Song::operator==(const Song& rhs){
        return (this->title == rhs.title);
    }
    bool Song::operator>(const Song& rhs){
        return (this->title > rhs.title);
    }
    bool Song::operator<(const Song& rhs){
        return (this->title < rhs.title);
    }
    ostream& operator<<(ostream& os, const Song& song){
        Song s = song;
        if(s.title != "")
            os << s.title << endl;
        return os;
        
    }

    void Song::readSongInfo(string input_filepath){
        ifstream infile(input_filepath);
        
        if(infile.fail()){
            cerr << "error opening infile" << endl;
            exit(1);
        }
        string line;
        getline(infile, line);
        title = line;

        infile.close();

    }
    void Song::addPlaycount(int count) {
	    playcount = playcount + count;
    }
