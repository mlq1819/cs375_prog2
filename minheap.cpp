#include "minheap.h"
#ifndef DEBUG
#define DEBUG true
#endif

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
#if DEBUG
cout << "Output file Stream Set: " << this->output.good() << endl;
#endif
	return true;
}

bool minheap::isHeap(unsigned int i) const{
	unsigned int l = i*2+1;
	unsigned int r=l+1;
	bool l_ = l<this->heap.size();
	bool r_ = r<this->heap.size();
	if(l_ && this->heap[l] < this->heap[i])
		return false;
	if(r_ && this->heap[r] < this->heap[i])
		return false;
	if(l_ && r_)
		return isHeap(l) && isHeap(r);
	if(l_)
		return isHeap(l);
	if(r_)
		return isHeap(r);
	return true;
}

void minheap::heapify(unsigned int i){
	unsigned int smallest = i;
	unsigned int l = i*2+1;
	unsigned int r = l+1;
#if DEBUG
int num = 0;
cout << "\tTest " << ++num << "-" << i << endl;
#endif
	if(l<this->heap.size() && this->heap[l] < this->heap[i])
		smallest = l;
	if(r<this->heap.size() && this->heap[r] < this->heap[i])
		smallest = r;
	if(smallest!=i){
		this->swap(this->heap[smallest].id, this->heap[i].id);
#if DEBUG
cout << "\tTest " << ++num << "-" << i << endl;
#endif
		/*int p = (i-1)/2;
		if(p>=0 && this->heap[p] > this->heap[i]){
			this->swap(this->heap[p].id, this->heap[i].id);
			this->heapify((unsigned int)p);
		}*/
#if DEBUG
cout << "\tTest " << ++num << "-" << i << endl;
#endif
		this->heapify(smallest);
	}
}

void minheap::swap(int a, int b){
	int a_i = this->handle[a];
	int b_i = this->handle[b];
	contestant a_c = contestant(this->heap[a_i]);
	this->heap[a_i] = contestant(this->heap[b_i]);
	this->heap[b_i] = contestant(a_c);
	this->handle[a]=b_i;
	this->handle[b]=a_i;
}

bool minheap::findContestant(int id) const {
	if(output!=NULL && output->is_open())
		(* this->output) << "findContestant <" << id << ">" << endl;
	else
		cout << "findContestant <" << id << ">" << endl;
	if(((unsigned int) id)<this->handle.size()){
		int i = this->handle[id];
		if(i!=-1){
			int p = this->heap[i].points;
			if(output!=NULL && output->is_open()){
				(* this->output) << "Contestant <" << id << "> is in the extended heap with score <" << p << ">." << endl;
			} else
				cout << "Contestant <" << id << "> is in the extended heap with score <" << p << ">." << endl;
			return true;
		}
	}
	if(output!=NULL && output->is_open())
		(* this->output) << "Contestant <" << id << "> is not in the extended heap." << endl;
	else
		cout << "Contestant <" << id << "> is not in the extended heap." << endl;
	return false;
}

bool minheap::insertContestant(int id, int score){
	if(output!=NULL && output->is_open())
		(* this->output) << "insertContestant <" << id << "> <" << score << ">" << endl;
	else
		cout << "insertContestant <" << id << "> <" << score << ">" << endl;
	if(this->num_const==this->max_size){
		if(output!=NULL && output->is_open())
			(* this->output) << "Contestant <" << id << "> could not be inserted because the extended heap is full." << endl;
		else
			cout << "Contestant <" << id << "> could not be inserted because the extended heap is full." << endl;
		this->shrink_to_fit();
		return false;
	}
	if(((unsigned int) id)<this->handle.size() && this->handle[id]!=-1){
		if(output!=NULL && output->is_open())
			(* this->output) << "Contestant <" << id << "> is already in the extended heap: cannot insert." << endl;
		else
			cout << "Contestant <" << id << "> is already in the extended heap: cannot insert." << endl;
		return false;
	}
	while(this->handle.size()<=((unsigned int) id)){
		this->handle.push_back(-1);
	}
	contestant c = contestant(id, score);
	this->handle[id]=this->heap.size();
	this->heap.push_back(c);
	this->num_const++;
	if(output!=NULL && output->is_open())
		(* this->output) << "Contestant <" << id << "> inserted with initial score <" << score << ">." << endl;
	else
		cout << "Contestant <" << id << "> inserted with initial score <" << score << ">." << endl;
	this->heapify(0);
	return true;
}

bool minheap::eliminateWeakest(bool print){
	if(print){
		if(output!=NULL && output->is_open())
			(* this->output) << "eliminateWeakest" << endl;
		else
			cout << "eliminateWeakest" << endl;
	}
	if(this->heap.size()==0){
		if(print){
			if(output!=NULL && output->is_open())
				(* this->output) << "No contestant can be eliminated since the extended heap is empty." << endl;
			else
				cout << "No contestant can be eliminated since the extended heap is empty." << endl;
		}
		return false;
	}
	int id = this->heap[0].id;
	int score = this->heap[0].points;
#if DEBUG
this->printAll();
#endif
	this->swap(this->heap[0].id, this->heap[this->heap.size()-1].id);
#if DEBUG
this->printAll();
#endif
	this->heap.pop_back();
	this->handle[id]=-1;
	this->num_const--;
	if(print){
		if(output!=NULL && output->is_open())
			(* this->output) << "Contestant <" << id << "> with current lowest score <" << score << "> eliminated." << endl;
		else
			cout << "Contestant <" << id << "> with current lowest score <" << score << "> eliminated." << endl;
	}
#if DEBUG
this->printAll();
#endif
	this->heapify(0);
#if DEBUG
this->printAll();
#endif
	return true;
}

