#include <stdlib.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include "Filereader.h"
#include "minheap.h"
#define DEBUG false

using namespace std;

int getArg0(string str){
	unsigned int i=0;
	while(i<str.length() && str[i]!=' ')
		i++;
	string arg0 = str.substr(0, i);
	if(arg0.compare("findContestant")==0){
		return 1;
	} else if(arg0.compare("insertContestant")==0){
		return 2;
	} else if(arg0.compare("eliminateWeakest")==0){
		return 3;
	} else if(arg0.compare("earnPoints")==0){
		return 4;
	} else if(arg0.compare("losePoints")==0){
		return 5;
	} else if(arg0.compare("showContestants")==0){
		return 6;
	} else if(arg0.compare("showHandles")==0){
		return 7;
	} else if(arg0.compare("showLocation")==0){
		return 8;
	} else if(arg0.compare("crownWinner")==0){
		return 9;
	} else
		return -1;
}

int getArg1(string str){
	unsigned int i=0;
	while(i<str.length() && str[i]!='<')
		i++;
	unsigned int j=i;
	while(j<str.length() && str[j]!='>')
		j++;
	if(++i>=j)
		return -1;
	return stoi(str.substr(i, j-i));
}

int getArg2(string str){
	unsigned int i=0;
	while(i<str.length() && str[i]!='<')
		i++;
	i++;
	while(i<str.length() && str[i]!='<')
		i++;
	unsigned int j=i;
	while(j<str.length() && str[j]!='>')
		j++;
	if(++i>=j)
		return -1;
	return stoi(str.substr(i, j-i));
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
	if(!ifp.is_open() && ifp.good()){
		cout << "Bad Input File Name: \"" << argv[1] << "\"" << endl;
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
	int max_comps = atoi(reader.current().c_str());
	minheap heap = minheap(max_comps);
	ofstream ofp;
	ofp.open(argv[2]);
	if(!ofp.is_open() || !ofp.good()){
		cout << "Bad Output File Name: \"" << argv[2] << "\"; printing to STDOUT instead" << endl;
	} else 
		heap.setOTP(&ofp);
//														execution phase
	while(reader.next()){
		int arg0 = getArg0(reader.current());
		int arg1 = getArg1(reader.current());
		int arg2 = getArg2(reader.current());
#if DEBUG
heap.printAll();
#endif
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
#if DEBUG
heap.printAll();
#endif
//														cleanup phase
	if(ofp.is_open())
		ofp.close();
	return 0;
}