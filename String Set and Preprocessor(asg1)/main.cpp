#include <iostream>
#include "stringset.h"

using namespace std;

int main() {

    stringset set;
    cout << set.intern_stringset("Hello") << endl;
    cout << set.intern_stringset("Hello2") << endl;
    cout << set.intern_stringset("Hello") << endl;

    return 0;
}
