rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамл€ющих кавычек (если они были)

rem ѕеременна€ PROGRAM будет хранить первый аргумент командной строки заключЄнный в кавычки
set PROGRAM="%~1"

rem провер€ем копирование пустого файла (копируем его во временную папку текущего пользовател€)
%PROGRAM% test_files\empty.txt %TEMP%\empty.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\empty.txt test_files\empty.txt
if ERRORLEVEL 1 goto err

rem провер€ем копирование файла из одной строки
%PROGRAM% test_files\one-line.txt %TEMP%\one-line.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\one-line.txt test_files\one-line.txt
if ERRORLEVEL 1 goto err

rem провер€ем копирование файла из нескольких строк
%PROGRAM% test_files\multiline.txt %TEMP%\multiline.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\multiline.txt test_files\multiline.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при копировании несуществующего файла
%PROGRAM% non-existing-file-name.txt %TEMP%\non-existing-file-name.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test_files\expected-output-when-input-file-is-missing.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при невозможности записи в выходной файл (в исполн€емый файл программы)
%PROGRAM% test_files\multiline.txt %PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1