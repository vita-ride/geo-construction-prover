#include "prover.h"
string findParent(unordered_map<string, string>& parent, string x) {
    if (parent[x].empty())
        return x;
    parent[x] = findParent(parent, parent[x]);
    return parent[x];
}

void Prover::initAxioms() {
    theory.initNormalized();

    theory.addEqSymAxiom();
    theory.addNEqSymAxiom();
    theory.addEqReflAxiom();
    theory.addEqSubAxioms();
    theory.addNegAxioms();

    theory.saturate();
}

bool Prover::prove() {
    cout << "Theorem to prove:" << endl << "\t" << theory.getTheorem().second
         << ": " << theory.getTheorem().first << endl
         << "Assumptions:" << endl;

    Formula theorem = theory.getTheorem().first;
    set<NormFormula> newFacts;

    for (size_t i = 0; i < theorem.numPremises(); i++) {
        Atomic a = theorem.premiseAt(i);
        NormFormula nf;
        nf.setConclusion(a);
        nf.setName("theorem_assume" + to_string(i));

        cout << "\t" << a << endl;
        newFacts.insert(nf);
    }
    cout << "It should be proved that:" << endl;
    for (size_t i = 0; i < theorem.numConclusions(); i++) {
        cout << "\t" << theorem.conclusionAt(i) << endl;
        goals.insert(theorem.conclusionAt(i));
    }

    unsigned depth = 0;
    bool contradiction = false;
    do {
        if (!newFacts.empty()) {
            theory.saturateFacts(newFacts);
            for (auto it = newFacts.begin(); it != newFacts.end(); it++) {
                theory.addFormula(*it);
                if (it->getConclusion().getName() == sBOT) {
                    contradiction = true;
                    theory.setContradictionName(it->getName());
                    break;
                }
                if (goals.find(it->getConclusion()) != goals.end()) {
                    goals.erase(it->getConclusion());
                    theory.addGoalName(it->getName());
                }
            }
        }
        newFacts.clear();
        if (!contradiction)
            for (size_t i = 0; i < theory.complexAxioms.size(); i++) {
                generateFacts(theory.complexAxioms.at(i), newFacts);
            }
        depth++;
    } while (!goals.empty() && depth < MAX_SEARCH_DEPTH && !newFacts.empty() && !contradiction);

    if (goals.empty()) {
        cout << "Proof successful!" << endl;
        theory.printProof();
        return true;
    } else {
        cout << "Proof failed: ";
        if (contradiction) {
            cout << "arrived at contradiction:" << endl;
            theory.printProof(true);
        } else {
            if (depth >= MAX_SEARCH_DEPTH) {
                cout << "maximum depth exceeded." << endl;
            } else {
                cout << "reached fixed point." << endl;
            }
            cout << "Unproven goals:" << endl;
            for (const Atomic goal : goals) {
                cout << goal << endl;
            }
        }
    }
    return false;
}

void Prover::generateFacts(NormFormula nf, set<NormFormula> &newFacts,
                           bool earlyChecked) {
    // early stopping
    if (nf.getConclusion().getName() == EQ_NATIVE_NAME &&
        nf.getConclusion().argAt(0) == nf.getConclusion().argAt(1))
        return;
    if (!earlyChecked && nf.numUnivVars() == 0) {
        NormFormula check;
        check.setConclusion(nf.getConclusion());
        if (theory.facts.find(check) != theory.facts.end())
            return;
        if (newFacts.find(check) != newFacts.end())
            return;
        earlyChecked = true;
    }

    while (nf.numPremises() > 0) {
        Atomic a = nf.premiseBack();
        if (a == nf.getConclusion())
            return;
        bool hasUnivVars = false;
        if (nf.numUnivVars() > 0) {
            for (size_t i = 0; i < a.arity(); i++) {
                if (!theory.isConstant(a.argAt(i))) {
                    hasUnivVars = true;
                    break;
                }
            }
            if (hasUnivVars)
                break;
        }
        NormFormula searchFor;
        searchFor.setConclusion(a);
        auto it = theory.facts.find(searchFor);
        if (it != theory.facts.end()) {
            nf.addUsedFact(pair(it->getName(), it->simpleString()));
            nf.popPremiseBack();
        } else break;
    }

    if (nf.numPremises() == 0) {
        if (!earlyChecked) {
            if (theory.facts.find(nf) != theory.facts.end() ||
                newFacts.find(nf) != newFacts.end())
                return;
        }

        string oldName = nf.getName();
        nf.setName(oldName + "applied" + to_string(appliedCounter++));
        newFacts.insert(nf);
        theory.addOrigin(nf, oldName);
        return;
    }

    const string predicate = nf.premiseBack().getName();
    auto curr = findFirst(theory.facts, predicate);

    while (curr != theory.facts.end() && curr->getConclusion().getName() == predicate) {
        NormFormula merged;
        if (canMerge(nf, *curr, merged)) {
            generateFacts(merged, newFacts, earlyChecked);
        }
        curr++;
    }
}

