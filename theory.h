#ifndef THEORY_H
#define THEORY_H

#include "formula.h"

class Origin {
public:
    Origin() {}
    Origin(const NormFormula &nf, const string &stepName) {
        formula = nf.getConclusion();
        factsUsed = nf.getUsedFacts();
        replacements = nf.getReplacements();
        step = stepName;
    }
    const Atomic &getFormula() const { return formula; }
    const string &getStep() const { return step; }

    size_t numFacts() const { return factsUsed.size(); }
    const pair<string, Atomic> &factAt(size_t i) const { return factsUsed.at(i); }
    void addFact(const pair<string, Atomic> &f) { factsUsed.push_back(f); }

    const unordered_map<string, string> &getReplacements() const {
        return replacements;
    }
    void setReplacements(const unordered_map<string, string> &repl) {
        replacements = repl;
    }

    bool isPrinted() const { return printed; }
    void setPrinted(bool p) { printed = p; }

    Atomic formula;
    string step;
    vector<pair<string, Atomic>> factsUsed;
    unordered_map<string, string> replacements;
    bool printed = false;
};

class Theory
{
    friend class Prover;
public:
    Theory() {
        addPredicate(sBOT, 0);
        addPredicate(sTOP, 0);
    }

    bool readTPTP(const string inputFile);

    void addAxiom(Formula &axiom, string name);
    bool setTheorem(Formula &thm, string name);
    const pair<Formula, string> &getTheorem() const { return theorem; }
    void addFormula(const NormFormula &formula);

    void addEqSymAxiom();
    void addNEqSymAxiom();
    void addEqSubAxioms();

    void addConstant(string s);
    bool isConstant(Term t) const;
    void addPredicate(const string &name, unsigned arity);
    void updateSignature(const Formula &f);

    bool equalsUniv(const NormFormula &lhs, const NormFormula &rhs) const;

    void initNormalized();
    void saturate();
    void saturateFacts(set<NormFormula> &fs);
    bool canSaturate(const NormFormula &nf1, const NormFormula &nf2,
                     NormFormula &result) const;

    void printFormulas();

    void addOrigin(NormFormula &nf, const string &stepName);
    void addGoalName(const string &name) { goalNames.push_back(name); }

    void printProof();
    void printFactOrigin(const string &name);

private:
    vector<pair<Formula, string>> initialAxioms;
    pair<Formula, string> theorem;
    bool theoremAdded = false;

    set<NormFormula> facts;
    vector<NormFormula> simpleImplications;
    vector<NormFormula> complexAxioms;

    set<string> constants;
    vector<pair<string, unsigned>> predicates;
    set<string> occuringPredicates;

    unordered_map<string, Origin> origins;
    vector<string> goalNames;
};

set<NormFormula>::iterator findFirst(const set<NormFormula> &fs, const string &predicate);

#endif // THEORY_H
