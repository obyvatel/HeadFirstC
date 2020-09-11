echo создать hfcal_UK.o
echo hfcal.h ищет в c:\includes
gcc -Ic:\includes -c hfcal_UK.c -o hfcal.o

echo конвертирование объектного файла в dll (dynamic link library)
gcc -shared hfcal.o -o c:\libs\hfcal.dll

echo создание treadmill.exe
gcc -Ic:\includes\ -c elliptical.c -o elliptical.o
gcc elliptical.o -Lc:\libs -lhfcal  -o elliptical

echo копирование hfcal.dll в текущую папку
copy c:\libs\hfcal.dll .\hfcal.dll

echo запуск
elliptical