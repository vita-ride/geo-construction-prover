#ifndef THEORY_H
#define THEORY_H

#include "formula.h"

class Theory
{
    friend class Prover;
public:
    Theory() {}

    bool readTPTP(const string inputFile);

    void addAxiom(Formula &axiom, string name);
    bool setTheorem(Formula &thm, string name);
    const pair<Formula, string> &getTheorem() const { return theorem; }
    void addFormula(const NormFormula &formula);

    void addConstant(string s);
    bool isConstant(Term t) const;
    void addPredicate(const string &name, unsigned arity);

    bool equalsUniv(const NormFormula &lhs, const NormFormula &rhs) const;
    set<NormFormula>::iterator findFirst(const string &predicate) const;

    void initNormalized();
    void saturate();
    bool canSaturate(const NormFormula &nf1, const NormFormula &nf2,
                     NormFormula &result) const;


    void printFormulas();

    vector<pair<Formula, string>> initialAxioms;
    pair<Formula, string> theorem;
    bool theoremAdded = false;

    set<NormFormula> facts;
    vector<NormFormula> simpleImplications;
    vector<NormFormula> complexAxioms;

    set<string> constants;
    vector<pair<string, unsigned>> predicates;
    set<string> occuringPredicates;

};

#endif // THEORY_H
