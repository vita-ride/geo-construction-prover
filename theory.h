#ifndef THEORY_H
#define THEORY_H

#include "formula.h"
#include <set>

class Theory
{
public:
    Theory() {}

    void addAxiom(Formula &axiom, string name);
    void addFormula(NormFormula &formula, string name);

    void addConstant(string s);
    bool isConstant(Term t);
    void addPredicate(const string &name, unsigned arity);

    void initNormalized();

    vector<pair<Formula, string>> initialAxioms;
    vector<pair<NormFormula, string>> facts;
    vector<pair<NormFormula, string>> simpleImplications;
    vector<pair<NormFormula, string>> complexAxioms;

    set<string> constants;
    vector<pair<string, unsigned>> predicates;
    set<string> occuringPredicates;

};

#endif // THEORY_H
