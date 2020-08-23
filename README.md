# HeadFirstC
Exercises from book

Перевод кодовой страницы. Шрифт командной строки установить Lucida Console.
chcp 1251
где 
1251	- кодировка Windows
866 	- кодировка DOS
65001 	- кодировка UTF-8

Вывести статус завершения программы. Например, "return 2".
echo %errorlevel%

Пример запуска програмы:
geo2json.exe < gpsdata.csv > output.json 2> error.log
<  - Поток данных stdin. Ввод данных из файла gpsdata.csv.
>  - Поток данных stdout. Вывод данных в файл output.json.
2> - Поток ошибок stderr. Вывод ошибок в файл error.log.

Пример одновременного запуска двух программ:
(bermuda|geo2json) < spooky.csv > output4.json

(bermuda|geo2json) - одновременно запускаются bermuda.exe и geo2json.exe.
| - обозначение канала передачи. Выходной поток bermuda.exe направляется во входной поток geo2json.exe.
1) На вход bermuda.exe поступают данные из spooky.csv.
2) На вход geo2json.exe поступают данные из выхода bermuda.exe
3) В output4.json поступают данные из выхода geo2json.exe.
