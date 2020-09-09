echo заголовки encrypt.h и checksum.h в c:\my_header_files
echo объектные файлы encrypt.o и checksum.o в c:\my_object_files\
echo прописать заголовки так: #include "c:\my_header_files\encrypt.h"

echo link object files and execute
gcc -Ic:\my_header_files test_code.c c:\my_object_files\encrypt.o c:\my_object_files\checksum.o -o test_code && test_code