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

    char * file_name;
    string commands = "cpp ";
};

// Scans through command line options using optget(3)
void options( int argc, char * argv[],
    const char * options, file_op &ops ) {

    int op;
    while ( (op = getopt( argc, argv, options )) != -1 ) {

        switch ( op ) {

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
                ops.commands.append("-D ");
                ops.commands.append(optarg );
                ops.commands.append(" ");
                break;

            case '?':

                if ( optopt == '@' || optopt == 'D' )
                    fprintf(stderr, "-%c needs an argument\n", optopt);
                else
                    fprintf(stderr, "Invalid option: -%c\n", optopt);
        }
    }

    if ( argc > optind ) {

        DEBUGF( 'f', "argv[optind] = %s\n", argv[optind] );
        ops.file_name = &*argv[optind];
    }
    else
        ops.file_name = nullptr;
}

// Used to verify whether the file is a proper .oc
// Returns a bool true if valid - false if invalid
bool verify( char * file_name ) {

    char * pos = strrchr(file_name, '.');

    bool check = pos && (strcmp(pos, ".oc") == 0);
    DEBUGF( 'f', "File Verification: %d\n", check );

    return check;
}

void read_pipe( const char * cmd_line, stringset &set ) {

    FILE * cpp = popen(cmd_line, "r");
    if ( !cpp ) {

        fprintf(stderr, "Error running cpp!");
        set_exitstatus( EXIT_FAILURE );
        return;
    }

    int line_size = 1024;
    char linein[line_size], *token, *saveptr;

    while ( fgets( linein, line_size, cpp ) ) {

        DEBUGF( 'o', "Line read in (fgets) -> %s\n", linein );

        token = strtok_r(linein, " \t\n", &saveptr);
        while ( token ) {

            DEBUGF( 'o', "Token -> %s\n", token );

            if ( strcmp ( "#", token ) == 0 ) break;
            set.intern_stringset( token );
            token = strtok_r(nullptr, " \t\n", &saveptr);
        }
    }

    pclose(cpp);
}

void write_file( char * path, string extension, stringset set ) {

    string file_name = path;
    file_name = file_name.substr(0, file_name.find_last_of('.'));
    DEBUGF('f', "Basename: %s\n", file_name.c_str());

    file_name.append(extension);
    DEBUGF('f', "Writing to file -> %s\n", file_name.c_str());

    FILE * output = fopen(file_name.c_str(), "w");
    set.dump_stringset(output);
    fclose(output);
}

int main( int argc, char * argv[] ) {

    file_op ops;
    options(argc, argv, "ly@:D:", ops);
    DEBUGF( 'f', "File Name: %s\n", ops.file_name );
    if ( !ops.file_name || !verify(ops.file_name) ) {

        fprintf(stderr, "Invalid .oc file or was not provided!");
        set_exitstatus( EXIT_FAILURE );
        return get_exitstatus();
    }

    ops.commands.append(ops.file_name);
    DEBUGF( 'o', "CPP command line: %s\n", ops.commands.c_str() );

    stringset set;
    read_pipe(ops.commands.c_str(), set);
    write_file(ops.file_name, ".str", set);

    return get_exitstatus();
}
