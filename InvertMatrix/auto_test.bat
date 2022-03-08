rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem матрица не квадратная 
%PROGRAM% test_files\matrix_not_square.txt > "%TEMP%\matrix_not_square.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\matrix_not_square.txt" test_files\matrix_not_square_result.txt
if ERRORLEVEL 1 goto err

rem файл пустой
%PROGRAM% test_files\empty_file.txt  > "%TEMP%\empty_file.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\empty_file.txt" test_files\empty_file_result.txt
if ERRORLEVEL 1 goto err

rem матрица вырожденная 
%PROGRAM% test_files\degenerate_matrix.txt > "%TEMP%\degenerate_matrix.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\degenerate_matrix.txt" test_files\degenerate_matrix_result.txt
if ERRORLEVEL 1 goto err

rem файл из одного числа
%PROGRAM% test_files\single_number.txt > "%TEMP%\single_number.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\single_number.txt" test_files\single_number_result.txt
if ERRORLEVEL 1 goto err

rem матрица 2x2
%PROGRAM% test_files\matrix_2x2.txt > "%TEMP%\matrix_2x2.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\matrix_2x2.txt" test_files\matrix_2x2_result.txt
if ERRORLEVEL 1 goto err

rem матрица 3x3
%PROGRAM% test_files\matrix_3x3.txt > "%TEMP%\matrix_3x3.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\matrix_3x3.txt" test_files\matrix_3x3_result.txt
if ERRORLEVEL 1 goto err

rem матрица 4x4
%PROGRAM% test_files\matrix_4x4.txt > "%TEMP%\matrix_4x4.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\matrix_4x4.txt" test_files\matrix_4x4_result.txt
if ERRORLEVEL 1 goto err

rem нет файла
%PROGRAM% test_files\file_non_exist.txt > "%TEMP%\file_non_exist.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\file_non_exist.txt" test_files\file_non_exist_result.txt
if ERRORLEVEL 1 goto err

rem нет аргумента
%PROGRAM% > "%TEMP%\non_argument.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\non_argument.txt" test_files\non_argument_result.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1