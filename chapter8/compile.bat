echo create object files
gcc -c encrypt.c -o encrypt.o
gcc -c checksum.c -o checksum.o

echo link object files and execute
gcc test_code.c encrypt.o checksum.o -o test_code && test_code