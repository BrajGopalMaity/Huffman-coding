#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<limits>

using namespace std;

#define INT_MIN numeric_limits<int>::min();
		
class pheap{
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

pheap *hp = NULL;
int size = 0;

pheap* pheap::meld(pheap *h1, pheap *h2){
	if(h1 == NULL)
		return h2;
	else if(h1->t >= h2->t){
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

pheap* pheap::removeMin(){
	pheap *h1 = hp,*tmp;
	pheap *ch = hp->child;	
	if(ch == NULL){
		return h1;
		hp = NULL;
		}
	else if(ch->next == NULL){
		h1->child = NULL;
		ch->previous = NULL;
		hp = ch;		
		return h1;
		}
	else{	
	h1->child = NULL;	
	vector<pheap*> q;
	int n;
	while(ch != NULL){
		ch->previous = NULL;
		tmp = ch->next;
		ch->next = NULL;
		q.push_back(ch);	
		ch = tmp;
		}	
	n = q.size();
	while(q.size() > 1){
		tmp=meld(q[0],q[1]);
		q.push_back(tmp);
		q.erase(q.begin());
		q.erase(q.begin());
		}
	hp = q[0];		
	return h1;
	}
}

void pheap::put(pheap *temp){
	hp = meld(hp,temp);
	size++;	
}

void pheap::pairingheap(){
	string s;
	int i;
	pheap *h1,*h2,*temp,*root,*tmp;
	ifstream ifile("freq_table.txt");
	if(!ifile.is_open())
		cout<<"Unable to open file\n";
	else{
		while(getline(ifile,s)){
			temp = new pheap;
			istringstream(s) >> temp->data >> temp->t;
			put(temp);
		}	 
		ifile.close();
		}
	while(size != 1){
		h1 = removeMin();
		h2 = removeMin();
		size-=2;
		tmp = new pheap;
		tmp->data = INT_MIN;
		tmp->t = h1->t + h2->t;
		tmp->left = h1;
		tmp->right = h2;
		put(tmp);
		}				
}

void callpheap(){
	pheap pp;
	pp.pairingheap();
}	


