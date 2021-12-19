#ifndef _SONG_H_
#define _SONG_H_
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Song {
    private:
        string title;
        int playcount;
        int index;

        
    public:
        Song();
        Song(const Song& other);
        Song& operator=(const Song& other);
        bool operator==(const Song& rhs);
        bool operator>(const Song& rhs);
        bool operator<(const Song& rhs);
        friend ostream& operator<<(ostream& os, const Song& song);

        string getTitle(){return title;};
        void setTitle(string t){title = t;};
        void play(){playcount++;};
	    int getPlaycount();
	    int getHeapIndex(){return index;};
	    void setHeapIndex(int i){index = i;};
	    void addPlaycount(int count);

        void readSongInfo(string input_filepath);

};
#endif
