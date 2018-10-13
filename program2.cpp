#include <stdlib.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include "program2.h"
#include "Filereader.h"
#define DEBUG false

using namespace std;

int getArg0(string str){
	int i=0;
	while(i<str.length && str[i]!=' ')
		i++;
	string arg0 = str.substr(0, i);
	if(arg0.compare("findContestant")){
		return 1;
	} else if(arg0.compare("insertContestant")){
		return 2;
	} else if(arg0.compare("eliminateWeakest")){
		return 3;
	} else if(arg0.compare("earnPoints")){
		return 4;
	} else if(arg0.compare("losePoints")){
		return 5;
	} else if(arg0.compare("showContestants")){
		return 6;
	} else if(arg0.compare("showHandles")){
		return 7;
	} else if(arg0.compare("showLocation")){
		return 8;
	} else if(arg0.compare("crownWinner")){
		return 9;
	} else
		return -1;
}

int getArg1(string str){
	int i=0;
	while(i<str.length && str[i]!='<')
		i++;
	int j=i;
	while(j<str.length && str[j]!='>')
		j++;
	j-= ++i;
	if(i>=j)
		return -1;
	return stoi(str.substr(i, j));
}

int getArg2(string str){
	int i=0;
	while(i<str.length && str[i]!='<')
		i++;
	i++;
	while(i<str.length && str[i]!='<')
		i++;
	int j=i;
	while(j<str.length && str[j]!='>')
		j++;
	j-= ++i;
	if(i>=j)
		return -1;
	return stoi(str.substr(i, j));
}

int main(int argc, char** argv){
	if(DEBUG){
		for(int i=0; i<argc; i++){
			if(i!=0)
				cout << ' ';
			cout << argv[i];
		}
		cout << endl;
	}
	if(argc<3){
		cout << "Not enough arguments: argc=" << argc << endl;
		return 1;
	}
	ifstream ifp;
	ifp.open(argv[1]);
	if(!ipf.is_open()){
		cout << "Bad Input File Name: " << argv[1] << endl;
		return 1;
	}
	FileReader reader = FileReader(&ifp);
//														reading phase
	if(!reader.readFile()){
		cout << "Reader Failure" << endl;
		ifp.close();
		return 1;
	}
	ifp.close();
//														processing phase
	reader.start();
	int max_comps = atoi(reader.current());
	minheap heap;
	ofstream ofp;
	ofp.open(argv[2]);
	if(!opf.is_open()){
		cout << "Bad Output File Name: " << argv[2] << "; printing to STDOUT instead" << endl;
		heap = minheap(max_comps);
	} else {
		heap = minheap(max_comps, &opf);
	}
//														execution phase
	while(reader.next(){
		int arg0 = getArg0(reader.current());
		int arg1 = getArg1(reader.current());
		int arg2 = getArg2(reader.current());
		switch(arg0){
			case 1:
				if(arg1!=-1)
					heap.findContestant(arg1);
				else
					cout << "Parse Error (arg1): str=" << reader.current() << endl;
				break;
			case 2:
				if(arg1!=-1 && arg2!=-1)
					heap.insertContestant(arg1, arg2);
				else {
					if(arg1==-1)
						cout << "Parse Error (arg1): str=" << reader.current() << endl;
					if(arg2==-1)
						cout << "Parse Error (arg2): str=" << reader.current() << endl;
				}
				break;
			case 3:
				heap.eliminateWeakest();
				break;
			case 4:
				if(arg1!=-1 && arg2!=-1)
					heap.earnPoints(arg1, arg2);
				else {
					if(arg1==-1)
						cout << "Parse Error (arg1): str=" << reader.current() << endl;
					if(arg2==-1)
						cout << "Parse Error (arg2): str=" << reader.current() << endl;
				}
				break;
			case 5:
				if(arg1!=-1 && arg2!=-1)
					heap.losePoints(arg1, arg2);
				else {
					if(arg1==-1)
						cout << "Parse Error (arg1): str=" << reader.current() << endl;
					if(arg2==-1)
						cout << "Parse Error (arg2): str=" << reader.current() << endl;
				}
				break;
			case 6:
				heap.showContestants();
				break;
			case 7:
				heap.showHandles();
				break;
			case 8:
				if(arg1!=-1)
					heap.showLocation(arg1);
				else
					cout << "Parse Error (arg1): str=" << reader.current() << endl;
				break;
			case 9:
				heap.crownWinner();
				break;
			default:
				cout << "Parse Error (arg0): str=" << reader.current() << endl;
		}
	}
//														cleanup phase
	if(opf.is_open())
		ofp.close();
	return 0;
}