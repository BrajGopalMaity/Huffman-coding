#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<limits>
#include<unordered_map>
#include<bitset>
#include "FreqTable.cpp"

using namespace std;

#define INT_MIN numeric_limits<int>::min();
		
typedef struct foheap{					//structure variable for 4-way minheap
	int data;
	int t;
	foheap *left;
	foheap *right;	
	string code;	
}foheap;

vector<foheap> fourHeap;				//array to hold fourway minheap structure
ofstream opfile ("code_table.txt");			//open code-table file

void fswap(int i, int j){				//swap function to swap two structure nodes in 4-way minheap
	foheap temp;
	temp = fourHeap[i];
	fourHeap[i] = fourHeap[j];
	fourHeap[j] = temp;
}

void fminHeapify(int i){				//minHeapify function to heapify a given array into 4-way minHeap
	int child[4],s;
	for(int j=3;j>=0;j--)				//get four children of parent
		child[3-j]=((i-3+1)*4)-j+3;
	s = i;
	for(int j=0;j<4;j++)
		if(child[j]<fourHeap.size() && fourHeap[child[j]].t<fourHeap[s].t)	//get minimum of 4 children and parent
			s = child[j];	
	if (s != i){					//if parent is not minimum swap it
		fswap(s,i);
		fminHeapify(s);
		}				
}

void fbuildHeap(){					//function to buid heap
	int n = fourHeap.size();
	for(int i = n/4+3;i >= 3;i--)
		fminHeapify(i);
}

foheap fextractMin(){					//extract the minimum element of the heap
	foheap min = fourHeap[3];
	fourHeap[3] = fourHeap[fourHeap.size()-1];
	fourHeap.pop_back();
	fminHeapify(3);		
	return min;
}

void fheapAgain(int i){					//heapify again after inserting an element
	int parent;
	if(i > 3){
		parent = ((i-4)/4)+3;
		if(fourHeap[parent].t > fourHeap[i].t){
			fswap(parent,i);
			fheapAgain(parent);
		}
	}
}

void fprintTree(foheap *node){				//print the data and code of that data in the code_table file
	int n = INT_MIN;
	if(node != NULL){
		if(node->data != n)
			opfile << node->data <<" "<< node->code <<endl;
		fprintTree(node->left);	
		fprintTree(node->right);
	}	
}

void fcodify(foheap *node,string c){			//assign a code to each of the terminal nodes(data) of the huffman tree
	if(node->left == NULL && node->right == NULL)
		node->code = c+node->code;
	if(node->left != NULL && node->right != NULL){
		fcodify(node->left, c+node->code);
		fcodify(node->right, c+node->code);		
	}
		
}

void fHeap(){					//main function to implement 4-way heap
	string s;
	int k = 0;
	int min = INT_MIN;
	foheap *h1,*h2,temp,*root;
	for(int i=0;i<3;i++){			//insert 3 dummy variables
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
			temp.code = "";
			fourHeap.push_back(temp);
		}	 
		ifile.close();
		}
	fbuildHeap();
	while(fourHeap.size() != 4)		//extract least frequency values 
	{	
		h1 = new foheap();
		h2 = new foheap();
		*h1 = fextractMin();
		*h2 = fextractMin();
		h1->code = "0";
		h2->code = "1";
		temp.data = INT_MIN;		//insert dummy data in the new node 
		temp.t = h1->t + h2->t;		//add least frequency values into the new node
		temp.left = h1;			//make those values child of the new node
		temp.right = h2;
		fourHeap.push_back(temp);	//push the new value
		fheapAgain(fourHeap.size()-1);	//call heapagain to take care of minHeap property	
	}	
	root = &fourHeap[fourHeap.size()-1];	//make the remaining element as the root of huffman tree
	root->code = "";			
	fcodify(root,"");			//assign codes to the data of the huffman tree calling fcodify function
	fprintTree(root);			//print the data and codes into code-table file
	opfile.close();	
}

int main(int argc, char* argv[]){
	freqtable(argv[1]);			//call frequency table function to create frequency table
	fHeap();				//call 4-way heap function to create coded huffman tree
	string s,cc="",cd;
	string num;
	int j = 0,i;
	size_t sz;
	bitset<8> bt;
	unordered_map<string, string> map;
	ifstream cfile("code_table.txt");
	if(!cfile.is_open())
		cout<<"Unable to open file\n";
	else{
		while(getline(cfile,s)){
				istringstream(s) >> num >> cd; //get the codes of data in a hashmap
				map[num] = cd;
			}
		cfile.close();		
	}	
	ifstream sfile(argv[1]);		//open input file
	ofstream ofile ("encoded.bin", ios::out | ios::binary);	//create encoded.bin file
	if(!sfile.is_open())
		cout<<"Unable to open file\n";	
	else{
		while(getline(sfile,s)){
			if(s != ""){
				istringstream(s) >> num; 
				cc += map[num]; //generate a string of codes of the data from the code-table and input file 
			}
		}
		int k=0;
		for(i = 0; i < cc.size();i++){ //run the loop for the length of the coded string
			if(cc[i] == '0')
				bt.set(7-j,0);	//if I get a 1 I set the bit else I reset the bit
			else 
				bt.set(7-j,1);		
			j++; 							
			if((i+1)%8 ==0){ 
				ofile.write ((char*)&bt, sizeof(char)); // write the 8bit code into the file
				j=0;
			}
		}
		if(j != 0){			//if the bits are not a multiple of 8 add padding
			for(;j<8;j++)
				bt.set(7-j,0);
			ofile.write ((char*)&bt, sizeof(char));
		}
		ofile.close();			//close the files
		sfile.close();		
	}
	return 0;
}	
