#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ctype.h" 

#include "scanner.h"

char token_image[100];

token scan(FILE *fp) {
    static int c = ' ';
        /* next available char; extra (int) width accommodates EOF */
    int i = 0;              /* index into token_image */

    /* skip white space */
    while (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r') {
        c = getc(fp);
    }
    if (c == EOF)
        return eof;

    if (c == '/') {
        c = getc(fp);

        //  1st case: Check if multiline comment
        if(c == '*') {
            c = getc(fp);
            while (c != EOF) {
                if (c == '*') {
                    c = getc(fp);
                    if (c == '/') {
                        break;
                    }
                }
                c = getc(fp);
                printf("\n\t%c,",c);
            }
            if (c == EOF) {
                fprintf(stderr, "error: unexpected end of file inside comment\n");
                exit(1);
            }

            c = getc(fp);
            c = getc(fp);

            printf("%c,",c);
            // return comment;
        } 

        // 2nd case: Check if singleline comment
        else if (c == '/') {   
            c = getc(fp);
            while (c != '\n') {
                c = getc(fp);
            }
            return comment;
        } 
    }
    while (c == '\n') {
        c = getc(fp);
    }
    if (isalpha(c)) {
        do {
            token_image[i++] = c;
            c = getc(fp);
        } while (isalpha(c) || isdigit(c) || c == '_');
        token_image[i] = '\0';
        if (!strcmp(token_image, "read")) return read;
        else if (!strcmp(token_image, "write")) return write;
        else return id;
    }
    else if (isdigit(c)) {
        do {
            token_image[i++] = c;
            c = getc(fp);
        } while (isdigit(c));
        token_image[i] = '\0';
        return literal;
    } else switch (c) {
        case ':':
            if (c = getc(fp) != '=') {
                fprintf(stderr, "lexical error\n");
                exit(1);
            } else {
                c = getc(fp);
                return becomes;
            }
            break;
        case '+': c = getc(fp); return add;
        case '-': c = getc(fp); return sub;
        case '*': c = getc(fp); return mul;
        case '/': c = getc(fp); return quo;
        case '(': c = getc(fp); return lparen;
        case ')': c = getc(fp); return rparen;
        default:
            printf("lexical error\n");
            exit(1);
    }
}
