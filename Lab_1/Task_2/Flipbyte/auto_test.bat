rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem ожидаем нулевой код завершения программы если inputByte = 6.
	%PROGRAM% 6 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_96.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если inputByte = 0.
	%PROGRAM% 0 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_0.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если inputByte = 255.
	%PROGRAM% 255 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_255.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если inputByte = 15.
	%PROGRAM% 15 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_240.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если inputByte = 240.
	%PROGRAM% 240 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_15.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если inputByte = 12.
	%PROGRAM% 12 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_48.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если в inputByte передаётся строка.
	%PROGRAM% string > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_no_digits.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если inputByte не задан.
	%PROGRAM% > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если inputByte больше 255.
	%PROGRAM% 256 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_out_range.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1