rem ѕеременна€ PROGRAM будет хранить первый аргумент командной строки заключЄнный в кавычки
set PROGRAM="%~1"

rem ожидаем нулевой код завершени€ программы если byte = 17, number of bits = 2, <L / R> = L.
	%PROGRAM% 17 2 L > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_68.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершени€ программы если byte = 255, number of bits = 5, <L / R> = R.
	%PROGRAM% 255 5 R > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_255.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершени€ программы если byte = 100, number of bits = 2, <L / R> = R.
	%PROGRAM% 100 2 R > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_25.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершени€ программы если byte = 256.
	%PROGRAM% 256 1 L > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_byte_arg_err.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершени€ программы если byte = -1.
	%PROGRAM% -1 1 L > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_byte_arg_err.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершени€ программы если number of bit = 8.
	%PROGRAM% 17 9 L> "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_num_bit_arg_err.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершени€ программы если number of bit = -1.
	%PROGRAM% 17 -1 L> "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_num_bit_arg_err.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершени€ программы если <L / R> = l.
	%PROGRAM% 17 5 l> "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_side_arg_err.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершени€ программы если <L / R> = T.
	%PROGRAM% 17 5 T> "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_side_arg_err.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершени€ программы если переданы не все аргументы.
	%PROGRAM% 155 4 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1