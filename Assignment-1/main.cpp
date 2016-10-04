#include <iostream>
#include <string>
using namespace std;

#include <stdio.h>
#include <unistd.h>

#include "auxlib.h"
#include "stringset.h"

char* options(int argc, char* argv[], const char* options) {

    int op;
    while( (op = getopt(argc, argv, options)) != -1) {

        switch(op) {

            case 'l':
                //Debug yylex() with yy_flex_debug = 1;
                break;

            case 'y':
                //Debug yyparse() with yydebug = 1
                break;

            case '@':
                set_debugflags(optarg);
                break;

            case 'D':
                //Implement --- Pass option and argument to cpp
                break;

            case '?':

                if(optopt == '@' || optopt == 'D')
                    fprintf(stderr, "The option -%c requires an argument\n", optopt);
                else
                    fprintf(stderr, "Invalid option: -%c\n", optopt);
        }
    }

    if(argc > optind)
        fprintf(stdout, "The extra argument is -> %s\n", argv[optind]);

    return nullptr;
}

int main(int argc, char* argv[]) {

    options(argc, argv, "ly@:D:");
    stringset set;

    return EXIT_SUCCESS;
}
