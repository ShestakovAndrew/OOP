rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem не все аргументы
%PROGRAM% test_files\labyrinth_1.txt > "%TEMP%\output_err.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\not_all_arguments_result.txt
if ERRORLEVEL 1 goto err

rem несуществующий входной файл
%PROGRAM% test_files\non_existent_input_file.txt test_files\labyrinth_1_out.txt > "%TEMP%\output_err.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\non_existent_input_file_result.txt
if ERRORLEVEL 1 goto err

rem файл c лабиринтом пустой 
%PROGRAM% test_files\empty_file.txt test_files\empty_file_out.txt > "%TEMP%\output_err.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\empty_file_result.txt
if ERRORLEVEL 1 goto err

rem лабиринт без начальной точки 
%PROGRAM% test_files\labyrinth_without_starting_point.txt test_files\out.txt > "%TEMP%\output_err.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\labyrinth_error_ending_starting_point.txt
if ERRORLEVEL 1 goto err

rem лабиринт без конечной точки 
%PROGRAM% test_files\labyrinth_without_ending_point.txt test_files\out.txt > "%TEMP%\output_err.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\labyrinth_error_ending_starting_point.txt
if ERRORLEVEL 1 goto err

rem лабиринт с двумя конечными точками
%PROGRAM% test_files\labyrinth_with_two_ending_point.txt test_files\out.txt > "%TEMP%\output_err.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\labyrinth_error_ending_starting_point.txt
if ERRORLEVEL 1 goto err

rem лабиринт с двумя начальными точками
%PROGRAM% test_files\labyrinth_with_two_starting_point.txt test_files\out.txt > "%TEMP%\output_err.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\labyrinth_error_ending_starting_point.txt
if ERRORLEVEL 1 goto err

rem прямоугольный лабиринт
%PROGRAM% test_files\labyrinth_1.txt test_files\labyrinth_1_out.txt > "%TEMP%\output_err.txt"
if ERRORLEVEL 1 goto err
fc.exe test_files\labyrinth_1_out.txt test_files\labyrinth_1_result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\empty_file.txt
if ERRORLEVEL 1 goto err

rem лабиринт произвольной формы
%PROGRAM% test_files\labyrinth_2.txt test_files\labyrinth_2_out.txt > "%TEMP%\output_err.txt"
if ERRORLEVEL 1 goto err
fc.exe test_files\labyrinth_2_out.txt test_files\labyrinth_2_result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\empty_file.txt
if ERRORLEVEL 1 goto err

rem запутанный лабиринт
%PROGRAM% test_files\labyrinth_3.txt test_files\labyrinth_3_out.txt > "%TEMP%\output_err.txt"
if ERRORLEVEL 1 goto err
fc.exe test_files\labyrinth_3_out.txt test_files\labyrinth_3_result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\empty_file.txt
if ERRORLEVEL 1 goto err

rem лабиринт 100x100
%PROGRAM% test_files\labyrinth_4.txt test_files\labyrinth_4_out.txt > "%TEMP%\output_err.txt"
if ERRORLEVEL 1 goto err
fc.exe test_files\labyrinth_4_out.txt test_files\labyrinth_4_result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\empty_file.txt
if ERRORLEVEL 1 goto err

rem ошибка при лабиринте 101x100
%PROGRAM% test_files\labyrinth_5.txt test_files\labyrinth_5_out.txt > "%TEMP%\output_err.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\labyrinth_5_error_result.txt
if ERRORLEVEL 1 goto err

rem пути не существует
%PROGRAM% test_files\labyrinth_6.txt test_files\labyrinth_6_out.txt > "%TEMP%\output_err.txt"
if ERRORLEVEL 1 goto err
fc.exe test_files\labyrinth_6_out.txt test_files\labyrinth_6.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\empty_file.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1