#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "parser.h"
#include "scanner.h"


typedef struct {
    char input;
    char lookahead;
    const char* production;
} parse_table_entry;

#endif /* PARSER_H */