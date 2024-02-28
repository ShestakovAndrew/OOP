rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem ожидаем нулевой код если пример из задания
	%PROGRAM% test_files\input_1.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_1.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_successfully.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код если файл пустой
	%PROGRAM% test_files\input_file_empty.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_file_empty.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_livestate_length_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код если выходной файл не передан
	%PROGRAM% test_files\input_1.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_1.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код если выходного файла не существует
	%PROGRAM% test_files\input_1.txt test_files\result_non_exist.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_result_file_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код если файл содержит 256 символов в строке
	%PROGRAM% test_files\input_2_256.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_2_256.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_successfully.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код если файл содержит 257 символов в строке 
	%PROGRAM% test_files\input_3_257.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_file_empty.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_read_size_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код если файл содержит 256 символов в колонке
	%PROGRAM% test_files\input_4_256.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_4_256.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_successfully.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код если файл содержит 257 символов в колонке
	%PROGRAM% test_files\input_5_257.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_file_empty.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_read_size_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код если файл содержит не замкнутый контур
	%PROGRAM% test_files\input_no_wall.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_file_empty.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_wall_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код если файл содержит неизвествный символ
	%PROGRAM% test_files\input_symbol_error.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_file_empty.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_symbol_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код если существует следующая итерация
	%PROGRAM% test_files\input_6.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_6.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_symbol_error.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1