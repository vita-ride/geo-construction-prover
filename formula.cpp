#include "formula.h"

/*
 * Parts of this code used for parsing include and modify
 * code from the Larus repository.
 * Original source: https://github.com/janicicpredrag/Larus
 * Original author: [Predrag Janicic]
 * Original license: GPL-3.0
 */

enum TOKEN { eEXCLAM, eQUESTION, eCOLON, eOPENL, eCLOSEL, eEND, eERROR, eNUMBER, eEQ, eNEQ, eNEG, eFALSE, eTRUE, eIMPL, eCONJ, eDISJ, eID, eOPENB, eCOMMA, eCLOSEB, eOPENLIST, eCLOSELIST };

const char* TEXTSTREAM;
int TEXTINDEX;
enum TOKEN NEXTTOKEN;
string NEXTLEXEME;

bool onlyClosedBrackets() {
    int i=TEXTINDEX;
    while(TEXTSTREAM[i] != '\0') {
        if (TEXTSTREAM[i] != ')' &&
            !isspace(TEXTSTREAM[i]))
            return false;
        i++;
    }
    return true;
}

void ReadNextToken() {
    if (TEXTSTREAM[TEXTINDEX] == '\0') {
        NEXTTOKEN = eEND;
        return;
    }
    while (TEXTSTREAM[TEXTINDEX] != '\0' && isspace(TEXTSTREAM[TEXTINDEX])) {
        TEXTINDEX++;
    }

    NEXTLEXEME = "";
    if (isalpha(TEXTSTREAM[TEXTINDEX]) || TEXTSTREAM[TEXTINDEX]=='_' || TEXTSTREAM[TEXTINDEX]=='$') {
        while (isalnum(TEXTSTREAM[TEXTINDEX]) || TEXTSTREAM[TEXTINDEX]=='_' || TEXTSTREAM[TEXTINDEX]=='$' || isdigit(TEXTSTREAM[TEXTINDEX])) {
            NEXTLEXEME += TEXTSTREAM[TEXTINDEX];
            TEXTINDEX++;
        }
        NEXTTOKEN = eID;
        TEXTINDEX--;
    }
    else if (isdigit(TEXTSTREAM[TEXTINDEX]) || TEXTSTREAM[TEXTINDEX]=='#') {
        while (isdigit(TEXTSTREAM[TEXTINDEX]) || TEXTSTREAM[TEXTINDEX]=='#' || TEXTSTREAM[TEXTINDEX]=='x'
               || (TEXTSTREAM[TEXTINDEX]>='a' && TEXTSTREAM[TEXTINDEX]<='f')) {
            NEXTLEXEME += TEXTSTREAM[TEXTINDEX];
            TEXTINDEX++;
        }
        NEXTTOKEN = eNUMBER;
        TEXTINDEX--;
    }
    else {
        switch(TEXTSTREAM[TEXTINDEX]) {
        case '=':
            if (TEXTSTREAM[TEXTINDEX+1]=='>') {
                TEXTINDEX++;
                NEXTTOKEN = eIMPL;
            }
            else
                NEXTTOKEN = eEQ;
            break;

        case '!':
            if (TEXTSTREAM[TEXTINDEX+1]=='=') {
                TEXTINDEX++;
                NEXTTOKEN = eNEQ;
            }
            else
                NEXTTOKEN = eEXCLAM;
            break;

        case '?':
            NEXTTOKEN = eQUESTION;
            break;
        case '&':
            NEXTTOKEN = eCONJ;
            break;
        case '~':
            NEXTTOKEN = eNEG;
            break;
        case '|':
            NEXTTOKEN = eDISJ;
            break;
        case '(':
            NEXTTOKEN = eOPENB;
            break;
        case ')':
            NEXTTOKEN = eCLOSEB;
            break;
        case '[':
            NEXTTOKEN = eOPENL;
            break;
        case ']':
            NEXTTOKEN = eCLOSEL;
            break;
        case ',':
            NEXTTOKEN = eCOMMA;
            break;
        case ':':
            NEXTTOKEN = eCOLON;
            break;
        default:
            NEXTTOKEN = eEND;
            break;
        }
    }
    TEXTINDEX++;
    return;
}


