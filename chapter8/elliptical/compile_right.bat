echo создать hfcal.o
echo hfcal.h ищет в c:\includes
gcc -Ic:\includes -c hfcal.c -o hfcal.o

echo создать elliptical.o
gcc -Ic:\includes -c elliptical.c -o elliptical.o

echo создать архивный файл
ar -rcs libhfcal.a hfcal.o
echo переместить архив в c:\libs
move libhfcal.a c:\libs\libhfcal.a

echo получить исполняемый файл
gcc elliptical.o -Lc:\libs -lhfcal -o elliptical

echo запуск
elliptical