rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла 
rem с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem сравнение пустых файлов одной кодировки
%PROGRAM% test_files\empty_first.txt test_files\empty_second.txt
if ERRORLEVEL 1 goto err

rem сравнение файлов из одной строки
%PROGRAM% test_files\line_first.txt test_files\line_second.txt
if ERRORLEVEL 1 goto err

rem сравнение файлов из нескольких строк
%PROGRAM% test_files\multiline_first.txt test_files\multiline_second.txt
if ERRORLEVEL 1 goto err

rem сравнение файлов из одной строки c ошибкой
%PROGRAM% test_files\line_first.txt test_files\line_second_error.txt
if NOT ERRORLEVEL 1 goto err

rem сравнение файлов из нескольких строк c ошибкой (3 строка)
%PROGRAM% test_files\multiline_first.txt test_files\multiline_second_error.txt
if NOT ERRORLEVEL 1 goto err

rem сравнение файлов из одной строки разных кодировок
%PROGRAM% test_files\line_first.txt test_files\line_second_utf16le.txt
if NOT ERRORLEVEL 1 goto err

rem сравнение пустых файлов разных кодировок
%PROGRAM% test_files\empty_first.txt test_files\empty_second_utf16le.txt
if NOT ERRORLEVEL 1 goto err

rem сравнение файлов из нескольких строк разных кодировок
%PROGRAM% test_files\multiline_first.txt test_files\multiline_second_utf16le.txt
if NOT ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1