bool Term::read()
{
    if (NEXTLEXEME == "$plus_int" || NEXTLEXEME == "$minus_int" || NEXTLEXEME == "$times_int")
        return false;

    name = NEXTLEXEME;

    ReadNextToken();

    if (NEXTTOKEN == eOPENB) // functional symbols unsupported
        return false;

    return true;
}

bool Atomic::read() {
    int TMP_TEXTINDEX = TEXTINDEX;
    enum TOKEN TMP_NEXTTOKEN = NEXTTOKEN;
    string TMP_NEXTLEXEME = NEXTLEXEME;

    if (NEXTTOKEN == eOPENB) {
        ReadNextToken();
        if (read() && NEXTTOKEN == eCLOSEB) {
            ReadNextToken();
            return true;
        }
    }
    TEXTINDEX = TMP_TEXTINDEX;
    NEXTTOKEN = TMP_NEXTTOKEN;
    NEXTLEXEME = TMP_NEXTLEXEME;

    if (NEXTTOKEN == eNEG) {
        ReadNextToken();
        if (!read())
            return false;
        name = PREFIX_NEGATED + name;
        return true;
    }

    args.clear();
    if (NEXTLEXEME == "false" || NEXTLEXEME == "$false") {
        name = sBOT;
        ReadNextToken();
        return true;
    }
    if (NEXTLEXEME == "true" || NEXTLEXEME == "$true") {
        name = sTOP;
        ReadNextToken();
        return true;
    }

    TMP_TEXTINDEX = TEXTINDEX;
    TMP_NEXTTOKEN = NEXTTOKEN;
    TMP_NEXTLEXEME = NEXTLEXEME;

    Term tL, tR;
    if (tL.read()) {
        if (NEXTTOKEN == eEQ || NEXTTOKEN == eNEQ ) {
            bool bEq = (NEXTTOKEN == eEQ);
            ReadNextToken();
            if (tR.read()) {
                name = bEq ? EQ_NATIVE_NAME : PREFIX_NEGATED + EQ_NATIVE_NAME;
                args.push_back(tL);
                args.push_back(tR);
                return true;
            }
        }
    }

    TEXTINDEX = TMP_TEXTINDEX;
    NEXTTOKEN = TMP_NEXTTOKEN;
    NEXTLEXEME = TMP_NEXTLEXEME;

    name = NEXTLEXEME;
    ReadNextToken();

    if (NEXTTOKEN == eOPENB) {
        ReadNextToken();
        while (NEXTTOKEN == eID) {
            Term t;
            t.read();
            args.push_back(t);
            if (NEXTTOKEN!=eCOMMA && NEXTTOKEN!=eCLOSEB)
                return false;
            if (NEXTTOKEN == eCLOSEB) {
                ReadNextToken();
                if (NEXTTOKEN == eEQ || NEXTTOKEN == eNEQ) {
                    break;
                }
            } else
                ReadNextToken();
        }
        //if (NEXTTOKEN != eEQ && NEXTTOKEN != eNEQ)
        return true;
    }

    TEXTINDEX = TMP_TEXTINDEX;
    NEXTTOKEN = TMP_NEXTTOKEN;
    NEXTLEXEME = TMP_NEXTLEXEME;

    args.clear();
    Term t1;
    if (!t1.read()) {
        TEXTINDEX = TMP_TEXTINDEX;
        NEXTTOKEN = TMP_NEXTTOKEN;
        NEXTLEXEME = TMP_NEXTLEXEME;
        ReadNextToken();
        args.clear();
        return true;
    }
    args.push_back(t1);
    if (NEXTTOKEN == eEQ)
        name = EQ_NATIVE_NAME;
    else if (NEXTTOKEN == eNEQ)
        name = PREFIX_NEGATED + EQ_NATIVE_NAME;
    else {
        TEXTINDEX = TMP_TEXTINDEX;
        NEXTTOKEN = TMP_NEXTTOKEN;
        NEXTLEXEME = TMP_NEXTLEXEME;
        ReadNextToken();
        args.clear();
        return true;
    }
    ReadNextToken();
    Term t2;
    if (!t2.read())
        return false;
    args.push_back(t2);

    return true;
}

