echo поместить hfcal.h в стандартную папку с заголовочными файлами
copy hfcal.h c:\MinGW\include\hfcal.h

echo создание объектного файла hfcal.o
gcc -c hfcal.c -o hfcal.o

echo переписать hfcal.o в папку стандартных библиотек
move hfcal.o c:\MinGW\lib\hfcal.o

echo создание объектного файла elliptical.o
gcc -c elliptical.c hfcal.o -o elliptical.o

echo создать архивный файл
ar -rcs libhfcal.a hfcal.o
echo переписать в папку стандартных библиотек
move libhfcal.a c:\MinGW\lib\libhfcal.a

echo компиляция
gcc elliptical.c -lhfcal -o elliptical

echo запуск
elliptical