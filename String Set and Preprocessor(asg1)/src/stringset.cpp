#include "stringset.h"

stringset::stringset() {

    stringset::string_set.max_load_factor(0.5);
}

const string* stringset::intern_stringset(const char* insert_string) {

    auto inserted = stringset::string_set.insert(insert_string);
    return &*inserted.first;
}

void stringset::dump_stringset(FILE* out) {

    unordered_set<string>::hasher set_hash_fn
        = stringset::string_set.hash_function();

    bool display_index;
    size_t max_bucket_depth = 0,
        curr_bucket_depth = 0;

    for(size_t i = 0; i < stringset::string_set.bucket_count(); ++i) {

        curr_bucket_depth = stringset::string_set.bucket_size(i);
        if(curr_bucket_depth > max_bucket_depth)
            max_bucket_depth = curr_bucket_depth;

        display_index = true;
        for(auto itor = stringset::string_set.cbegin(i);
            itor != stringset::string_set.cend(i); ++itor) {

            if(display_index) {

                fprintf(out, "string_set[ %4zu]: ", i);
                display_index = false;
            }
            else
                fprintf(out, "            %4s   ", "");

            const string* str = &*itor;
            fprintf(out, "%22zu %p->\"%s\"\n", set_hash_fn(*str),
                str, str->c_str());
        }
    }

    fprintf(out, "load_factor = %.3f\n", stringset::string_set.load_factor());
    fprintf(out, "bucket_count = %zu\n", stringset::string_set.bucket_count());
    fprintf(out, "max_bucket_size = %zu\n", max_bucket_depth);
}
