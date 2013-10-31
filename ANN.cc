#include <iostream>
#include <fstream>
#include <cmath>
#include "ANN.h"
#include "ProcElem.h"

using namespace std;

ANN::ANN(){
    numInput = 0;
    numHidden = 0;
    numOutput = 0;
    numPattern = 0;
    createNodes(); //CreateNodes sets ups all of the internal structure of the ANN
}

void ANN::createNodes(){
/*--NO SETTING UP WEIGHTS--*/

    inFile.open("weights.in"); //Open the weights file
    inFile >> numInput >> numHidden >> numOutput; //Grab the first three values for the number of nodes for each

    //note that we aren't making an input layer array of PE's, because the values for the input array serves that purpose
    hiddenLayer = new ProcElem [numHidden]; //create the nodes for the hidden layer
    outputLayer = new ProcElem [numOutput];//create the nodes for the output layer
    int counter(0);
    double temp; //the variable that stores the weight for a given node and index
    for(int j(0);j<numHidden;j++){ //loop through the weights
        for(int h(0);h<numInput;h++){ //loop through the input nodes
            inFile >> temp;
            hiddenLayer[j].setWeight(temp); //sets the weight for the hidden nodes based on what's input
        }
    }

    //This does the same for the weights on the output layer, pulling from the second half of the weights.in file
    for(int i(0);i<numOutput;i++){
        for(int j(0);j<numHidden;j++){
            inFile >> temp;
            outputLayer[i].setWeight(temp);
        }
    }
     inFile.close(); //finished with the weights.in file

/*--SETTING UP INPUT ARRAY--*/
    inFile.open("inputs.in");
    while(inFile >> temp){//counts the number of patterns in an input file
        counter++;
    }
    numPattern = counter/numInput; //calculation for the total number of patterns
    inFile.close(); //closing and reopening since counting is done
    inFile.open("inputs.in");

    inputLayer = new double *[numPattern];
    for(int k(0);k<numPattern;k++){
        inputLayer[k]=new double [numInput];
        for(int j(0);j<numInput;j++){
            inFile >> inputLayer[k][j]; //Filling in the input array for every pattern
        }
    }
    inFile.close(); //Slosed the input file stream since we're done with inputs.in
}

void ANN::Run(){
    outFile.open("inputs.out"); //The result of the ANN will output to this file
    for(int k(0);k<numPattern;k++){
        //Read the Input layer into the hidden layer
        for(int i(0);i<numHidden;i++){
            for(int j(0);j<numInput;j++){
                //This adds to the hidden layer inputs.
                hiddenLayer[i].setInput(inputLayer[k][j]);
            }
        }
        //hidden layer calculates sigmoid
        for(int j(0);j<numOutput;j++){
            for(int i(0);i<numHidden;i++){
                //Sets the input of the output node to be the result of the hidden layer's sigmoid function
                //It adds this input at the end of the vector for Inputs for the output layer
                outputLayer[j].setInput(hiddenLayer[i].sigmoid());
                hiddenLayer[i].inputClear();
            }
            //This also takes the output layer of our ANN, since it is calculated, and adds it to the vector
            //We store all of our outputs in a vector so it is easier to calculate the error later
            outputLayer[j].sigmoid();
            outputLayer[j].inputClear();
        }

        Output(k); //simply outputs the entire line for a given input pattern to a file

    }
    outFile.close();
}

void ANN::BackPropagation(){
/*--SETUP EXPECTED AND ERROR ARRAYS--*/
    inFile.open("expected.out"); //we need to read in the expected inputs to calculate the error
    outFile.open("error.out"); //errors will be output here
    //temp variables
    double newWeight(0.0), sum(0.0) , weightDiff(0.0), hiddenError(0.0), errorSum(0.0);

    outError = new double *[numPattern]; //Dynamically creating the 2D array for the output errors
    for(int k(0);k<numPattern;k++){
        outError[k]=new double [numOutput];
    }

    expected = new double *[numPattern];
    for(int i(0);i<numPattern;i++){
        expected[i]=new double [numOutput]; //Dynamically creating the 2D array for the expected values
        for (int j(0);j<numOutput;j++){
            inFile >> expected[i][j]; //reads from the file and stores it in the expected values
        }
    }

    outFile << totalError() << endl; //We needed to output the total error for the ANN after comparisons

/*--SUMMATION OF ERRORS--OUTPUT LAYER ADJUSTMENT--*/
    for(int j(0);j<numOutput;j++){
        for(int i(0);i<numHidden;i++){
            for(int k(0);k<numPattern;k++){
                /*The error for a given pattern's output node is equal to the expected
                output for that pattern minus the actual output for the node*/
                outError[k][j]=(expected[k][j]-outputLayer[j].getOutput(k));
               //Sum is a temp sum that sums output error * hidden layer out put for a given pattern
               sum += outError[k][j] * hiddenLayer[i].getOutput(k);
            }
            //The new weight becomes the sum of the errors added to the current weight
            newWeight = outputLayer[j].getWeight(i) + sum;
            //The difference is the new weight minus the old weight
            weightDiff = newWeight - outputLayer[j].getWeight(i);
            //output the difference in weights
            outFile << weightDiff << " ";
            //Set the weight of the output layer to the new weight. Finished correction for output layer
            outputLayer[j].setWeight(i, newWeight);
        }
    }
    outFile.close();

/*--SUMMATION OF ERRORS--HIDDEN LAYER ADJUSTMENT--*/
    for (int i(0);i<numHidden;i++){
        for(int h(0);h<numInput;h++){
            for(int k(0);k<numPattern;k++){
                for(int j(0);j<numOutput;j++){
                   //The sum of the errors is the sum of the output error * the current weight
                    errorSum += outError[k][j] * outputLayer[j].getWeight(i);
                }
                /*The error for the hidden layer is equal to the output of the hidden node
                multiplied by 1 - that same output times the sum of the errors
                The ongoing sum total is between the hidden layer's error and the input layer this time
                versus the output error to the hidden layer in the previous summation*/
                hiddenError = (hiddenLayer[i].getOutput(k) * (1 - hiddenLayer[i].getOutput(k))) * errorSum;
                sum += hiddenError * inputLayer[k][h];
            }
            //Establishes the new weight and sets the hidden layer's weight to that value
            newWeight = hiddenLayer[i].getWeight(h) + sum;
            hiddenLayer[i].setWeight(h, newWeight);
        }
    }
    //Now that all of the weights have been adjusted, output those changes to the weights.out file
    outputWeight();
}

void ANN::outputWeight(){
        outFile.open("weights.out");
    outFile << numInput << " " << numHidden << " " << numOutput << endl;
    for (int i(0);i<numHidden;i++){
        for (int h(0);h<numInput;h++){
            outFile << hiddenLayer[i].getWeight(h) << " ";
        }
        outFile << endl;
    }
    for (int j(0);j<numOutput;j++){
        for(int i(0);i<numHidden;i++){
            outFile << outputLayer[j].getWeight(i) << " ";
        }
        outFile << endl;
    }
    outFile.close();
}

double ANN::totalError(){
//total error for a pattern goes here
    double tempError(0);
    for (int k(0);k<numPattern;k++){
        for(int j(0);j<numOutput;j++){
            tempError += (expected[k][j]-outputLayer[j].getOutput(k)) * (expected[k][j]-outputLayer[j].getOutput(k));
        }
    }
    return 0.5 * tempError;
}
//K in this case is the current iteration of the pattern
void ANN::Output(int k){
    for(int j(0);j<numOutput;j++){
        outFile << outputLayer[j].getOutput(k) << " ";
    }
    outFile << endl;
}
