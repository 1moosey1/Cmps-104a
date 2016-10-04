// Juan Gonzalez
// 1497521
// CMPS104a Assignment 1

#include <iostream>
#include <string>
using namespace std;

#include <stdio.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>

#include "auxlib.h"
#include "stringset.h"

// Scans through command line options using optget(3)
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
        return argv[optind];

    return nullptr;
}

// Used to verify whether the file is a proper .oc
// Returns a bool true if valid - false if invalid
bool verify(char* file_name) {

    char* pos = strrchr(file_name, '.');
    DEBUGF('f', "File Verification: %d\n", pos && (strcmp(pos, ".oc") == 0));

    return pos && (strcmp(pos, ".oc") == 0);
}

int main(int argc, char* argv[]) {

    char* file_name = options(argc, argv, "ly@:D:");
    DEBUGF('f', "File Name: %s\n", file_name);
    if(!file_name || !verify(file_name)) {

        fprintf(stderr, "Invalid .oc program file or was not provided!");
        return EXIT_FAILURE;
    }

    //File* output = popen();

    stringset set;

    return EXIT_SUCCESS;
}
