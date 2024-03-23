rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem не все аргументы
	%PROGRAM% test_files\input_labyrinth_1.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

rem несуществующий входной файл
	%PROGRAM% test_files\input_no_file.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_no_file.txt
	if ERRORLEVEL 1 goto err

rem лабиринт без начальной точки 
	%PROGRAM% test_files\input_non_starting_point.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_start_end_point_error.txt
	if ERRORLEVEL 1 goto err

rem лабиринт без конечной точки 
	%PROGRAM% test_files\input_non_ending_point.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_start_end_point_error.txt
	if ERRORLEVEL 1 goto err

rem лабиринт с двумя конечными точками
	%PROGRAM% test_files\input_two_ending_point.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_start_end_point_error.txt
	if ERRORLEVEL 1 goto err

rem лабиринт с двумя начальными точками
	%PROGRAM% test_files\input_two_starting_point.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_start_end_point_error.txt
	if ERRORLEVEL 1 goto err

rem прямоугольный лабиринт
	%PROGRAM% test_files\input_labyrinth_1.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_labyrinth_1.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_empty_file.txt
	if ERRORLEVEL 1 goto err

rem лабиринт произвольной формы
	%PROGRAM% test_files\input_labyrinth_2.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_labyrinth_2.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_empty_file.txt
	if ERRORLEVEL 1 goto err

rem запутанный лабиринт
	%PROGRAM% test_files\input_labyrinth_3.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_labyrinth_3.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_empty_file.txt
	if ERRORLEVEL 1 goto err

rem лабиринт 100x100
	%PROGRAM% test_files\input_labyrinth_4.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_labyrinth_4.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_empty_file.txt
	if ERRORLEVEL 1 goto err

rem ошибка при лабиринте 101x100
	%PROGRAM% test_files\input_labyrinth_5.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_error_size.txt
	if ERRORLEVEL 1 goto err

rem пути не существует
	%PROGRAM% test_files\input_labyrinth_6.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\input_labyrinth_6.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_empty_file.txt
	if ERRORLEVEL 1 goto err

rem файл c лабиринтом пустой 
	%PROGRAM% test_files\input_empty_file.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_empty_file_error.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1