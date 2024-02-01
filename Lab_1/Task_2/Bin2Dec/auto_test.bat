rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem ожидаем нулевой код завершения программы если num = 110010000.
	%PROGRAM% 110010000 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_400.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если binStr == 32 нулевых бита.
	%PROGRAM% 00000000000000000000000000000000 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_0.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если binStr == 32 единичных бита.
	%PROGRAM% 11111111111111111111111111111111 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_4294967295.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если binStr задан корректно.
	%PROGRAM% 10101010101010101010101010101010 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_2863311530.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если binStr слева есть сначала нули.
	%PROGRAM% 00010101010101010101010101010101 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_357913941.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если binStr передаётся строка.
	%PROGRAM% string > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_binstr_arg_err.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если binStr больше 32.
	%PROGRAM% 0001010101010101010101010101010111 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_binstr_arg_err.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если binStr больше 32.
	%PROGRAM% > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1