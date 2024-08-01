#ifndef PROVER_H
#define PROVER_H

#include "theory.h"

class Prover
{
public:
    Prover(const Theory &t) {
        theory = t;
    }

    void initAxioms();
    bool prove();
    void generateFacts(NormFormula nf, set<NormFormula> &newFacts,
                       bool earlyChecked = false);
    bool canMerge(const NormFormula &nf, const NormFormula &f,
                  NormFormula &merged);

    Theory theory;
    set<Atomic> goals;

    unsigned appliedCounter = 0;
};

#endif // PROVER_H
