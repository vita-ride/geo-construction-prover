#include "theory.h"

void Theory::addAxiom(Formula &axiom, string name) {
    initialAxioms.push_back(pair<Formula, string>(axiom, name));
}

void Theory::addFormula(NormFormula &formula, string name) {
    if (formula.isFact()) {
        facts.push_back(pair<NormFormula, string>(formula, name));
    } else if (formula.isSimpleImplication()) {
        simpleImplications.push_back(pair<NormFormula, string>(formula, name));
    } else {
        complexAxioms.push_back(pair<NormFormula, string>(formula, name));
    }
}

void Theory::addConstant(string s) {
    if (s != "_")
        constants.insert(s);
}

bool Theory::isConstant(Term t) {
    return constants.find(t.getName()) != constants.end();
}

void Theory::addPredicate(const string &name, unsigned arity) {
    string p = name;

    if (p == "true" || p == "$true" || p == "false"|| p == "$false")
        return;

    if (name == "_")
        return;

    if (p[0] == '$')
        p = p.substr(1, p.size() - 1);

    if (occuringPredicates.find(p) != occuringPredicates.end())
        return;

    occuringPredicates.insert(p);

    for (size_t i = 0; i < predicates.size(); i++) {
        if (predicates[i].first == p) {
            return;
        }
    }

    if (p == sBOT || p == sTOP) {
        predicates.push_back(pair<string, unsigned>(sBOT, 0));
        predicates.push_back(pair<string, unsigned>(sTOP, 0));
    } else if (p.size() > 3 && p.substr(0, 3) == PREFIX_NEGATED) {
        predicates.push_back(
            pair<string, unsigned>(p.substr(3, p.size() - 3), arity));
        predicates.push_back(pair<string, unsigned>(p, arity));
    } else {
        predicates.push_back(pair<string, unsigned>(p, arity));
        predicates.push_back(pair<string, unsigned>(PREFIX_NEGATED + p, arity));
    }
}
