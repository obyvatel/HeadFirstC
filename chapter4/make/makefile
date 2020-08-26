message_hider.o: encrypt.h encrypt.c message_hider.c
	gcc -c message_hider.c
encrypt.o: encrypt.h encrypt.c
	gcc -c encrypt.c
message_hider: message_hider.o encrypt.o
	gcc message_hider.o encrypt.o -o message_hider
