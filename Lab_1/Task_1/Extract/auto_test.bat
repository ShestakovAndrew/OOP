rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem ожидаем нулевой код завершения программы если позиция 0 и диапазон 10 из 20 возможных.
	%PROGRAM% test_files\input.txt "%TEMP%\result.txt" 0 10 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_half.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\extract_successfully.txt
	if ERRORLEVEL 1 goto err

rem 2) ожидаем нулевой код завершения программы если позиция 0 и диапазон 20 из 20 возможных байт.
	%PROGRAM% test_files\input.txt "%TEMP%\result.txt" 0 20 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_full.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\extract_successfully.txt
	if ERRORLEVEL 1 goto err

rem 3) ожидаем ненулевой код завершения программы если диапазон = 0 из 20 возможных байт.
	%PROGRAM% test_files\input.txt "%TEMP%\result.txt" 0 0 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\extract_incorrect_range.txt
	if ERRORLEVEL 1 goto err

rem 4) ожидаем ненулевой код завершения программы если начальная позиция -1.
	%PROGRAM% test_files\input.txt "%TEMP%\result.txt" -1 10 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\extract_incorrect_position.txt
	if ERRORLEVEL 1 goto err

rem 5) ожидаем ненулевой код завершения программы если начальная позиция 30 больше чем файл 20 байт.
	%PROGRAM% test_files\input.txt "%TEMP%\result.txt" 30 10 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\extract_incorrect_position.txt
	if ERRORLEVEL 1 goto err

rem 6) ожидаем ненулевой код завершения программы если диапазон 30 из 20 возможных байт.
	%PROGRAM% test_files\input.txt "%TEMP%\result.txt" 0 30 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\extract_incorrect_range.txt
	if ERRORLEVEL 1 goto err

rem 7) ожидаем ненулевой код завершения программы если некоректное кол-во аргументов.
	%PROGRAM% test_files\input.txt 0 30 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\extract_incorrect_argv.txt
	if ERRORLEVEL 1 goto err

rem 8) ожидаем ненулевой код завершения программы если входного файла не существует.
	%PROGRAM% test_files\input_no_exist.txt "%TEMP%\result.txt" 0 30 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\no_file.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1