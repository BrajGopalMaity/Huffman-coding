#include<stdio.h>
#include<ctime>
#include "HuffmanBinHeap.cpp"
#include "4wayHeap.cpp"
#include "PairingHeap.cpp"
#include "FreqTable.cpp"

int main(int argc, char* argv[]){
	clock_t start_time;
	freqtable(argv[1]);
	
	// binary heap
	start_time = clock();
	for(int i = 0; i < 10; i++)                                                             //run 10 times on given data set
		bHeap();
	cout << "Time using binary heap (microsecond): " << (clock() - start_time)/10 << endl;

	// 4-way heap
	start_time = clock();
	for(int i = 0; i < 10; i++)								//run 10 times on given data set
		fHeap();
	cout << "Time using 4-way heap (microsecond): " << (clock() - start_time)/10 << endl;
	
	// Pairing heap
	start_time = clock();
	for(int i = 0; i < 10; i++)								//run 10 times on given data set
		callpheap();
	cout << "Time using Pairing heap (microsecond): " << (clock() - start_time)/10 << endl;
	
	return 0;
	}
