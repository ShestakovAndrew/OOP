rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem ожидаем нулевой код завершения программы если матрицы корректны.
	%PROGRAM% test_files\matrix_1.txt test_files\matrix_2.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_matrix_1_2.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если матрица зануляется.
	%PROGRAM% test_files\matrix_1.txt test_files\matrix_zero.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\matrix_zero.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если матрица умножается на единичную матрицу.
	%PROGRAM% test_files\matrix_1.txt test_files\matrix_ones.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_matrix_1_ones.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если матрица перемножается на саму себя.
	%PROGRAM% test_files\matrix_1.txt test_files\matrix_1.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_matrix_1_1.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если матрица на выводе имеет 3 точность.
	%PROGRAM% test_files\matrix_1.txt test_files\matrix_3.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_matrix_1_3.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если указаны не все аргументы.
	%PROGRAM% test_files\matrix_1.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если матрица 2x3.
	%PROGRAM% test_files\matrix_1.txt test_files\matrix_2x3.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_size_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если матрица пустая.
	%PROGRAM% test_files\matrix_1.txt test_files\matrix_empty.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_matrix_empty_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если файла с матрицей не существует.
	%PROGRAM% test_files\matrix_non_exist_file.txt test_files\matrix_1.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_file_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код завершения программы если матрица задана не корректно.
	%PROGRAM% test_files\matrix_coef_error.txt test_files\matrix_1.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_coef_error.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1