bool Conjunction::read(bool conclusion) {
    int TMP_TEXTINDEX = TEXTINDEX;
    enum TOKEN TMP_NEXTTOKEN = NEXTTOKEN;
    string TMP_NEXTLEXEME = NEXTLEXEME;

    if (NEXTTOKEN == eOPENB) {
        ReadNextToken();
        if (read(conclusion) && NEXTTOKEN == eCLOSEB && (!conclusion || onlyClosedBrackets())) {
            ReadNextToken();
            if (NEXTTOKEN != eCONJ)
                return true;
        }
    }

    clear();
    TEXTINDEX = TMP_TEXTINDEX;
    NEXTTOKEN = TMP_NEXTTOKEN;
    NEXTLEXEME = TMP_NEXTLEXEME;

    Atomic a;
    while (a.read()) {
        add(a);
        a.clear();
        if (NEXTTOKEN != eCONJ)
            break;
        ReadNextToken();
    }
    return conclusion ? (NEXTTOKEN == eCLOSEB || NEXTTOKEN == eEND) : true;
}


bool Formula::read() {
    if (!readWithoutCheckingBoundness())
        return false;

    // Check if all variables in the premises are bound
    for(unsigned i = 0; i < premises.size(); i++) {
        for(unsigned j = 0; j < premises.at(i).arity(); j++) {
            Term t = premises.at(i).argAt(j);
            bool foundArg = false;

            for (unsigned l = 0; l < numUnivVars() && !foundArg; l++) {
                if (t.getName() == univVarAt(l)) {
                    foundArg = true;
                }
            }
            if (!foundArg && 'A' <= t.getName()[0] && t.getName()[0] <= 'Z') {
                return false;
            }
        }
    }

    for(unsigned i = 0; i < conclusion.size(); i++) {
        for(unsigned j = 0; j < conclusion.at(i).arity(); j++) {
            Term t = conclusion.at(i).argAt(j);
            bool foundArg = false;

            for (unsigned l = 0; l < numUnivVars() && !foundArg; l++) {
                if (t.getName() == univVarAt(l)) {
                    foundArg = true;
                }
            }
            if (!foundArg && 'A' <= t.getName()[0] && t.getName()[0] <= 'Z') {
                return false;
            }

        }
    }

    // Check if all universally quantified variables are used
    for (unsigned l = 0; l < numUnivVars(); l++) {
        string var = univVarAt(l);
        bool foundVar = false;
        for(unsigned i = 0; i < premises.size() && !foundVar; i++) {
            for(unsigned j = 0; j < premises.at(i).arity()  && !foundVar; j++) {
                Term t = premises.at(i).argAt(j);
                if (var == t.getName()) {
                    foundVar = true;
                }

            }
        }
        for(unsigned i = 0; i < conclusion.size() && !foundVar; i++) {
            for(unsigned j = 0; j < conclusion.at(i).arity()  && !foundVar; j++) {
                Term t = conclusion.at(i).argAt(j);
                if (var == t.getName()) {
                    foundVar = true;
                }

            }
        }

        if (!foundVar) {
            return false;
        }
    }

    return true;
}

bool Formula::readUnivVars() {
    if (NEXTTOKEN == eEXCLAM) {
        ReadNextToken();
        if (NEXTTOKEN != eOPENL) {
            return false;
        }
        clearUnivVars();
        ReadNextToken();
        while (NEXTTOKEN == eID) {
            addUnivVar(NEXTLEXEME);
            ReadNextToken();
            if (NEXTTOKEN!=eCOMMA && NEXTTOKEN!=eCLOSEL)
                return false;
            if (NEXTTOKEN==eCLOSEL) {
                ReadNextToken();
                break;
            }
            ReadNextToken();
        }
        if (NEXTTOKEN != eCOLON)
            return false;
        ReadNextToken();
        return true;
    }
    return false;
}


