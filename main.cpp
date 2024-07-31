#include <iostream>
#include "theory.h"
using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2) {
        cout << "Usage: ./geoprover filename" << endl;
    } else {
        string inputFile = argv[1];
        Theory t;
        t.readTPTP(inputFile);
        t.initNormalized();
        t.saturate();
        t.printFormulas();
    }
}
