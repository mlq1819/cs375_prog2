#ifndef MQ_MINHEAP_H
#define MQ_MINHEAP_H
#include <stdlib.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

class contestant{
	public:
		contestant(int id, int points){this->id=id; this->points=points;};
		int id;
		int points;
		bool operator<(contestant o) const {return this->points<o.points;};
		bool operator<=(contestant o) const {return this->points<=o.points;};
		bool operator>(contestant o) const {return this->points>o.points;};
		bool operator>=(contestant o) const {return this->points>=o.points;};
		bool operator==(contestant o) const {return this->points==o.points;};
		bool operator!=(contestant o) const {return this->points!=o.points;};
};

class minheap{
	private:
		std::vector<int> handle;
		std::vector<contestant> heap;
		void heapify();
		void swap(int, int);
		std::ofstream * output;
		int max_size;
		int num_const;
	public:
		minheap(int max_size);
		minheap(int max_size, std::ofstream * output);
		contestant operator[](int i) const {return this->heap[this->handle[i]]};
		void shrink_to_fit(){this->heap.shrink_to_fit(); this->handle.shrink_to_fit();};
		
		bool findContestant(int) const;
		bool insertContestant(int, int);
		bool eliminateWeakest(){return this->eliminateWeakest(true);};
		bool eliminateWeakest(bool);
		bool earnPoints(int, int);
		bool losePoints(int, int);
		void showContestants() const;
		void showHandles() const;
		bool showLocation(int) const;
		bool crownWinner();
};

#endif