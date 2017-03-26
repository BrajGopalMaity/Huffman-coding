#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<limits>
#include<bitset>

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
}deHeap;

deHeap *head = new deHeap;

void decode(int d,string code){
	int i=0;
	deHeap *dec = head;
	deHeap *tmp;
	while(i<code.length()){
		if(code[i] == '0'){
			if(dec->left == NULL){
				tmp = new deHeap;
				tmp->data = INT_MIN;
				dec->left = tmp;
				}
			dec = dec->left;			
			}
		else{
			if(dec->right == NULL){
				tmp = new deHeap;
				tmp->data = INT_MIN;
				dec->right = tmp;
				}
			dec = dec->right;
			}
		i++;
	}		
	dec->data = d;
	dec->left = dec->right = NULL;	
}

void decodify(string enc){
	int min = INT_MIN;
	deHeap *node = head;
	ofstream ofile("decoded.txt");
	for(int j=0;j<=enc.length();j++){
		if(node->data != min){
			ofile << node->data << endl;
			node = head;
			j--;
			}
		else{
			if(enc[j] == '0')
				node = node->left;
			else
				node = node->right;
		}			
		
		}	
	ofile.close();		
	}

int main(int argc, char* argv[]){
	string code,s,enc;
	int d;
	streampos size;
	char *mem;
	bitset<8> b;
	head->data = INT_MIN;
	ifstream file(argv[2]);
	if(!file.is_open())
		cout<<"Unable to open file\n";
	else{		
		while(getline(file,s))
			{
				istringstream(s) >> d >> code;
				decode(d,code);
			}	
		file.close();	
	}
	ifstream ifile(argv[1], ios::in | ios::binary | ios::ate);
	if(!ifile.is_open())
		cout<<"Unable to open file\n";
	else{
		size = ifile.tellg();
		mem = new char[size];
		ifile.seekg(0,ios::beg);
		ifile.read(mem, size);
		for(int i=0;i<size;i++){
			b = mem[i];
			enc += b.to_string();
		}	
		ifile.close();
		delete[] mem;
		decodify(enc);	
	}
	return 0;
}
