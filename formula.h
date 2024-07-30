#ifndef FORMULA_H
#define FORMULA_H

#include "common.h"

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
    bool read();

    const string &getName() const { return name; }

private:
    string name;
    //bool constant
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
    bool read();


    string getName() const { return name; }
    Term argAt(size_t i) const { return args.at(i); }
    size_t arity() const { return args.size(); }

    void clear() {
        name = "";
        args.clear();
    }

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

    size_t size() const { return conjuncts.size(); }
    Atomic at(size_t i) const {
        return conjuncts.at(i);
    }
    void add(const Atomic &a) { conjuncts.push_back(a); }

    bool read(bool conclusion = false);
    void clear() { conjuncts.clear(); }
private:
    vector<Atomic> conjuncts;
};

class NormFormula;

class Formula {
public:
    Formula() {}
    Formula(const Formula &f)  {
        premises = f.premises;
        conclusions = f.conclusions;
        universalVars = f.universalVars;
    }
    Formula(const Conjunction &prem, const Conjunction &conc) {
        premises = prem;
        conclusions = conc;
    }
    Formula &operator=(const Formula &f) {
        premises = f.premises;
        conclusions = f.conclusions;
        universalVars = f.universalVars;
        return *this;
    }

    size_t numPremises() const { return premises.size(); }
    size_t numConclusions() const { return conclusions.size(); }

    size_t numUnivVars() const { return universalVars.size(); }
    const string &univVarAt(size_t i) const { return universalVars.at(i); }
    void addUnivVar(const string &varName) { universalVars.push_back(varName); }
    void setUnivVars(const vector<string> &vars) { universalVars = vars; }
    int univVarIndex(string v) const;

    bool read();
    bool readUnivVars();
    bool readImplication();
    bool readWithoutCheckingBoundness();
    bool readTPTPStatement(const string &s, string &name, fofType &type);

    friend ostream &operator<<(ostream &os, const Formula &f);

    void normalize(const string &name, vector<pair<NormFormula, string>> &output) const;

    void clearUnivVars() { universalVars.clear(); }
    void clear() {
        premises.clear();
        conclusions.clear();
        clearUnivVars();
    }
private:
    Conjunction premises, conclusions;
    vector<string> universalVars;
};


class NormFormula {
public:
    NormFormula() {}
    NormFormula(const NormFormula &nf) {
        premises = nf.premises;
        conclusion = nf.conclusion;
        universalVars = nf.universalVars;
    }
    NormFormula(const Conjunction &prem, const Atomic &conc) {
        premises = prem;
        conclusion = conc;
    }
    NormFormula &operator=(const NormFormula &nf) {
        premises = nf.premises;
        conclusion = nf.conclusion;
        universalVars = nf.universalVars;
        return *this;
    }

    size_t numPremises() const { return premises.size(); }

    size_t numUnivVars() const { return universalVars.size(); }
    const string &univVarAt(size_t i) const { return universalVars.at(i); }
    void addUnivVar(const string &varName) { universalVars.push_back(varName); }
    void setUnivVars(const vector<string> &vars) { universalVars = vars; }

    bool isFact() const;
    bool isSimpleImplication() const;

    friend ostream &operator<<(ostream &os, const NormFormula &f);
private:
    Conjunction premises;
    Atomic conclusion;
    vector<string> universalVars;
};


inline ostream &operator<<(ostream &os, const Term &t) {
    os << t.getName();
    return os;
}

inline ostream &operator<<(ostream &os, const Atomic &a) {
    if (a.getName() == "false" || a.getName() == sBOT || a.getName() == PREFIX_NEGATED + sTOP) {
        os << "$false";
    } else if (a.getName() == "true" || a.getName() == sTOP || a.getName() == PREFIX_NEGATED + sBOT) {
        os << "$true";
    } else if (a.getName() == EQ_NATIVE_NAME) {
        os << a.argAt(0).getName() << " = " << a.argAt(1).getName();
    } else if (a.getName() == PREFIX_NEGATED + EQ_NATIVE_NAME) {
        os << a.argAt(0).getName() << " != " << a.argAt(1).getName();
    } else {
        if (a.getName().find(PREFIX_NEGATED) == 0) {
            string s = PREFIX_NEGATED;
            os << " ~"
               << a.getName().substr(s.length(), a.getName().size() - s.length())
               << " ";
        } else {
            os << a.getName();
        }
        if (a.arity() > 0) {
            os << "(";
            for (size_t i = 0; i < a.arity(); i++) {
                os << a.argAt(i).getName();
                if (i != a.arity() - 1)
                    os << ",";
            }
            os << ")";
        }
    }
    return os;
}

inline ostream &operator<<(ostream &os, const Conjunction &c) {
    os << "(";
    for (size_t i = 0; i < c.size(); i++) {
        os << c.at(i);
        if (i != c.size() - 1)
            os << " & ";
    }
    os << ")";
    return os;
}

inline ostream &operator<<(ostream &os, const Formula &f) {
    size_t size = f.numUnivVars();
    if (size > 0) {
        os << "(! [";
        for (size_t i = 0; i < size; i++) {
            os << f.univVarAt(i);
            if (i + 1 < size)
                os << ",";
        }
        os << "] : ";
    }

    if (f.numPremises() > 0) {
        os << "(" << f.premises << " => " << f.conclusions << ")";
    } else {
        os << f.conclusions;
    }

    if (size > 0)
        os << ")";

    return os;
}

inline ostream &operator<<(ostream &os, const NormFormula &f) {
    size_t size = f.numUnivVars();
    if (size > 0) {
        os << "(! [";
        for (size_t i = 0; i < size; i++) {
            os << f.univVarAt(i);
            if (i + 1 < size)
                os << ",";
        }
        os << "] : ";
    }

    if (f.numPremises() > 0) {
        os << "(" << f.premises << " => " << f.conclusion << ")";
    } else {
        os << f.conclusion;
    }

    if (size > 0)
        os << ")";

    return os;
}


#endif // FORMULA_H
