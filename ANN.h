///< The ANN class which creates the structure of the ANN

#ifndef ANN_H
#define ANN_H
#include <iostream>
#include <fstream>
#include "ProcElem.h"

using namespace std;

class ANN{
public:
    /// \brief Default Constructor to initialize the ANN.
    ///
    ///This will set up the ANN depending on the data in the files specified
    ///by the weights.in file. Specifically it builds the structure and sets the weights
    ///between the nodes.
    ANN();

	/// \brief Used to train the network via back propagation.
	///
    ///There is an expected output file and the user wishes to train the network
	///This function will set all of the new weights for the ANN, as well as outputing the error
    ///for all patterns in an input file
	void BackPropagation();

	/// \brief This runs the network for a given input data set with any number of input patterns.
	///
    ///It sets the output files and outputs for a given pattern. This can thenbe used in back
    ///propagation to train the network.
	void Run();

    /// \brief Outputs the weights to weights.out.
    ///
    /// Precondition: The ANN has been created and run through and produced outputs
    /// Postcondition: creates a file called weights.out that outputs all of the current nodes and weights in the ANN
    void outputWeight();

private:
    ifstream inFile; ///file in stream
	ofstream outFile; ///file out stream
    double ** inputLayer; ///stores all of the inputs from inputs.in for access later on
	ProcElem * hiddenLayer; ///The hidden layer of PEs of the ANN
	ProcElem * outputLayer; ///The output layer of PEs of the ANN
	int numInput, numHidden, numOutput, numPattern;
	///integer values for the numbers of elements in the layers

	double ** outError; ///Error in the output values

    ///the expected values for the network for a given number of patterns. this is only applicable in back propagation
	double ** expected;

    ///Precondition: There are no existing nodes in the ANN, there is a weights.in file
    ///Postcondition: reads weights.in, sets up all of the corresponding arrays of ProcElem(s) and fills the weights
    void createNodes();

	void Output(int k);



    ///Precondition: The ANN has been created and has run through and produced outputs
    ///Postcondition: Outputs the total error
	double totalError();

};
#endif
