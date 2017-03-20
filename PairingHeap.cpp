#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<limits>

using namespace std;

#define INT_MIN numeric_limits<int>::min();
		
typedef struct pheap{
	int data;
	int t;
	pheap *previous;
	pheap *next;
	pheap *child;	
	pheap *left;
	pheap *right;
	string code;	
}pheap;

pheap *hp = NULL;
int size = 0;

pheap* meld(pheap *h1, pheap *h2){
	if(h1 == NULL)
		return h2;
	else if(h1->t >= h2->t){
		h1->next = h2->child;
		h2->child = h1;
		h1->previous = h2;
		return h2;
		}
	else{
		h2->next = h1->child;
		h1->child = h2;
		h2->previous = h1;
		return h1;
		}		
		
}

pheap* removeMin(){
	pheap *h1 = hp;
	pheap *ch = hp->child;
	ch->previous = NULL;
	vector<pheap*> q;
	int n;
	while(ch != NULL){
		q.push_back(ch);
		ch = ch->next;
		}
	n = q.size();
	while(q.size() > 1){
		q[n]=meld(q[0],q[1]);
		//q.erase(q.begin());
		//q.erase(q.begin()+1);
		}
	//hp = q[0];	
	size--;		
	return h1;
}

void put(pheap *temp){
	hp = meld(hp,temp);
	size++;	
}

void printTree(pheap *node){
	int n = INT_MIN;
	if(node != NULL){
		if(node->data != n)
			cout << node->data <<" "<< node->t<<" "<< node->code <<endl;
		printTree(node->left);	
		printTree(node->right);
	}	
}

void codify(pheap *node,string c){
	if(node->left == NULL && node->right == NULL)
		node->code = c+node->code;
	if(node->left != NULL && node->right != NULL){
		codify(node->left, c+node->code);
		codify(node->right, c+node->code);		
	}
		
}

void pairingheap(){
	string s;
	int i;
	pheap *h1,*h2,*temp,*root;
	ifstream ifile("freq_table.txt");
	if(!ifile.is_open())
		cout<<"Unable to open file\n";
	else{
		while(getline(ifile,s)){
			temp = new pheap;
			istringstream(s) >> temp->data >> temp->t;
			temp->code = "";
			put(temp);
		}	 
		ifile.close();
		}
	while(size > 1){
		h1 = removeMin();
		h2 = removeMin();
		h1->code = "0";
		h2->code = "1";
		temp->data = INT_MIN;
		temp->t = h1->t + h2->t;
		temp->left = h1;
		temp->right = h2;
		put(temp);
		}
	cout << "OK";	
	//root = hp;
	//root->code = "0";
	//codify(root,"");
	//printTree(root);		
}

int main(){
	pairingheap();
	return 0;
}	


