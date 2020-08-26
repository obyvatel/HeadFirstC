echo create object files
gcc -c message_hider.c encrypt.c

echo link object files
gcc message_hider.o encrypt.o -o message_hider