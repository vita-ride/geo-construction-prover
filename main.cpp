#include <iostream>
#include "prover.h"
#include <chrono>
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
        t.printFormulas();

        auto start = chrono::high_resolution_clock::now();
        p.prove();
        auto end = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "Elapsed(ms): " << duration.count() << endl;
    }
}
