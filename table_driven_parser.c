#include <stdio.h>
#include <stdlib.h>

#include "table_driven_parser.h"
#include "parser.h"

const char* production_rules[] = {
    "program -> stmt_list",
    "stmt_list -> stmt_list stmt",
    "stmt_list -> stmt",
    "stmt -> id := expr",
    "stmt -> read id",
    "stmt -> write expr",
    "expr -> expr addop term", 
    "expr -> term",
    "term -> term mulop factor",
    "term -> factor",
    "factor -> ( expr )",
    "factor -> id",
    "factor -> literal",
    "addop -> +",
    "addop -> -",
    "mulop -> *",
    "mulop -> /"
};

const int rhs_length[] = {1, 2, 1, 3, 2, 2, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1};

int parsing_table[12][12] = {
    // read  write   id     lit    bec    +      -     *     /     (     )     $$
    {   2,     2,     1,     1,    -1,    3,     3,    3,    3,    1,    -1,    1 }, // program
    {   4,     4,     4,     4,    -1,    4,     4,    4,    4,    4,    -1,   -1 }, // stmt_list
    {   5,     6,     5,     5,    -1,   -1,    -1,   -1,   -1,    5,    -1,   -1 }, // stmt
    {   7,     7,     7,     7,    -1,   -1,    -1,   -1,   -1,    7,    -1,   -1 }, // expr
    {   9,     9,     8,     8,    -1,   9,     9,    9,    9,    8,    -1,   -1 }, // term_tail
    {  -1,    -1,     8,     8,    -1,  -1,    -1,   -1,   -1,    8,    -1,   -1 }, // term
    {  11,    11,    10,    10,    -1,  11,    11,   11,   11,   10,    -1,   -1 }, // factor_tail
    {  -1,    -1,    13,    14,    -1,  -1,    -1,   -1,   -1,   12,    -1,   -1 }, // factor
    {  -1,    -1,    -1,    -1,    15,  -1,    -1,   -1,   -1,   -1,    -1,   -1 }, // add_op
    {  -1,    -1,    -1,    -1,    16,  -1,    -1,   -1,   -1,   -1,    -1,   -1 }  // mult_op
};

FILE *input_file;

void parse(FILE *inputFile) {
    #include <stdio.h>

    printf("    | read | write |  id  | lit  | bec  |  +   |  -   |  *   |  /   |  (   |  )   |  $$  |\n");
    printf("----|------|-------|------|------|------|------|------|------|------|------|------|------|\n");
    for(int i=0; i<12; i++) {
        printf("%-4s|", i==0 ? "prog" : (i==1 ? "stmt_list" : (i==2 ? "stmt" : (i==3 ? "expr" : (i==4 ? "term_tail" : (i==5 ? "term" : (i==6
    
    // print footer row
    printf("+------+------+------+\n");
}

void parser(FILE *inputFile) {
    int stack[100];
    int top = -1;
    stack[++top] = eof;
    stack[++top] = 1;
    token current_token = scan(inputFile);

    while (top >= 0) {
        int X = stack[top--];
        if (X == current_token) {
            current_token = scan(inputFile);
        } else if (X < 100) {
            fprintf(stderr, "Syntax error: unexpected token %d\n", current_token);
            exit(1);
        } else if (parsing_table[X - 100][current_token] == 0) {
            fprintf(stderr, "Syntax error: unexpected token %d\n", current_token);
            exit(1);
        } else {
            int rule = parsing_table[X - 100][current_token];
            int i;
            for (i = 17; i > 0; i--) {
                stack[++top] = parsing_table[rule - 1][i];
            }
        }
    }
    printf("Parsing successful!\n");
}

int main(int argc, char *argv[]) {

    input_file = fopen(argv[1], "r");

    // parse(input_file);
    printf(argv[1]);
}