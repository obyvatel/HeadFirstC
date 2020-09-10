gcc -Ic:\includes\ -c elliptical.c -o elliptical.o
gcc elliptical.o -Lc:\libs -lhfcal  -o elliptical

echo запуск
PATH="%PATH%;c:\libs\"
elliptical