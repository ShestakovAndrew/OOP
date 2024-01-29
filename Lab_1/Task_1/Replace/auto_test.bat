rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
chcp 1251
set PROGRAM="%~1"

rem ожидаем нулевой код завершения программы если есть 1 совпадение в 1 строке.
%PROGRAM% test_files\single_replace_line.txt "%TEMP%\single_replace_line_result.txt" "кошка" "собака" > "%TEMP%\single_replace_line_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\single_replace_line_result.txt" test_files\single_replace_line_result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\single_replace_line_output.txt" test_files\replace_successfully.txt
if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если есть 2 совпадения в 1 строке.
%PROGRAM% test_files\many_replace_line.txt "%TEMP%\many_replace_line_result.txt" "кошка" "собака" > "%TEMP%\many_replace_line_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\many_replace_line_result.txt" test_files\many_replace_line_result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\many_replace_line_output.txt" test_files\replace_successfully.txt
if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если есть 1 совпадения в 4 строках.
%PROGRAM% test_files\single_replace_multiline.txt "%TEMP%\single_replace_multiline_result.txt" "кошка" "собака" > "%TEMP%\single_replace_multiline_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\single_replace_multiline_result.txt" test_files\single_replace_multiline_result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\single_replace_multiline_output.txt" test_files\replace_successfully.txt
if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если есть 2+ совпадения в 4 строках.
%PROGRAM% test_files\many_replace_multiline.txt "%TEMP%\many_replace_multiline_result.txt" "кошка" "собака" > "%TEMP%\many_replace_multiline_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\many_replace_multiline_result.txt" test_files\many_replace_multiline_result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\many_replace_multiline_output.txt" test_files\replace_successfully.txt
if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы если есть совпадение среди цифр.
%PROGRAM% test_files\replace_digit.txt "%TEMP%\replace_digit_result.txt" "1231234" "кошка" > "%TEMP%\replace_digit_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\replace_digit_result.txt" test_files\replace_digit_result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\replace_digit_output.txt" test_files\replace_successfully.txt
if ERRORLEVEL 1 goto err

rem ожидаем нулевой код завершения программы в случае если может быть зацикливание.
%PROGRAM% test_files\replace_mom.txt "%TEMP%\replace_mom_result.txt" "ма" "мама" > "%TEMP%\replace_mom_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\replace_mom_result.txt" test_files\replace_mom_result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\replace_mom_output.txt" test_files\replace_successfully.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код, если в файле нет текста.
%PROGRAM% test_files\file_empty.txt "%TEMP%\file_empty_result.txt" "кошка" "собака" > "%TEMP%\file_empty_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\file_empty_output.txt" test_files\file_empty_result.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код, если не верные аргументы
%PROGRAM% test_files\single_replace_line.txt "test_files\single_replace_line.txt" > "%TEMP%\file_missing_argv_result.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\file_missing_argv_result.txt" test_files\file_missing_argv_result.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код, если файла не существует.
%PROGRAM% non_existing_file_name.txt arg2 arg3 arg4 > "%TEMP%\non_existing_file_name_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\non_existing_file_name_output.txt" test_files\file_missing_result.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1