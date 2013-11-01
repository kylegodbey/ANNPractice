#include <iostream>
#include "ANN.h"

using namespace std;

int main()
{
    ANN PNUT;
    int selection(0);
    cout << "Hello! Where is the love. Would you like to run the ANN for a given input, or train the network?" << endl;
    cout << "1. Run production network please\n";
    cout << "2. Train network\n> ";
    cin >> selection;
    if(selection==1){
        PNUT.Run();
    } else if(selection==2){
        PNUT.Run();
        PNUT.BackPropagation();
    }
    return 0;
}
