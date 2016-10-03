#include <iostream>
#include "stringset.h"

#include <string>
using namespace std;

int main() {

    stringset set;
    set.intern_stringset("Hello");
    set.intern_stringset("Hello2");
    set.intern_stringset("Hello3");
    set.intern_stringset("Hello4");
    set.intern_stringset("Hello5");
    set.intern_stringset("Hello6");
    set.intern_stringset("Hell");
    set.intern_stringset("Hel2");
    set.intern_stringset("He3");
    set.intern_stringset("H4");
    set.intern_stringset("ello5");
    set.intern_stringset("llo6");
    set.dump_stringset(stdout);

    return EXIT_SUCCESS;
}
