#ifndef PROVER_H
#define PROVER_H

#include "theory.h"

class Prover
{
public:
    Prover(Theory &t): theory(t) {}

    void initAxioms();
    bool prove();
    void generateFacts(NormFormula nf, set<NormFormula> &newFacts,
                       bool earlyChecked = false);
    bool canMerge(const NormFormula &nf, const NormFormula &f,
                  NormFormula &merged);

    Theory &theory;
    set<Atomic> goals;

    unsigned appliedCounter = 0;
};

class UnionManager
{
public:
    UnionManager(){}
    string representative(const string &name, bool fact = false);
    bool makeUnion(const string &a, const string &b);
    bool addConstant(const string &var, const string &c, bool fact = false);
    unordered_map<string,string> getReplacements(const vector<string> &vars);
private:
    unordered_map<string, string> parent;
    const char constantPrefix = '_';
    const char secondaryPrefix = '.';
};



#endif // PROVER_H
