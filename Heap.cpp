#include <iostream>
#include "Heap.h"
#include <math.h>
#include <cassert>

using namespace std;

	Heap::Heap():songs(){
		
	}
	/*Heap::Heap(Song *array[], int cap){
		for(int i = 0; i <= cap; i++)
		       songs.push_back(array[i]);
	}*/
	void Heap::insert(Song *s){
		s->setHeapIndex(songs.size());
		songs.push_back(s);
	}
	void Heap::maxHeapify(int i){
		unsigned int left = (2*i) + 1;
		unsigned int  right = (2*i) + 2;
		int largest;
		Song *temp;
		if(left < songs.size() && songs.at(left)->getPlaycount() > songs.at(i)->getPlaycount())
			largest = left;
		else 
			largest = i;
		if(right < songs.size() && songs.at(right)->getPlaycount() > songs.at(largest)->getPlaycount())
			largest = right;
		if(largest != i)
		{
			temp = songs.at(i);
			songs.at(i) = songs.at(largest);
			songs.at(i)->setHeapIndex(i);
			songs.at(largest) = temp;
			songs.at(largest)->setHeapIndex(largest);
			maxHeapify(largest);
		}
	}
	Song* Heap::extractMax(){
		Song *max = songs.at(0);
		songs.at(0) = songs.at(songs.size() - 1);
		songs.pop_back();
		maxHeapify(0);
		return max;
	}
	void Heap::increaseKey(int index, int count){
		songs[index]->addPlaycount(count);
		Song *temp;
		while(index > 0 && songs[(index - 1)/2]->getPlaycount() < songs[index]->getPlaycount()){
			temp = songs[index];
			songs[index] = songs[(index - 1)/2];
			songs[index]->setHeapIndex(index);
			songs[(index - 1)/2] = temp;
			songs[(index-1)/2]->setHeapIndex((index - 1)/2);
			index = (index - 1)/2;
		}
	}
	void Heap::showSongs(){
		for(unsigned int i = 0; i < songs.size(); i++){
			cout << songs[i]->getTitle() << "  " << songs[i]->getPlaycount() << endl;
		}
	}
	bool Heap::isEmpty(){
		if(songs.size() == 0)
			return true;
		else
			return false;
	}

	/*void Heap::showHeap(){
		cout << *songs.at(0) << endl;
		cout << *songs.at(1) << *songs.at(2) << endl;
		cout << *songs.at(3) << *songs.at(4) << *songs.at(5) << *songs.at(6) << endl;
	}
	void Heap::showHeap2(){
		cout << *songs.at(0) << endl;
		cout << *songs.at(1) << *songs.at(2) << endl;
		cout << *songs.at(3) << *songs.at(4) << *songs.at(5) << endl;
	}
	int main(){
		Heap h;
		Song a,b,c,d,e,f,g;
		a.setTitle("apple");
		b.setTitle("ball");
		c.setTitle("cookie");
		d.setTitle("dong");
		e.setTitle("epic");
		f.setTitle("food");
		g.setTitle("ground");
		h.insert(&a);
		h.insert(&b);
		h.insert(&c);
		h.insert(&d);
		h.insert(&e);
		h.insert(&f);
		h.insert(&g);
		h.showHeap();
		h.increaseKey(f.getHeapIndex(), 5);
		h.showHeap();
		h.increaseKey(d.getHeapIndex(), 4);
		h.showHeap();
		h.increaseKey(g.getHeapIndex(), 100);
		h.showHeap();
		Song max;
		max = *h.extractMax();
		h.showHeap2();
		cout << max << endl;*/
	
