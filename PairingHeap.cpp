#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<limits>

using namespace std;

#define INT_MIN numeric_limits<int>::min();
		
class pheap{							//class variable for pairing minheap
	int data;
	int t;
	pheap *previous;
	pheap *next;
	pheap *child;	
	pheap *left;
	pheap *right;
	public:
		pheap(){
			this->previous = NULL;
			this->next = NULL;
			this->child = NULL;
			this->left = NULL;
			this->right = NULL;
			}
		pheap* meld(pheap*,pheap*);
		pheap* removeMin();
		void put(pheap*);
		void pairingheap();						
};

pheap *hp = NULL;						//variable to hold the root of pairing minheap
int size = 0;

pheap* pheap::meld(pheap *h1, pheap *h2){			//meld function to meld two roots into one pairing heap
	if(h1 == NULL)
		return h2;
	else if(h1->t >= h2->t){				//check for the lesser of both and attach the other one into that
		if(h2->child != NULL){
			h1->next = h2->child;
			h2->child->previous = h1;
			} 
		h2->child = h1;
		h1->previous = h2;
		return h2;
		}
	else{   
		if(h1->child != NULL){	
			h2->next = h1->child;
			h1->child->previous = h2;
			} 
		h1->child = h2;
		h2->previous = h1;
		return h1;
		}		
		
}

pheap* pheap::removeMin(){					//extractmin fucntion to extract the root of the pairing minHeap
	pheap *h1 = hp,*tmp;
	pheap *ch = hp->child;	
	if(ch == NULL){					//if root has no child then make the pairing heap nul and return root
		hp = NULL;
		return h1;
		}
	else if(ch->next == NULL){			//if root has a single child then make that child root and return root
		h1->child = NULL;
		ch->previous = NULL;
		hp = ch;		
		return h1;
		}
	else{				//if root has more than one child then remove root and do multipass merging of its children
	h1->child = NULL;	
	vector<pheap*> q;
	while(ch != NULL){		//get the children of root in a queue
		ch->previous = NULL;
		tmp = ch->next;
		ch->next = NULL;
		q.push_back(ch);	
		ch = tmp;
		}	
	while(q.size() > 1){		//until only one root is left do multipass melding
		tmp=meld(q[0],q[1]);
		q.push_back(tmp);
		q.erase(q.begin());
		q.erase(q.begin());
		}
	hp = q[0];			//make the result of meld operation the root of heap and return the initial root
	return h1;
	}
}

void pheap::put(pheap *temp){		//function to put new element in the pairing heap using meld operation
	hp = meld(hp,temp);
	size++;	
}

void pheap::pairingheap(){		//main function to implement pairing heap priority queue
	string s;
	int i;
	pheap *h1,*h2,*temp,*root,*tmp;
	ifstream ifile("freq_table.txt");
	if(!ifile.is_open())
		cout<<"Unable to open file\n";
	else{
		while(getline(ifile,s)){	//take an entry from the file and insert it into the heap
			temp = new pheap;
			istringstream(s) >> temp->data >> temp->t;
			put(temp);
		}	 
		ifile.close();
		}
	while(size != 1){			//extract least frequency values 
		h1 = removeMin();
		h2 = removeMin();
		size-=2;
		tmp = new pheap;
		tmp->data = INT_MIN;		//insert dummy data in the new node
		tmp->t = h1->t + h2->t;		//add least frequency values into the new node
		tmp->left = h1;			//make those values child of the new node
		tmp->right = h2;
		put(tmp);			//push the new value
		}				
}

void callpheap(){
	pheap pp;
	pp.pairingheap();			//call the main pairingheap function
}	


