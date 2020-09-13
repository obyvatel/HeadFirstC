echo компиляция и линковка
gcc -Ic:\opencv\build\include\ -c webcam.c -o webcam.o
gcc webcam.o -Lc:\opencv\build\gpu\x86\bin -Lc:\opencv\build\x86\mingw\lib -lopencv_core231 -lopencv_highgui231 -o webcam

echo запуск
webcam
