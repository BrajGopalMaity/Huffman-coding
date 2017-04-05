#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<limits>

using namespace std;

#define INT_MIN numeric_limits<int>::min();
		
typedef struct foheap{						//structure variable for 4-way minheap
	int data;
	int t;
	foheap *left;
	foheap *right;		
}foheap;

vector<foheap> fourHeap;					//array to hold fourway minheap structure

void fswap(int i, int j){					//swap function to swap two structure nodes in 4-way minheap
	foheap temp;
	temp = fourHeap[i];
	fourHeap[i] = fourHeap[j];
	fourHeap[j] = temp;
}

void fminHeapify(int i){					//minHeapify function to heapify a given array into 4-way minHeap 
	int child[4],s;
	for(int j=3;j>=0;j--)					//get four children of parent
		child[3-j]=((i-3+1)*4)-j+3;
	s = i;
	for(int j=0;j<4;j++)					
		if(child[j]<fourHeap.size() && fourHeap[child[j]].t<fourHeap[s].t) //get minimum of 4 children and parent
			s = child[j];	
	if (s != i){						//if parent is not minimum swap it
		fswap(s,i);
		fminHeapify(s);
		}				
}

void fbuildHeap(){						//function to buid heap
	int n = fourHeap.size();
	for(int i = n/4+3;i >= 3;i--)
		fminHeapify(i);
}

foheap fextractMin(){						//extract the minimum element of the heap 
	foheap min = fourHeap[3];
	fourHeap[3] = fourHeap[fourHeap.size()-1];
	fourHeap.pop_back();
	fminHeapify(3);		
	return min;
}

void fheapAgain(int i){						//heapify again after inserting an element
	int parent;
	if(i > 3){
		parent = ((i-4)/4)+3;
		if(fourHeap[parent].t > fourHeap[i].t){
			fswap(parent,i);
			fheapAgain(parent);
		}
	}
}

void fHeap(){							//main function to implement 4-way heap
	string s;
	int k = 0;
	int min = INT_MIN;
	foheap *h1,*h2,temp,*root;
	for(int i=0;i<3;i++){					//insert 3 dummy variables
		temp.data = temp.t = min;
		temp.left = temp.right = NULL;
		fourHeap.push_back(temp);
		}
	ifstream ifile("freq_table.txt");
	if(!ifile.is_open())
		cout<<"Unable to open file\n";
	else{
		while(getline(ifile,s)){			
			istringstream(s) >> temp.data >> temp.t;//take an entry from the file and insert it into the heap array
			temp.left = temp.right = NULL;
			fourHeap.push_back(temp);
		}	 
		ifile.close();
		}
	fbuildHeap();
	while(fourHeap.size() != 4)				//extract least frequency values 
	{	
		h1 = new foheap();
		h2 = new foheap();
		*h1 = fextractMin();
		*h2 = fextractMin();
		temp.data = INT_MIN;				//insert dummy data in the new node 
		temp.t = h1->t + h2->t;				//add least frequency values into the new node
		temp.left = h1;					//make those values child of the new node
		temp.right = h2;
		fourHeap.push_back(temp);			//push the new value
		fheapAgain(fourHeap.size()-1);			//call heapagain to take care of minHeap property
	}		
}

