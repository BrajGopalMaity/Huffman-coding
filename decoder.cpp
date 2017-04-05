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

typedef struct deHeap{				//structure to hold the decoder tree
	int data;
	deHeap *left;
	deHeap *right;	
	deHeap(){
		this->left = NULL;
		this->right = NULL;
	}	
}deHeap;

deHeap *head = new deHeap;			//root of the decoder tree

void decode(int d,string code){
	int i=0;
	deHeap *dec = head;
	deHeap *tmp;
	while(i<code.length()){			//run for the whole length of the code
		if(code[i] == '0'){		//if the bit is 0 go left and make a node if not present
			if(dec->left == NULL){
				tmp = new deHeap;
				tmp->data = INT_MIN;
				dec->left = tmp;
				}
			dec = dec->left;			
			}
		else{				//if the bit is 1 go right and make a node if not present
			if(dec->right == NULL){
				tmp = new deHeap;
				tmp->data = INT_MIN;
				dec->right = tmp;
				}
			dec = dec->right;
			}
		i++;
	}		
	dec->data = d;				//add data at the end and make it terminal node
	dec->left = dec->right = NULL;	
}

void decodify(string enc){
	int min = INT_MIN;
	deHeap *node = head;
	ofstream ofile("decoded.txt");		//open decoded.txt
	for(int j=0;j<=enc.length();j++){	//run for the whole length of encoded string
		if(node->data == -1){		//if EOF is present break from the loop and end decoding
			ofile << node->data;
			break;
			}
		//if actual data is obtained after traversing the tree write it down and start from root again	
		else if(node->data != min){
			ofile << node->data << endl;
			node = head;
			j--;
			}
		else{		//if actual data is not found then depending on 0 or 1 in the code go left or right respectively
			if(enc[j] == '0')
				node = node->left;
			else
				node = node->right;
		}			
		
		}	
	ofile.close();				//close file
	}

int main(int argc, char* argv[]){
	string code,s,enc;
	int d;
	streampos size;
	char *mem;
	bitset<8> b;
	head->data = INT_MIN;
	ifstream file(argv[2]);			//open code_table.txt
	if(!file.is_open())
		cout<<"Unable to open file\n";
	else{		
		while(getline(file,s))
			{
				istringstream(s) >> d >> code;	//prepare the decoder tree
				decode(d,code);
			}	
		file.close();	
	}
	ifstream ifile(argv[1], ios::in | ios::binary | ios::ate);	//open encoded.bin
	if(!ifile.is_open())
		cout<<"Unable to open file\n";
	else{
		size = ifile.tellg();
		mem = new char[size];
		ifile.seekg(0,ios::beg);
		ifile.read(mem, size);		//get the size of the encoded file and allocate a memory buffer of that size
		for(int i=0;i<size;i++){	//get the code present in that file in the buffer and convert in to string
			b = mem[i];
			enc += b.to_string();
		}	
		ifile.close();
		delete[] mem;			//deallocate buffer
		decodify(enc);			//run the string through th decoder tree to generate decode file
	}
	return 0;
}
