rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem ожидаем нулевой код если HEADER коректный
	%PROGRAM% test_files\input_correct_file.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_correct_file.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код если HEADER mono коректный 
	%PROGRAM% test_files\input_file_mono.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_file_mono.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код если используется RLE компрессия данных.
	%PROGRAM% test_files\input_file_RLE_compression.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_file_RLE_compression.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код если в HEADER little-endian
	%PROGRAM% test_files\input_file_LE.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_LE.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код если в HEADER bfReserved1 не содержит нули
	%PROGRAM% test_files\input_file_reserved_error.bmp > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_incorrect_file.txt
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