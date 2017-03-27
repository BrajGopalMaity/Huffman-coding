#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<limits>

using namespace std;

#define INT_MIN numeric_limits<int>::min();
		
typedef struct foheap{
	int data;
	int t;
	foheap *left;
	foheap *right;		
}foheap;

vector<foheap> fourHeap;

void fswap(int i, int j){
	foheap temp;
	temp = fourHeap[i];
	fourHeap[i] = fourHeap[j];
	fourHeap[j] = temp;
}

void fminHeapify(int i){
	int child[4],s;
	for(int j=3;j>=0;j--)
		child[3-j]=((i-3+1)*4)-j+3;
	s = i;
	for(int j=0;j<4;j++)
		if(child[j]<fourHeap.size() && fourHeap[child[j]].t<fourHeap[s].t)
			s = child[j];	
	if (s != i){
		fswap(s,i);
		fminHeapify(s);
		}				
}

void fbuildHeap(){
	int n = fourHeap.size();
	for(int i = n/4+3;i >= 3;i--)
		fminHeapify(i);
}

foheap fextractMin(){
	foheap min = fourHeap[3];
	fourHeap[3] = fourHeap[fourHeap.size()-1];
	fourHeap.pop_back();
	fminHeapify(3);		
	return min;
}

void fheapAgain(int i){
	int parent;
	if(i > 3){
		parent = ((i-1)/4)+3;
		if(fourHeap[parent].t > fourHeap[i].t){
			fswap(parent,i);
			fheapAgain(parent);
		}
	}
}

void fHeap(){
	string s;
	int k = 0;
	int min = INT_MIN;
	foheap *h1,*h2,temp,*root;
	for(int i=0;i<3;i++){
		temp.data = temp.t = min;
		temp.left = temp.right = NULL;
		fourHeap.push_back(temp);
		}
	ifstream ifile("freq_table.txt");
	if(!ifile.is_open())
		cout<<"Unable to open file\n";
	else{
		while(getline(ifile,s)){
			istringstream(s) >> temp.data >> temp.t;
			temp.left = temp.right = NULL;
			fourHeap.push_back(temp);
		}	 
		ifile.close();
		}
	fbuildHeap();
	while(fourHeap.size() != 4)
	{	
		h1 = new foheap();
		h2 = new foheap();
		*h1 = fextractMin();
		*h2 = fextractMin();
		temp.data = INT_MIN;
		temp.t = h1->t + h2->t;
		temp.left = h1;
		temp.right = h2;
		fourHeap.push_back(temp);
		fheapAgain(fourHeap.size()-1);		
	}		
}

