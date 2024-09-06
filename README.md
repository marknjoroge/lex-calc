# Simple Compiler Documentation

## Overview

This document describes a simple compiler implemented in C for a basic language that can perform read operations, arithmetic calculations, and write operations. The compiler consists of three main components: a scanner, a parser, and a table-driven parser.

The compiler is designed to process programs with the following structure:

```
/* prog1 */
read a
read b
area := a * b
perimeter := 2 * (a + b)
write area
write perimeter
```
### Running

Give execute permission to the script

```sh
chmod +x parser.sh
```

Then run

```sh
./parser.sh
```

## 1. Scanner

The scanner, also known as a lexical analyzer, is responsible for breaking down the input program into a series of tokens.

### Tokens

The scanner recognizes the following tokens:

- Keywords: `read`, `write`
- Identifiers: Variable names (e.g., `a`, `b`, `area`, `perimeter`)
- Operators: `:=` (assignment), `*` (multiplication), `+` (addition)
- Literals: Integer constants (e.g., `2`)
- Special symbols: `(` and `)`

### Implementation

The scanner reads the input character by character and groups them into tokens. It skips whitespace and comments. For each token, it returns:

1. Token type (e.g., KEYWORD, IDENTIFIER, OPERATOR)
2. Token value (e.g., "read", "a", ":=")

## 2. Parser

The parser analyzes the sequence of tokens produced by the scanner to determine if the program is syntactically correct according to the language's grammar.

### Grammar

The simplified grammar for our language:

```
program -> statement_list
statement_list -> statement | statement statement_list
statement -> read_stmt | write_stmt | assignment_stmt
read_stmt -> "read" IDENTIFIER
write_stmt -> "write" IDENTIFIER
assignment_stmt -> IDENTIFIER ":=" expression
expression -> term | term "+" term
term -> factor | factor "*" factor
factor -> IDENTIFIER | INTEGER | "(" expression ")"
```

### Implementation

The parser uses a recursive descent approach, with a function for each non-terminal in the grammar. It calls the scanner to get tokens as needed and builds an abstract syntax tree (AST) or generates intermediate code.

## 3. Table-Driven Parser

The table-driven parser is an alternative to the recursive descent parser. It uses a parsing table and a stack to determine the sequence of productions to apply.

### Parsing Table

The parsing table is a 2D array where rows represent non-terminals, columns represent terminals, and each cell contains the production to use.

### Implementation

1. Initialize the stack with the start symbol and EOF.
2. Repeat until the stack is empty:
   a. If the top of the stack matches the current input token, pop the stack and advance to the next token.
   b. If the top of the stack is a non-terminal, look up the production in the parsing table and replace the top of the stack with the right-hand side of the production.
   c. If neither of the above, report a syntax error.

## Integration

The three components work together as follows:

1. The scanner reads the input file and produces a stream of tokens.
2. The parser (either recursive descent or table-driven) consumes these tokens and checks for syntactic correctness.
3. If the program is syntactically correct, the parser generates an intermediate representation (e.g., AST or three-address code).

## Example

For the input program:

```
/* prog1 */
read a
read b
area := a * b
perimeter := 2 * (a + b)
write area
write perimeter
```

The scanner would produce tokens like:

```
(KEYWORD, "read"), (IDENTIFIER, "a"), (KEYWORD, "read"), (IDENTIFIER, "b"),
(IDENTIFIER, "area"), (OPERATOR, ":="), (IDENTIFIER, "a"), (OPERATOR, "*"), (IDENTIFIER, "b"),
...
```

The parser would then analyze these tokens to ensure they follow the grammar rules and potentially generate an intermediate representation of the program.

## Conclusion

This simple compiler demonstrates the basic principles of lexical analysis and parsing. It can be extended to handle more complex language features, perform semantic analysis, and generate executable code.
