#include <iostream>
#include <string>
#include "hash.h"
#include <cmath>

using namespace std;

int hash_function(string text, int k) {
    if (k <= 0) return 0;
    unsigned long total = 0;
    for (int i = 0; i < (int)text.size(); ++i) {
        char c = text[i];
        // manual tolower (no <cctype>)
        if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
        total += (unsigned long)(unsigned char)c * (unsigned long)(i + 1);
    }
    return (int)(total % (unsigned long)k);
}