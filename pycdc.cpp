#include <cstring>
#include "ASTree.h"

#ifdef WIN32
#  define PATHSEP '\\'
#else
#  define PATHSEP '/'
#endif

bool block_DEBUG = false;
bool stack_DEBUG = false;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "No input file specified\n");
        return 1;
    }

    const char *filename = argv[1];
    if (strcmp(filename, "-d") == 0) {
        filename = argv[2];
        block_DEBUG = true;
        stack_DEBUG = true;
    }

    PycModule mod;
    mod.loadFromFile(filename);
    if (!mod.isValid()) {
        fprintf(stderr, "Could not load file %s\n", filename);
        return 1;
    }
    const char* dispname = strrchr(filename, PATHSEP);
    dispname = (dispname == NULL) ? filename : dispname + 1;
    fprintf(pyc_output, "# Source Generated with Decompyle++\n");
    fprintf(pyc_output, "# File: %s (Python %d.%d%s)\n\n", dispname, mod.majorVer(), mod.minorVer(),
            (mod.majorVer() < 3 && mod.isUnicode()) ? " Unicode" : "");
    decompyle(mod.code(), &mod);

    return 0;
}
