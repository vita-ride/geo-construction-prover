#ifndef THEORY_H
#define THEORY_H

#include "formula.h"

class Theory
{
public:
    Theory() {}

    void addAxiom(Formula &axiom, string name);
    void addFormula(NormFormula &formula);

    void addConstant(string s);
    bool isConstant(Term t) const;
    void addPredicate(const string &name, unsigned arity);

    bool equalsUniv(const NormFormula &lhs, const NormFormula &rhs) const;
    set<NormFormula>::iterator findFirst(const string &predicate) const;

    void initNormalized();
    void saturate();
    bool canSaturate(const NormFormula &nf1, const NormFormula &nf2,
                     NormFormula &result) const;

    vector<pair<Formula, string>> initialAxioms;
    set<NormFormula> facts;
    vector<NormFormula> simpleImplications;
    vector<NormFormula> complexAxioms;

    set<string> constants;
    vector<pair<string, unsigned>> predicates;
    set<string> occuringPredicates;

};

#endif // THEORY_H
