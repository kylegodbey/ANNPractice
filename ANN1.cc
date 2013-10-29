//Implementation for ANN class


#include <iostream>
#include <fstream>
#include <cmath>
#include "ANN.h"

using namespace std;

//Just put the ANN::function_name stuff here
ANN::ANN(){
  n=0;
  p=0;
}
//Opens the weights.in
bool ANN::open_IO(){
    inFile.open("weights.in");
        if( inFile.fail() ) { //file check
        cout << "Input file opening failed.\n";
        return false;
    }
    outFile.open("inputs.out");
    return true;
}

void ANN::fillArray(){
	int inputs(0), outputs(0);
		inFile >> inputs >> outputs;
		n = inputs;
		p = outputs;
	input = new double [inputs];
	output = new double[outputs];
	weights = new double*[inputs];
		for(int i=0; i< inputs; i++){
			weights[i] = new double[outputs];
			}
	//use a for loop to fill the weights array with the values from the weights file.
	for(int j(0);j<p;j++){
		for(int i(0);i<n;i++){
			inFile >> weights[i][j];
		}
	}
	inFile.close();
	inFile.open("inputs.in");
	for(int i(0);i<n;i++){
		inFile >> input[i];
	}
	inFile.close();
	//for populating the output array
	for(int j(0);j<p;j++){
	  output[j] = sigmoid(j);
	  outFile << output[j] << endl;
	}
}

void ANN::outputTest(){
	cout << "\tINPUTS\n";
	cout << "There are " << n << " input nodes\n";
		for(int i=0; i<n; i++){
		cout << input[i] << " ";
		}
	cout << endl;
	cout << "\tOUTPUTS\n";
	cout << "There are " << p << " output nodes\n";
		for(int i=0; i<p; i++){
		cout << output[i] << " ";
		}
	cout << endl;
	cout << "\tWEIGHTS\n";
		for(int row=0; row<n; row++){
			for(int col=0; col<p; col++){
				cout << weights[row][col] << " ";
			}
			cout << endl;
		}

	//for loop to output the values in the input array
	//for loop to output the values of the output array
	//double for loop to output the values of the weights array
}

double ANN::sigmoid(int j){
	double sum(0), sigvalue;
	for(int i(0);i<n; i++){
		sum = sum + input[i]*weights[i][j];
	}//summing the weights and indexes

	sigvalue = 1/(1+exp(-(sum)));
	//should provide the correct value
	return sigvalue;
}

void ANN::close_IO() {
    inFile.close();
	outFile.close();
	}


