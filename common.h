#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <set>

using namespace std;

const string sBOT = "a01";
const string sTOP = "a02";

const string EQ_NATIVE_NAME = "eqnative";
const string PREFIX_NEGATED = "nnn";

enum fofType { eAxiom, eConjecture, eAny };

string skipChar(const string &str, char c);

#endif // COMMON_H
