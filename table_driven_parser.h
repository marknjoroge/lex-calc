#include <stdio.h>
#include "scanner.h"


typedef struct {
    char input;
    char lookahead;
    const char* production;
} parse_table_entry;