bool minheap::earnPoints(int id, int points){
	if(output!=NULL && output->is_open())
		(* this->output) << "earnPoints <" << id << "> <" << points << ">" << endl;
	else
		cout << "earnPoints <" << id << "> <" << points << ">" << endl;
	if(((unsigned int) id)<this->handle.size()){
		int i = this->handle[id];
		if(i!=-1){
			this->heap[i].points+=points;
			if(output!=NULL && output->is_open())
				(* this->output) << "Contestant <" << id << ">'s score increased by <"<<  points << "> points to <" << this->heap[i].points <<  ">." << endl;
			else
				cout << "Contestant <" << id << ">'s score increased by <" << points << "> points to <" << this->heap[i].points <<  ">." << endl;
			return true;
		}
	}
	if(output!=NULL && output->is_open())
		(* this->output) << "Contestant <" << id << "> is not in the extended heap." << endl;
	else
		cout << "Contestant <" << id << "> is not in the extended heap." << endl;
	return false;
}

bool minheap::losePoints(int id, int points){
	if(output!=NULL && output->is_open())
		(* this->output) << "losePoints <" << id << "> <" << points << ">" << endl;
	else
		cout << "losePoints <" << id << "> <" << points << ">" << endl;
	if(((unsigned int) id)<this->handle.size()){
		int i = this->handle[id];
		if(i!=-1){
			this->heap[i].points-=points;
			if(output!=NULL && output->is_open())
				(* this->output) << "Contestant <" << id << ">'s score decreased by <" << points << "> points to <" << this->heap[i].points <<  ">." << endl;
			else
				cout << "Contestant <" << id << ">'s score decreased by <" << points << "> points to <" << this->heap[i].points <<  ">." << endl;
			return true;
		}
	}
	if(output!=NULL && output->is_open())
		(* this->output) << "Contestant <" << id << "> is not in the extended heap." << endl;
	else
		cout << "Contestant <" << id << "> is not in the extended heap." << endl;
	return false;
}

void minheap::showContestants() const {
	if(output!=NULL && output->is_open())
		(* this->output) << "showContestants" << endl;
	else
		cout << "showContestants" << endl;
	if(output!=NULL && output->is_open()){
		for(unsigned int i=0; i<this->heap.size(); i++){
			(* this->output) << "Contestant <" << this->heap[i].id << "> is in extended heap location <" << i+1 << "> with score <" << this->heap[i].points << ">." << endl;
		}
	} else {
		for(unsigned int i=0; i<this->heap.size(); i++){
			cout << "Contestant <" << this->heap[i].id << "> is in extended heap location <" << i+1 << "> with score <" << this->heap[i].points << ">." << endl;
		}
	}
}

void minheap::showHandles() const {
	if(output!=NULL && output->is_open())
		(* this->output) << "showHandles" << endl;
	else
		cout << "showHandles" << endl;
	if(output!=NULL && output->is_open()){
		for(unsigned int i=1; i<this->handle.size(); i++){
			if(this->handle[i]==-1)
				(* this->output) << "There is no Contestant <" << i << "> in the extended heap: handle[<" << i << ">]=-1." << endl;
			else
				(* this->output) << "Contestant <" << i << "> stored in extended heap location <" << this->handle[i]+1 << ">." << endl;
		}
	} else {
		for(unsigned int i=1; i<this->handle.size(); i++){
			if(this->handle[i]==-1)
				cout << "There is no Contestant <" << i << "> in the extended heap: handle[<" << i << ">]=-1." << endl;
			else
				cout << "Contestant <" << i << "> stored in extended heap location <" << this->handle[i]+1 << ">." << endl;
		}
	}
}

bool minheap::showLocation(int id) const{
	if(output!=NULL && output->is_open())
		(* this->output) << "showLocation <" << id << ">" << endl;
	else
		cout << "showLocation <" << id << ">" << endl;
	if(((unsigned int) id)<this->handle.size()){
		int i = this->handle[id];
		if(i!=-1){
			if(output!=NULL && output->is_open())
				(* this->output) << "Contestant <" << id << "> stored in extended heap location <" << i+1 << ">." << endl;
			else
				cout << "Contestant <" << id << "> stored in extended heap location <" << i+1 << ">." << endl;
			return true;
		}
	}
	if(output!=NULL && output->is_open())
		(* this->output) << "There is no contestant <" << id << "> in the extended heap: handle[<" << id << ">]=-1." << endl;
	else
		cout << "There is no contestant <" << id << "> in the extended heap: handle[<" << id << ">]=-1." << endl;
	return false;
}

bool minheap::crownWinner(){
	if(output!=NULL && output->is_open())
		(* this->output) << "crownWinner" << endl;
	else
		cout << "crownWinner" << endl;
	while(this->num_const>1){
		this->eliminateWeakest(false);
	}
	if(output!=NULL && output->is_open())
		(* this->output) << "Contestant <" << this->heap[0].id << "> wins with score <" << this->heap[0].points << ">!" << endl;
	else
		cout << "Contestant <" << this->heap[0].id << "> wins with score <" << this->heap[0].points << ">!" << endl;
	return true;
}

void minheap::printAll() const {
	cout << "\tHeap" << endl;
	for(unsigned int i=0; i<this->heap.size(); i++)
		cout << "\t\theap[" << i << "]=<" << this->heap[i].id << "," << this->heap[i].points << ">" << endl;
	cout << "\tHandle" << endl;
	for(unsigned int i=1; i<this->handle.size(); i++){
		cout << "\t\thandle[" << i << "]=" << this->handle[i] << endl;
		if(this->handle[i]!=-1 && ((unsigned int)this->heap[this->handle[i]].id)!=i)
			cout << "\t\tWARNING - handle does not match heap - WARNING" << endl;
	}
}