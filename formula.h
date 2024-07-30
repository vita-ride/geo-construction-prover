#ifndef FORMULA_H
#define FORMULA_H

#include <string>
#include <vector>

using namespace std;

class Term {
public:
    Term() {}
    Term (const Term &t) {
        name = t.name;
    }
    Term &operator=(const Term &t) {
        name = t.name;
        return *this;
    }
    Term (const string &s) {
        name = s;
    }

private:
    string name;
};

class Atomic {
public:
    Atomic() {}
    Atomic(const Atomic &a) {
        name = a.name;
        args = a.args;
    }
    Atomic &operator=(const Atomic &a) {
        name = a.name;
        args = a.args;
        return *this;
    }

    string getName() const { return name; }
    size_t getArity() const { return args.size(); }

private:
    string name;
    vector<Term> args;
};

class Conjunction {
public:
    Conjunction() {}
    Conjunction(const Conjunction &c) {
        conjuncts = c.conjuncts;
    }
    Conjunction &operator=(const Conjunction &c) {
        conjuncts = c.conjuncts;
        return *this;
    }
private:
    vector<Atomic> conjuncts;
};

class Formula {
public:
    Formula() {}
    Formula(const Formula &f)  {
        premises = f.premises;
        conclusion = f.conclusion;
    }
    Formula &operator=(const Formula &f) {
        premises = f.premises;
        conclusion = f.conclusion;
        return *this;
    }
private:
    Conjunction premises, conclusion;
};

class NormFormula {
public:
    NormFormula() {}
    NormFormula(const NormFormula &nf) {
        premises = nf.premises;
        conclusion = nf.conclusion;
    }
    NormFormula &operator=(const NormFormula &nf) {
        premises = nf.premises;
        conclusion = nf.conclusion;
        return *this;
    }
private:
    Conjunction premises;
    Atomic conclusion;
};

#endif // FORMULA_H
