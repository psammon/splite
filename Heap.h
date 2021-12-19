#ifndef _HEAP_H_
#define _HEAP_H_
#include "Song.h"
//#include "Song"
#include <vector>
#include <iostream>

class Heap {
	private:
		std::vector<Song*> songs;
		

	public:
		Heap();
		//Heap(Song *array[], int cap);
		void insert(Song *s);
		Song* extractMax();
		void increaseKey(int index, int count);
		void maxHeapify(int i);
		//void showHeap();
		bool isEmpty();
		//void showHeap2();
		void showSongs();
};
#endif

