// Juan Gonzalez
// 1497521
// CMPS104a Assignment 1
// Modified from Wesley Mackey's stringset.h

#ifndef __STRING_SET__
#define __STRING_SET__

#include <string>
#include <unordered_set>
using namespace std;

#include <stdio.h>

class stringset {

    public:

        stringset();
        const string* intern_stringset (const char*);
        void dump_stringset (FILE*);

    private:
        unordered_set<string> string_set;
};

#endif // __STRING_SET__
