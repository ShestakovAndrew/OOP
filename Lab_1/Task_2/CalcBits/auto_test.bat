rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem ожидаем нулевой код завершения программы если byte = 0.
	%PROGRAM% 0 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_0.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если byte = 1.
	%PROGRAM% 1 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_1.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если byte = 5.
	%PROGRAM% 5 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_2.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если byte = 100.
	%PROGRAM% 100 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_3.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если byte = 101.
	%PROGRAM% 101 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_4.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если byte = 179.
	%PROGRAM% 179 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_5.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если byte = 187.
	%PROGRAM% 187 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_6.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если byte = 254.
	%PROGRAM% 254 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_7.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если byte = 255.
	%PROGRAM% 255 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_8.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если byte = 256.
	%PROGRAM% 256 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_out_of_range.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если byte нет.
	%PROGRAM% > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если вместо byte передали не число.
	%PROGRAM% string > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_byte_not_digit.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если byte = -1.
	%PROGRAM% -1 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_byte_not_digit.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1