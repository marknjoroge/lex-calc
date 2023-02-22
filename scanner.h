
typedef enum {read, write, id, literal, becomes,
                add, sub, mul, quo, lparen, rparen, 
                eof, comment, newline} token;


extern token scan(FILE *inputFile);
