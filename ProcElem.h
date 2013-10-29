///<  The processing element class. These functions and variables are common amongst nodes.

#ifndef PROCELEM_H
#define PROCELEM_H
#include <cstdlib>
#include <vector>

using namespace std;

class ProcElem{
public:
    /// \brief Default Constructor.

    ProcElem();

    /// \brief Sets weight of a node given an index to change.
    ///
	/// Precondition: (0 <= index < numInput); (0<= Wt <= 1),
	/// Postcondition: Sets the weight for a given index to a weight value

	void setWeight(int index, double Wt);

    /// \brief Used to initialize the weights vectors.
    ///
	/// Precondition: Wt is between 0 and 1,
	/// Postcondition: The number of weights increases by 1
    /// and the value of that weight is added as the last weight in the weights vector

    void setWeight(double Wt);

    /// \brief Sets the input to a node given an index and a value to change to.
    ///
    /// Precondition: (0 <= index < numInput); (0<= In <= 1),
	/// Postcondition: Sets the input value at a given index in the inputs vector

	void setInput (int index, double In);

    /// \brief Initializes the inputs vector.
    ///
    /// Precondition: In is a value between 0 and 1,
	/// Postcondition: This initializes the inputs for a given node, by pushing
    /// back into the inputs vector

	void setInput (double In);

    /// \brief Gets the weight of a node from an index signifying the connected node.
    ///
    /// Precondition: The index is within range,
    /// Postcondition: Returns the weight value for a node at that given index

	double getWeight(int index);

    /// \brief Gets the input to a node from the connected node in the prior layer.
    ///
    /// Precondition: The index is within range,
	/// Postcondition: returns the input value

	double getInput(int index);

	/// \brief Returns the activation function for all connected inputs and adds to the outputs vector.
	///
    /// This will add the the vector in order such that the outputs vector stores
    /// the output of a node for all patterns ran.

    double sigmoid();

    /// \brief This will clear the input vector.
    ///
    /// Clearing a given PE inputs vector so the patterns can be cycled through,
    /// and added to.

    void inputClear();

    /// \brief This will get the output of the node for a given pattern, k.
    ///
    /// Get output will return the output at the index of the vector, k, which
    /// is the output of the node for the pattern in question.

    double getOutput(int k);

private:
    vector<double> outputs; /// the outputs of this node for k patterns
	vector<double> weights; /// A weights vector
	vector<double> inputs; /// The input value for this PE

};
#endif
