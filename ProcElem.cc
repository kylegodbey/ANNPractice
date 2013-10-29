#include <iostream>
#include <cmath>
#include "ProcElem.h"

using namespace std;

ProcElem::ProcElem(){

}

void ProcElem::setWeight(int index, double Wt){
//Sets the weight for a given index to a weight value
    weights[index]=Wt;
}

void ProcElem::setWeight(double Wt){
//Sets the weight for a given index to a weight value
    weights.push_back(Wt);
}

double ProcElem::getWeight(int index){
//returns the weight value for a given index
	//error checking
	if((index >= weights.size()) || (index < 0)) {cout << "OUT OF RANGE\n"; return 0.0;}
	return weights[index];
	}


void ProcElem::setInput(int index, double In){
//Sets the input value.  The input value should be between 0 and 1
	inputs[index] = In;
}

void ProcElem::setInput(double In){
//Sets the input value.  The input value should be between 0 and 1
	inputs.push_back(In);
}

double ProcElem::getInput(int index){
//returns the input value stored in this node
	return inputs[index];
}

void ProcElem::inputClear(){
    //clears the input vector
    inputs.clear();
}

double ProcElem::sigmoid(){

	double sum(0), sigvalue;
	for(int i(0);i<weights.size(); i++){
		sum += inputs[i]*weights[i];
	}//summing the weights and indexes

	sigvalue = 1/(1+exp(-(sum)));
	//should provide the correct value
	outputs.push_back(sigvalue); //this will push the output of a node into a vector
	return sigvalue;
}

double ProcElem::getOutput(int k){
    return outputs[k];
}
