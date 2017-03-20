#include<stdio.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<unordered_map>

using namespace std;

int main(){
	string s;
	vector<string> words;	
	unordered_map <string, int> map;
	ifstream file("sample_input_small.txt");
	if(!file.is_open())
		cout<<"Unable to open file\n";
	else{		
		while(getline(file,s))
			if(s != "")
				words.push_back(s);
		file.close();
		for(int i=0;i<words.size();i++)
			map[words[i]]++;	
	}
	ofstream ofile("freq_table.txt");
	if(!ofile.is_open())
		cout<<"Unable to open file\n";
	else{
		for(auto& x:map){
			ofile << x.first;
			ofile << " "; 
			ofile << x.second;
			ofile << endl;	
			}
	}					
	return 0;			
}
