#include "prover.h"

string findParent(unordered_map<string, string>& parent, string x) {
    if (!parent[x].empty()) {
        parent[x] = findParent(parent, parent[x]);
    }
    return parent[x];
}

void Prover::initAxioms() {
    theory.initNormalized();

    theory.addEqSymAxiom();
    theory.addNEqSymAxiom();
    theory.addEqSubAxioms();

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
        goals.insert(theorem.premiseAt(i));
    }

    unsigned depth = 0;
    // todo newPredicates = occuringPredicates
    do {
        if (!newFacts.empty()) {
            theory.saturateFacts(newFacts);
            for (auto it = newFacts.begin(); it != newFacts.end(); it++) {
                theory.addFormula(*it);
                if (goals.find(it->getConclusion()) != goals.end())
                    goals.erase(it->getConclusion());
            }
        }
        // for (fact: newfacts) newPredicates.insert(fact)
        newFacts.clear();
        for (size_t i = 0; i < theory.complexAxioms.size(); i++) {
            // if (any premise name in newPredicates)
            generateFacts(theory.complexAxioms.at(i), newFacts);
        }
        // newPredicates.clear()
        depth++;
    } while (!goals.empty() && depth < 500 && !newFacts.empty());

    if (goals.empty()) {
        cout << "Proof successful!" << endl;
        return true;
    }

    cout << "Proof failed" << endl;
    theory.printFormulas();
    return false;

}

void Prover::generateFacts(NormFormula nf, set<NormFormula> &newFacts, bool earlyChecked) {
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
            nf.addUsedFact(it->getName());
            nf.popPremiseBack();
        } else return;
    }

    if (nf.numPremises() == 0) {
        if (!earlyChecked) {
            if(theory.facts.find(nf) != theory.facts.end() ||
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

    // univ variables from conclusion matching with constants in premise
    unordered_map<string, string> univToConst;
    for (size_t i = 0; i < premise.arity(); i++) {
        if (!theory.isConstant(premise.argAt(i))) continue;
        if (theory.isConstant(conc.argAt(i))) {
            if (premise.argAt(i) != conc.argAt(i))
                return false;
        } else if (univToConst.find(conc.argAt(i).getName()) !=
                   univToConst.end()) {
            if (univToConst[conc.argAt(i).getName()] != premise.argAt(i).getName())
                return false;
        } else {
            univToConst[conc.argAt(i).getName()] = premise.argAt(i).getName();
        }
    }

    // univ variables from premise matching with constants in conclusion
    unordered_map<string, string> replConst;

    // univ variables from conclusion matching with univ variables in premise
    unordered_map<string, unordered_set<string>> univToUniv;

    for (size_t i = 0; i < premise.arity(); i++) {
        if (theory.isConstant(premise.argAt(i))) continue;
        if (theory.isConstant(conc.argAt(i))) {
            if (replConst.find(premise.argAt(i).getName()) !=
                replConst.end()) {
                if (replConst[premise.argAt(i).getName()] != conc.argAt(i).getName())
                    return false;
            } else {
                replConst[premise.argAt(i).getName()] = conc.argAt(i).getName();
            }
        } else {
            if (univToConst.find(conc.argAt(i).getName()) != univToConst.end()) {
                if (replConst.find(premise.argAt(i).getName()) != replConst.end()) {
                    if (replConst[premise.argAt(i).getName()] !=
                        univToConst[conc.argAt(i).getName()])
                        return false;
                } else {
                    replConst[premise.argAt(i).getName()] =
                        univToConst[conc.argAt(i).getName()];
                }
            }
            univToUniv[conc.argAt(i).getName()].insert(premise.argAt(i).getName());
        }
    }
    // init parents map
    unordered_map<string, string> parents;
    for (auto it = univToUniv.begin(); it != univToUniv.end(); it++) {
        const unordered_set<string> &univSet = it->second;
        auto curr = univSet.begin();
        string first = *curr;
        curr++;
        while (curr != univSet.end()) {
            string root1 = findParent(parents, first);
            string root2 = findParent(parents, *curr);
            if (root1 != root2)
                parents[root2] = root1;
            curr++;
        }
    }
    // prefer to use univ vars with lower index
    unordered_set<string> pickedParents;
    for (size_t i = 0; i < nf.numUnivVars(); i++) {
        string univVar = nf.univVarAt(i);
        string par = findParent(parents, univVar);
        if (pickedParents.find(par) != pickedParents.end()) {
            if (univVar != par) {
                parents[univVar] = "";
                parents[par] = univVar;
            }
            pickedParents.insert(univVar);
        }
    }
    // update replConst for parents
    for (size_t i = 0; i < nf.numUnivVars(); i++) {
        string univVar = nf.univVarAt(i);
        string par = findParent(parents, univVar);
        if (univVar != par && replConst.find(univVar) != replConst.end()) {
            if (replConst.find(par) == replConst.end()) {
                replConst[par] = replConst[univVar];
            } else if (replConst[par] != replConst[univVar]) {
                return false;
            }
        }
    }

    vector<string> representatives;
    unordered_map<string, string> repl;
    for (size_t i = 0; i < nf.numUnivVars(); i++) {
        string univVar = nf.univVarAt(i);
        string par = findParent(parents, univVar);
        if (univVar == par) {
            if (replConst.find(univVar) != replConst.end())
                repl[univVar] = replConst[univVar];
            else
                representatives.push_back(univVar);
        } else {
            if (replConst.find(par) != replConst.end())
                repl[univVar] = replConst[par];
            else
                repl[univVar] = par;
        }
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
    merged.addUsedFact(f.getName());
    merged.addReplacements(repl);
    return true;
}


