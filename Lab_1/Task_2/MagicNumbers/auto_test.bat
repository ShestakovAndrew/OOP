rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem ожидаем вывод Non_magic если ввели 0.
	%PROGRAM% < test_files\input_0.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_non_magic.txt
	if ERRORLEVEL 1 goto err

rem ожидаем вывод Non_magic если ввели 1.
	%PROGRAM% < test_files\input_1.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_non_magic.txt
	if ERRORLEVEL 1 goto err

rem ожидаем вывод Non_magic если ввели 18446744073709551615.
	%PROGRAM% < test_files\input_18446744073709551615.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_non_magic.txt
	if ERRORLEVEL 1 goto err

rem ожидаем вывод Error если ввели 18446744073709551616.
	%PROGRAM% < test_files\input_18446744073709551616.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем вывод Error если ввели не число.
	%PROGRAM% < test_files\input_string.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем вывод Error если ничего не вводили.
	%PROGRAM% < test_files\input_empty.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевое завершение программы если аргумент указан корректно и N = 20.
	%PROGRAM% --find 20 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_N_20.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевое завершение программы если аргумент указан не корректно.
	%PROGRAM% --find > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1