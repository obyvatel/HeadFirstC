gcc -Ic:\includes\ -c elliptical.c -o elliptical.o
gcc elliptical.o -Lc:\libs -lhfcal  -o elliptical

echo запуск. PATH не сработал, пришлось hfcal.dll 
echo переписать в папку с исполнямым файлом
PATH="%PATH%;c:\libs\"
elliptical