#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<limits>

using namespace std;

#define INT_MIN numeric_limits<int>::min();
		
typedef struct heap{						//structure variable for binary minheap
	int data;
	int t;
	heap *left;
	heap *right;		
}heap;

vector<heap> binHeap;						//array to hold binary minheap structure

void swap(int i, int j){					//swap function to swap two structure nodes in binary minheap
	heap temp;
	temp = binHeap[i];
	binHeap[i] = binHeap[j];
	binHeap[j] = temp;
}

void minHeapify(int i){						//minHeapify function to heapify a given array into binary minHeap 
	int l = 2*i + 1;					//get children of parent
	int r = 2*i + 2;
	int s = i;
	if(l<binHeap.size() && binHeap[l].t<binHeap[s].t)	//get minimum of 4 children and parent
		s = l;
	if(r<binHeap.size() && binHeap[r].t<binHeap[s].t)	
		s = r;
	if(s!=i){						//if parent is not minimum swap it
		swap(s,i);
		minHeapify(s);
		}	
}

void buildHeap(){						//function to buid heap
	int n = binHeap.size();
	for(int i=n/2;i >=0;i--)
		minHeapify(i);
}

heap extractMin(){						//extract the minimum element of the heap
	heap min = binHeap[0];
	binHeap[0] = binHeap[binHeap.size()-1];
	binHeap.pop_back();
	minHeapify(0);		
	return min;
}
	
void heapAgain(int i){						//heapify again after inserting an element
	int parent;
	if(i != 0){
		parent = (i-1)/2;
		if(binHeap[parent].t > binHeap[i].t){
			swap(parent,i);
			heapAgain(parent);
		}
	}
}	

void bHeap(){							//main function to implement binary heap priority queue
	string s;
	int k = 0;
	heap *h1,*h2,temp,*root;
	ifstream ifile("freq_table.txt");
	if(!ifile.is_open())
		cout<<"Unable to open file\n";
	else{
		while(getline(ifile,s)){
			istringstream(s) >> temp.data >> temp.t;//take an entry from the file and insert it into the heap array
			temp.left = temp.right = NULL;
			binHeap.push_back(temp);
		}	 
		ifile.close();
		}
	buildHeap();	
	while(binHeap.size() != 1)				//extract least frequency values 
	{	
		h1 = new heap();
		h2 = new heap();
		*h1 = extractMin();
		*h2 = extractMin();
		temp.data = INT_MIN;				//insert dummy data in the new node
		temp.t = h1->t + h2->t;				//add least frequency values into the new node
		temp.left = h1;					//make those values child of the new node
		temp.right = h2;
		binHeap.push_back(temp);			//push the new value
		heapAgain(binHeap.size()-1);			//call heapagain to take care of minHeap property		
	}		
}	

