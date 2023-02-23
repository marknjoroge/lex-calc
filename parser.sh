# clear
# gcc scanner.c parser.c -o parser
gcc -c scanner.c 
gcc -c table_driven_parser.c 
gcc -o parser scanner.o table_driven_parser.o
./parser prog1