bool Formula::readImplication() {
    int TMP_TEXTINDEX = TEXTINDEX;
    enum TOKEN TMP_NEXTTOKEN = NEXTTOKEN;
    string TMP_NEXTLEXEME = NEXTLEXEME;

    if (NEXTTOKEN == eOPENB) {
        ReadNextToken();
        if (readImplication() && NEXTTOKEN == eCLOSEB &&
            onlyClosedBrackets()) {
            ReadNextToken();
            return true;
        }
    }
    TEXTINDEX = TMP_TEXTINDEX;
    NEXTTOKEN = TMP_NEXTTOKEN;
    NEXTLEXEME = TMP_NEXTLEXEME;

    premises.clear();
    conclusion.clear();
    if (!premises.read())
        return false;
    if (NEXTTOKEN == eIMPL) {
        ReadNextToken();
        if (conclusion.read(true))
            return true;
    } else {
        TEXTINDEX = TMP_TEXTINDEX;
        NEXTTOKEN = TMP_NEXTTOKEN;
        NEXTLEXEME = TMP_NEXTLEXEME;

        premises.clear();
        conclusion.clear();
        if (conclusion.read(true))
            return true;
    }
    return false;
}

bool Formula::readWithoutCheckingBoundness() {
    int TMP_TEXTINDEX = TEXTINDEX;
    enum TOKEN TMP_NEXTTOKEN = NEXTTOKEN;
    string TMP_NEXTLEXEME = NEXTLEXEME;

    if (NEXTTOKEN == eOPENB) {
        ReadNextToken();
        if (readWithoutCheckingBoundness()
            && (NEXTTOKEN == eCLOSEB || NEXTTOKEN == eEND)
            && onlyClosedBrackets()) {
            ReadNextToken();
            return true;
        }
    }
    TEXTINDEX = TMP_TEXTINDEX;
    NEXTTOKEN = TMP_NEXTTOKEN;
    NEXTLEXEME = TMP_NEXTLEXEME;

    if (readUnivVars()) {
        return readWithoutCheckingBoundness();
    }
    return readImplication();
}

bool Formula::readTPTPStatement(const string &s, string &name, fofType &type) {
    size_t pos1, pos2;
    string ss = skipChar(s, ' ');

    clear();
    if (ss.substr(0, 4) != "fof(") {
        return false;
    }
    pos1 = ss.find(',');
    if (pos1 == string::npos) {
        return false;
    }
    name = ss.substr(4, pos1 - 4);
    pos2 = ss.find(',', pos1 + 1);
    if (pos2 == string::npos) {
        return false;
    }
    string s1 = ss.substr(pos1 + 1, pos2 - pos1 - 1);
    if (type == eAxiom && s1 != string("axiom")) {
        return false;
    }
    if (type == eConjecture && s1 != string("conjecture")) {
        return false;
    }
    if (s1 == string("axiom"))
        type = eAxiom;
    else if (s1 == string("conjecture"))
        type = eConjecture;
    else
        return false;

    ss = ss.substr(pos2 + 1, ss.size() - pos2 - 2);

    TEXTSTREAM = ss.c_str();
    TEXTINDEX = 0;
    ReadNextToken();
    if (read()) {
        return true;
    } else {
        cout << "Input error: axiom: " << name << " : " << *this;
        cout << " gives ill-formed CL formula! " << endl << endl;
        return false;
    }
}


int Formula::univVarIndex(string v) const {
    for (size_t i = 0; i < numUnivVars(); i++)
        if (v == univVarAt(i))
            return i;
    return -1;
}


bool NormFormula::isFact() const {
    return numPremises() == 0;
}

bool NormFormula::isSimpleImplication() const {
    return numPremises() == 1;
}



