#include "stringset.h"

stringset::stringset() {

    stringset::string_set.max_load_factor(0.5);
}

const string* stringset::intern_stringset(const char* insert_string) {

    auto inserted = stringset::string_set.insert(insert_string);
    return &*inserted.first;
}

void stringset::dump_stringset(FILE*) {

    return;
}
