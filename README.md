# geo-construction-prover
A prover for a subset of coherent logic where implications have conjunctions of atomic formulas on both sides, **without disjunctions or existential quantifiers.**
Designed to verify the correctness of geometric constructions. Made for **ArgoTriCS**, a program that generates triangle constructions based on given points.

## Build
To build, type the following commands in the root folder:
```
mkdir build
cd build
cmake ..
cmake --build .
```

## Input
The supported input format is a subset of the standard TPTP FOF format, where formulas **don't have any disjunctions or existential quantifiers.**

## Usage
`./geoprover filename`
