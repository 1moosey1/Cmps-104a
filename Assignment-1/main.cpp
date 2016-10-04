/* Juan Gonzalez
    1497521
    CMPS104a Assignment 1

    DEBUGGING
    -@
    @ - Enable all debug flags
    f - Debug filename
    o - Debug command line to pipe
*/

#include <iostream>
#include <string>
using namespace std;

#include <stdio.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>

#include "auxlib.h"
#include "stringset.h"

struct file_op {

    char* file_name;
    string commands = "cpp";
};

// Scans through command line options using optget(3)
void options(int argc, char* argv[], const char* options, file_op &ops) {

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
                ops.commands.append(" -D");
                ops.commands.append(optarg);
                ops.commands.append(" ");
                break;

            case '?':

                if(optopt == '@' || optopt == 'D')
                    fprintf(stderr, "The option -%c requires an argument\n", optopt);
                else
                    fprintf(stderr, "Invalid option: -%c\n", optopt);
        }
    }

    if(argc > optind) {

        DEBUGF('f', "argv[optind] = %s\n", argv[optind]);
        ops.file_name = &*argv[optind];
    }
    else
        ops.file_name = nullptr;
}

// Used to verify whether the file is a proper .oc
// Returns a bool true if valid - false if invalid
bool verify(char* file_name) {

    char* pos = strrchr(file_name, '.');
    DEBUGF('f', "File Verification: %d\n", pos && (strcmp(pos, ".oc") == 0));

    return pos && (strcmp(pos, ".oc") == 0);
}

int main(int argc, char* argv[]) {

    file_op ops;
    options(argc, argv, "ly@:D:", ops);
    DEBUGF('f', "File Name: %s\n", ops.file_name);
    if(!ops.file_name || !verify(ops.file_name)) {

        fprintf(stderr, "Invalid .oc program file or was not provided!");
        return EXIT_FAILURE;
    }

    ops.commands.append(ops.file_name);
    DEBUGF('o', "CPP command line: %s\n", ops.commands.c_str());

    //FILE* cpp = popen(ops.commands.c_str(), "r");
    //pclose(cpp);

    stringset set;

    return EXIT_SUCCESS;
}
