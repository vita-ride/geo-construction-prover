#include <iostream>
#include "prover.h"
using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2) {
        cout << "Usage: ./geoprover filename" << endl;
    } else {
        string inputFile = argv[1];
        Theory t;
        if(!t.readTPTP(inputFile))
            return 1;

        Prover p(t);
        p.initAxioms();
        p.prove();
    }
}
