#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<limits>

using namespace std;

#define INT_MIN numeric_limits<int>::min();
		
typedef struct heap{
	int data;
	int t;
	heap *left;
	heap *right;	
	string code;	
}heap;

vector<heap> binHeap;

void swap(int i, int j){
	heap temp;
	temp = binHeap[i];
	binHeap[i] = binHeap[j];
	binHeap[j] = temp;
}

void minHeapify(int i){
	int l = 2*i + 1;
	int r = 2*i + 2;
	int s = i;
	if(l<binHeap.size() && binHeap[l].t<binHeap[s].t)
		s = l;
	if(r<binHeap.size() && binHeap[r].t<binHeap[s].t)	
		s = r;
	if(s!=i){
		swap(s,i);
		minHeapify(s);
		}	
}

void buildHeap(){
	int n = binHeap.size();
	for(int i=n/2;i >=0;i--)
		minHeapify(i);
}

heap extractMin(){
	if (binHeap.size() < 1)
		cout << "Heap underflow\n";
	heap min = binHeap[0];
	binHeap[0] = binHeap[binHeap.size()-1];
	binHeap.pop_back();
	minHeapify(0);		
	return min;
}
	
void heapAgain(int i){
	int parent;
	if(i != 0){
		parent = (i-1)/2;
		if(binHeap[parent].t > binHeap[i].t){
			swap(parent,i);
			heapAgain(parent);
		}
	}
}	

/*void printTree(heap *node){
	int n = INT_MIN;
	if(node != NULL){
		if(node->data != n)
			cout << node->data <<" "<< node->t<<" "<< node->code <<endl;
		printTree(node->left);	
		printTree(node->right);
	}	
}

void codify(heap *node,string c){
	if(node->left == NULL && node->right == NULL)
		node->code = c+node->code;
	if(node->left != NULL && node->right != NULL){
		codify(node->left, c+node->code);
		codify(node->right, c+node->code);		
	}
		
}
*/
void bHeap(){
	string s;
	int k = 0;
	heap *h1,*h2,temp,*root;
	ifstream ifile("freq_table.txt");
	if(!ifile.is_open())
		cout<<"Unable to open file\n";
	else{
		while(getline(ifile,s)){
			istringstream(s) >> temp.data >> temp.t;
			temp.left = temp.right = NULL;
			temp.code = "";
			binHeap.push_back(temp);
		}	 
		ifile.close();
		}
	buildHeap();	
	while(binHeap.size() != 1)
	{	
		h1 = new heap();
		h2 = new heap();
		*h1 = extractMin();
		*h2 = extractMin();
		h1->code = "0";
		h2->code = "1";
		temp.data = INT_MIN;
		temp.t = h1->t + h2->t;
		temp.left = h1;
		temp.right = h2;
		binHeap.push_back(temp);
		heapAgain(binHeap.size()-1);		
	}
	//root = &binHeap[binHeap.size()-1];
	//root->code = "";
	//codify(root,"");
	//printTree(root);		
}	

