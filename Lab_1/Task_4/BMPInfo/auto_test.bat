rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem ожидаем нулевой код если bmp 1 бит на пиксель
	%PROGRAM% test_files\input_1.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_1.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код если bmp 4 бита на пиксель
	%PROGRAM% test_files\input_4.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_4.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код если bmp 8 бит на пиксель
	%PROGRAM% test_files\input_8.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_8.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код если bmp 24 бита на пиксель
	%PROGRAM% test_files\input_24.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_24.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код если используется RLE компрессия данных.
	%PROGRAM% test_files\input_8_rle.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_8_rle.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код если в bfReserved не содержит нули
	%PROGRAM% test_files\input_file_reserved_error.bmp > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_incorrect_reserved.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код если файл пустой
	%PROGRAM% test_files\input_empty_file.bmp > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_empty_file_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код если нет аргумента
	%PROGRAM% > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1