bool Prover::canMerge(const NormFormula &nf, const NormFormula &f, NormFormula &merged) {
    Atomic premise = nf.premiseBack();
    Atomic conc = f.getConclusion();

    UnionManager um;

    for (size_t i = 0; i < premise.arity(); i++) {
        Term arg1 = premise.argAt(i);
        Term arg2 = conc.argAt(i);

        if (theory.isConstant(arg1)) {
            if (theory.isConstant(arg2)) {
                if (arg1 != arg2)
                    return false;
            } else {
                if (!um.addConstant(arg2.getName(), arg1.getName(), true))
                    return false;
            }
        } else {
            if (theory.isConstant(arg2)) {
                if (!um.addConstant(arg1.getName(), arg2.getName()))
                    return false;
            } else {
                if (!um.makeUnion(arg1.getName(), arg2.getName()))
                    return false;
            }
        }
    }

    unordered_map<string,string> repl = um.getReplacements(nf.getUnivVars());
    vector<string> representatives;

    for (size_t i = 0; i < nf.numUnivVars(); i++) {
        if (repl.find(nf.univVarAt(i)) == repl.end())
            representatives.push_back(nf.univVarAt(i));
    }

    Conjunction mergedPremises;
    for (size_t i = 0; i < nf.numPremises() - 1; i++) {
        Atomic a = nf.premiseAt(i);
        for (size_t j = 0; j < a.arity(); j++) {
            if (repl.find(a.argAt(j).getName()) != repl.end()) {
                a.setArg(j, repl[a.argAt(j).getName()]);
            }
        }
        mergedPremises.add(a);
    }

    Atomic mergedConclusion = nf.getConclusion();
    for (size_t i = 0; i < mergedConclusion.arity(); i++) {
        if (repl.find(mergedConclusion.argAt(i).getName()) != repl.end()) {
            mergedConclusion.setArg(i, repl[mergedConclusion.argAt(i).getName()]);
        }
    }

    merged.setPremises(mergedPremises);
    merged.setConclusion(mergedConclusion);
    merged.setUnivVars(representatives);
    merged.setName(nf.getName());
    merged.copyOrigin(nf);
    merged.addUsedFact(pair(f.getName(), f.simpleString()));
    merged.addReplacements(repl);

    return true;
}


string UnionManager::representative(const string &name, bool fact){
    string x = fact ? secondaryPrefix + name : name;
    if (parent.find(x) == parent.end())
        return x;
    parent[x] = representative(parent[x]);
    return parent[x];
}

bool UnionManager::makeUnion(const string &a, const string &b){
    string reprA = representative(a);
    string reprB = representative(b, true);

    if (reprA == reprB)
        return true;

    if (reprA[0] == constantPrefix) {
        if (reprB[0] == constantPrefix) {
            return false;
        }
    } else if (reprB[0] == constantPrefix) {
        parent[reprA] = reprB;
        return true;
    }

    parent[reprB] = reprA;
    return true;
}

bool UnionManager::addConstant(const string &var, const string &c, bool fact){
    string repr = representative(var, fact);
    string constantName = constantPrefix + c;

    if (repr == constantName)
        return true;

    if (repr[0] == constantPrefix)
        return false;

    parent[repr] = constantName;
    return true;
}

unordered_map<string,string> UnionManager::getReplacements(const vector<string> &vars) {
    unordered_map<string,size_t> varIndex;
    for (size_t i = 0; i < vars.size(); i++) {
        varIndex[vars.at(i)] = i;
    }

    unordered_map<string,string> replacements;
    for (size_t i = 0; i < vars.size(); i++) {
        string var = vars.at(i);
        string repr = representative(var);

        if (var == repr)
            continue;

        if (repr[0] == constantPrefix) {
            replacements[var] = repr.substr(1, repr.length()-1);
        } else {
            if (i < varIndex[repr]) {
                parent.erase(var);
                parent[repr] = var;
            } else {
                replacements[var] = repr;
            }
        }
    }
    return replacements;
}


