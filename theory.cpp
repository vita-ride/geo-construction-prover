#include "theory.h"

/*
 * Parts of this code include and modify
 * code from the Larus repository.
 * Original source: https://github.com/janicicpredrag/Larus
 * Original author: [Predrag Janicic]
 * Original license: GPL-3.0
 */

void Theory::addAxiom(Formula &axiom, string name) {
    initialAxioms.push_back(pair<Formula, string>(axiom, name));
}

void Theory::addFormula(NormFormula &formula) {
    if (formula.isFact()) {
        facts.insert(formula);
    } else if (formula.isSimpleImplication()) {
        simpleImplications.push_back(formula);
    } else {
        complexAxioms.push_back(formula);
    }
}

void Theory::addConstant(string s) {
    if (s != "_")
        constants.insert(s);
}

bool Theory::isConstant(Term t) const {
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

bool Theory::equalsUniv(const NormFormula &lhs, const NormFormula &rhs) const {
    map<string, string> repl;
    if (lhs.numPremises() != rhs.numPremises())
        return false;
    if (lhs.getConclusion().getName() != rhs.getConclusion().getName())
        return false;

    for (size_t i = 0; i < lhs.numPremises(); i++) {
        if (lhs.premiseAt(i).getName() != rhs.premiseAt(i).getName())
            return false;
        for (size_t j = 0; j < lhs.premiseAt(i).arity(); j++) {
            if (isConstant(lhs.premiseAt(i).argAt(j))) {
                if (lhs.premiseAt(i).argAt(j) != rhs.premiseAt(i).argAt(j))
                    return false;
            } else if (repl.find(lhs.premiseAt(i).argAt(j).getName()) != repl.end()) {
                if (repl[lhs.premiseAt(i).argAt(j).getName()] !=
                    rhs.premiseAt(i).argAt(j).getName())
                    return false;
            } else {
                repl[lhs.premiseAt(i).argAt(j).getName()] =
                    rhs.premiseAt(i).argAt(j).getName();
            }
        }
    }
    for (size_t i = 0; i < lhs.getConclusion().arity(); i++) {
        if (isConstant(lhs.getConclusion().argAt(i))) {
            if (lhs.getConclusion().argAt(i) != rhs.getConclusion().argAt(i))
                return false;
        } else if (repl.find(lhs.getConclusion().argAt(i).getName()) != repl.end()) {
            if (repl[lhs.getConclusion().argAt(i).getName()] !=
                rhs.getConclusion().argAt(i).getName())
                return false;
        } else {
            repl[lhs.getConclusion().argAt(i).getName()] =
                rhs.getConclusion().argAt(i).getName();
        }
    }

    return true;
}

set<NormFormula>::iterator Theory::findFirst(const string &predicate) const {
    Atomic conc(predicate);
    NormFormula searchFor;
    searchFor.setConclusion(conc);

    return lower_bound(facts.begin(), facts.end(), searchFor);
}


void Theory::initNormalized() {
    for (auto it = initialAxioms.begin(); it != initialAxioms.end(); it++) {
        vector<NormFormula> normalized;
        Formula &ax = it->first;
        ax.normalize(it->second, normalized);
        for (size_t i = 0; i < normalized.size(); i++) {
            addFormula(normalized.at(i));
        }
    }
}

void Theory::saturate() {
    bool updated = false;
    unsigned count = 0;
    //todo
    do {
        updated = false;
        for(size_t i = 0; i < simpleImplications.size(); i++) {
            const NormFormula nf1 = simpleImplications.at(i);
            for(size_t j = 0; j < simpleImplications.size(); j++) {
                const NormFormula nf2 = simpleImplications.at(j);
                NormFormula result;
                if (canSaturate(nf1, nf2, result)) {
                    if(result.premiseAt(0)==result.getConclusion())
                        continue;
                    bool exists = false;
                    for (size_t k = 0; k < simpleImplications.size(); k++) {
                        if (equalsUniv(result, simpleImplications.at(k))) {
                            exists = true;
                            break;
                        }
                    }
                    if (!exists) {
                        result.setName(nf2.getName() + "sat" + to_string(count++));
                        addFormula(result);
                        updated = true;
                    }
                }
            }
        }
    } while (updated);
    do {
        updated = false;
        for(size_t i = 0; i < simpleImplications.size(); i++) {
            const NormFormula nf1 = simpleImplications.at(i);
            const string predicate = nf1.premiseAt(0).getName();
            // search for fact
            auto curr = findFirst(predicate);
            while (curr != facts.end() && curr->getConclusion().getName() == predicate) {
                NormFormula result;
                if (canSaturate(nf1, *curr, result)) {
                    bool exists = facts.find(result) != facts.end();
                    if (!exists) {
                        result.setName(curr->getName() + "sat" + to_string(count++));
                        addFormula(result);
                        updated=true;
                    }
                }
                curr++;
            }
        }
    } while (updated);
}

bool Theory::canSaturate(const NormFormula &nf1, const NormFormula &nf2,
                 NormFormula &result) const {
    Atomic a1 = nf1.premiseAt(0);
    Atomic a2 = nf2.getConclusion();

    if (a1.getName() != a2.getName())
        return false;

    map<string, string> repl;

    for (size_t i = 0; i < a1.arity(); i++) {
        if (isConstant(a1.argAt(i))) {
            if (!isConstant(a2.argAt(i)) || a1.argAt(i) != a2.argAt(i))
                return false;
        } else if (repl.find(a1.argAt(i).getName()) != repl.end()) {
            if (repl[a1.argAt(i).getName()] != a2.argAt(i).getName())
                return false;
        } else
            repl[a1.argAt(i).getName()] = a2.argAt(i).getName();
    }

    Atomic replaced = nf1.getConclusion();
    for (size_t i = 0; i < replaced.arity(); i++) {
        if (repl.find(replaced.argAt(i).getName()) != repl.end())
            replaced.setArg(i, repl[replaced.argAt(i).getName()]);
    }

    result = nf2;
    result.setConclusion(replaced);
    return true;
}




