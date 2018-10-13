#include "minheap.h"

using namespace std;

minheap::minheap(int max_size){
	this->handle=vector<int>();
	this->heap=vector<contestant>();
	this->output=NULL;
	this->max_size=max_size;
	this->num_const=0;
}

bool minheap::setOTP(ofstream * output){
	if(this->output==NULL)
		return false;
	this->output=output;
	return true;
}

void minheap::heapify(unsigned int i){
	unsigned int smallest = i;
	unsigned int l = i*2+1;
	unsigned int r = l+1;
	if(l<this->heap.size() && this->heap[l] < this->heap[i])
		smallest = l;
	if(r<this->heap.size() && this->heap[r] < this->heap[i])
		smallest = r;
	if(smallest!=i){
		this->swap(smallest, i);
		int p = (i-1)/2;
		if(p>=0 && this->heap[p] > this->heap[i])
			this->heapify((unsigned int)p);
		this->heapify(smallest);
	}
}

void minheap::swap(int a, int b){
	int a_i = this->handle[a];
	int b_i = this->handle[b];
	contestant a_c = this->heap[a_i];
	this->heap[a_i] = this->heap[b_i];
	this->heap[b_i] = a_c;
	this->handle[a]=b_i;
	this->handle[b]=a_i;
}

bool minheap::findContestant(int id) const {
	if(id<this->handle.size()){
		int i = this->handle[id];
		if(i!=-1){
			int p = this->heap[i].points;
			if(output!=NULL && output->is_open()){
				(* this->output) << "Contestant " << id << " is in the extended heap with score " << p << "." << endl;
			} else
				cout << "Contestant " << id << " is in the extended heap with score " << p << "." << endl;
			return true;
		}
	}
	if(output!=NULL && output->is_open())
		(* this->output) << "Contestant " << id << " is not in the extended heap." << endl;
	else
		cout << "Contestant " << id << " is not in the extended heap." << endl;
	return false;
}

bool minheap::insertContestant(int id, int score){
	if(this->num_const==this->max_size){
		if(output!=NULL && output->is_open())
			(* this->output) << "Contestant " << id << " could not be inserted because the extended heap is full." << endl;
		else
			cout << "Contestant " << id << " could not be inserted because the extended heap is full." << endl;
		this->shrink_to_fit();
		return false;
	}
	if(id<this->handle.size() && this->handle[id]!=-1){
		if(output!=NULL && output->is_open())
			(* this->output) << "Contestant " << id << " is already in the extended heap: cannot insert." << endl;
		else
			cout << "Contestant " << id << " is already in the extended heap: cannot insert." << endl;
		return false;
	}
	while(this->handle.size()<=id){
		this->handle.push_back(-1);
	}
	contestant c = contestant(id, score);
	this->handle[id]=this->heap.size();
	this->heap.push_back(c);
	if(output!=NULL && output->is_open())
		(* this->output) << "Contestant " << id << " inserted with initial score " << score << "." << endl;
	else
		cout << "Contestant " << id << " inserted with initial score " << score << "." << endl;
	this->heapify(0);
	return true;
}

bool minheap::eliminateWeakest(bool print){
	if(this->heap.size()==0){
		if(print){
			if(output!=NULL && output->is_open())
				(* this->output) << "No contestant can be eliminated since the extended heap is empty." << endl;
			else
				cout << "No contestant can be eliminated since the extended heap is empty." << endl;
		}
		return false;
	}
	this->swap(0, this->heap.size()-1);
	contestant c = contestant(this->heap[this->heap.size()-1]);
	this->heap.pop_back();
	this->handle[c.id]=-1;
	this->num_const--;
	if(print){
		if(output!=NULL && output->is_open())
			(* this->output) << "Contestant " << c.id << " with current lowest score " << c.points << " eliminated." << endl;
		else
			cout << "Contestant " << c.id << " with current lowest score " << c.points << " eliminated." << endl;
	}
	this->heapify(0);
	return true;
}

bool minheap::earnPoints(int id, int points){
	if(id<this->handle.size()){
		int i = this->handle[id];
		if(i!=-1){
			this->heap[i].points+=points;
			if(output!=NULL && output->is_open())
				(* this->output) << "Contestant " << id << "'s score increased by "<<  points << " points to " << this->heap[i].points <<  "." << endl;
			else
				cout << "Contestant " << id << "'s score increased by " << points << " points to " << this->heap[i].points <<  "." << endl;
			return true;
		}
	}
	if(output!=NULL && output->is_open())
		(* this->output) << "Contestant " << id << " is not in the extended heap." << endl;
	else
		cout << "Contestant " << id << " is not in the extended heap." << endl;
	return false;
}

bool minheap::losePoints(int id, int points){
	if(id<this->handle.size()){
		int i = this->handle[id];
		if(i!=-1){
			this->heap[i].points-=points;
			if(output!=NULL && output->is_open())
				(* this->output) << "Contestant " << id << "'s score decreased by " << points << " points to " << this->heap[i].points <<  "." << endl;
			else
				cout << "Contestant " << id << "'s score decreased by " << points << " points to " << this->heap[i].points <<  "." << endl;
			return true;
		}
	}
	if(output!=NULL && output->is_open())
		(* this->output) << "Contestant " << id << " is not in the extended heap." << endl;
	else
		cout << "Contestant " << id << " is not in the extended heap." << endl;
	return false;
}

void minheap::showContestants() const {
	if(output!=NULL && output->is_open()){
		for(int i=0; i<this->heap.size(); i++){
			(* this->output) << "Contestant " << this->heap[i].id << " is in extended heap location " << i << " with score " << this->heap[i].points << "." << endl;
		}
	} else {
		for(int i=0; i<this->heap.size(); i++){
			cout << "Contestant " << this->heap[i].id << " is in extended heap location " << i << " with score " << this->heap[i].points << "." << endl;
		}
	}
}

void minheap::showHandles() const {
	if(output!=NULL && output->is_open()){
		for(int i=0; i<this->handle.size(); i++){
			if(this->handle[i]==-1)
				(* this->output) << "There is no Contestant " << i << " in the extended heap: handle[" << i << "]=-1." << endl;
			else
				(* this->output) << "Contestant " << i << " stored in extended heap location " << this->handle[i] << "." << endl;
		}
	} else {
		for(int i=0; i<this->handle.size(); i++){
			if(this->handle[i]==-1)
				cout << "There is no Contestant " << i << " in the extended heap: handle[" << i << "]=-1." << endl;
			else
				cout << "Contestant " << i << " stored in extended heap location " << this->handle[i] << "." << endl;
		}
	}
}

bool minheap::showLocation(int id) const{
	if(id<this->handle.size()){
		int i = this->handle[id];
		if(i!=-1){
			if(output!=NULL && output->is_open())
				(* this->output) << "Contestant " << id << " stored in extended heap location " << i << "." << endl;
			else
				cout << "Contestant " << id << " stored in extended heap location " << i << "." << endl;
			return true;
		}
	}
	if(output!=NULL && output->is_open())
		(* this->output) << "There is no contestant " << id << " in the extended heap: handle[" << id << "]=-1." << endl;
	else
		cout << "There is no contestant " << id << " in the extended heap: handle[" << id << "]=-1." << endl;
	return false;
}

bool minheap::crownWinner(){
	while(this->num_const>1){
		this->eliminateWeakest(false);
	}
	if(output!=NULL && output->is_open())
		(* this->output) << "Contestant " << this->heap[0].id << " wins with score " << this->heap[0].points << "!" << endl;
	else
		cout << "Contestant " << this->heap[0].id << " wins with score " << this->heap[0].points << "!" << endl;
	return true;
}