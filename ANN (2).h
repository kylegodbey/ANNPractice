//Header file for ANN class

#include <iostream>
#include <fstream>



using namespace std; 	

class ANN{
public:
	ANN();
	//~ANN();
	bool open_IO();
	void close_IO();
	void fillArray(); //takes the first two inputs from the 
	void outputTest(); // cout the output so we know what's going on 


private:
	int n,p;
	ifstream inFile; //file in stream
	ofstream outFile; //file out stream
	//array for input nodes
	double * input;
	//array for output nodes
	double * output;
	//array for weights
	double ** weights;
	double sigmoid(int j); //performs the operation of the sigmoid and returns the value for a given j
};
