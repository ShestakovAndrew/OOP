rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem ожидаем нулевой код завершения программы если decStr = 110010000.
	%PROGRAM% 253 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_11111101.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если binStr == 32 нулевых бита.
	%PROGRAM% 0 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_0.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если binStr == 32 единичных бита.
	%PROGRAM% 4294967295 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_11111111111111111111111111111111.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если binStr задан корректно.
	%PROGRAM% 2863311530 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_10101010101010101010101010101010.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если binStr слева есть сначала нули.
	%PROGRAM% 357913941 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_10101010101010101010101010101.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если binStr передаётся строка.
	%PROGRAM% string > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_decstr_no_digits.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если binStr не задан.
	%PROGRAM% > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если binStr больше 2^32.
	%PROGRAM% 4294967296 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_decstr_out_range.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1