#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<limits>

using namespace std;

#define INT_MIN numeric_limits<int>::min();

typedef struct deHeap{
	int data;
	deHeap *left;
	deHeap *right;	
	deHeap(){
		this->left = NULL;
		this->right = NULL;
	}	
}

deHeap *dec,*tmp;
dec->data = INT_MIN;

void decode(int d,string code){
		if(code[0] == '0'){
			tmp = new deHeap;
			tmp->data = INT_MIN;
			dec->left = tmp;
			dec = tmp;			
			}
		else{
			tmp = new deHeap;
			tmp->data = INT_MIN;
			dec->right = tmp;
			dec = tmp;
			}
		decode(d,)	
}

int main(){
	string code;
	int d;
	ifstream file("code_table.txt");
	if(!file.is_open())
		cout<<"Unable to open file\n";
	else{	
		dec	
		while(getline(file,s))
			{
				istringstream(s) >> d >> code;
				decode(d,code);
			}	
		file.close();
		for(int i=0;i<words.size();i++)
			map[words[i]]++;	
	}
	return 0;
}
