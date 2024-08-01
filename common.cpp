#include "common.h"

string skipChar(const string &str, char c) {
    string out;
    size_t slen = str.size();
    for (size_t i = 0; i < slen; i++) {
        if (str[i] != c)
            out += str[i];
    }
    return out;
}
