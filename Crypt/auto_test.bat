rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem не все аргументы
%PROGRAM% crypt test_files\input_file_one_byte.txt test_files\output_file_one_byte.txt > "%TEMP%\output_err.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\not_all_arguments_result.txt
if ERRORLEVEL 1 goto err

rem несуществующий входной файл
%PROGRAM% crypt test_files\non_existent_input_file.txt test_files\output_file_one_byte.txt 170 > "%TEMP%\output_err.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\non_existent_input_file_result.txt
if ERRORLEVEL 1 goto err

rem неправильный ключ
%PROGRAM% crypt test_files\input_file_one_byte.txt test_files\output_file_one_byte.txt 256 > "%TEMP%\output_err.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\wrong_key_result.txt
if ERRORLEVEL 1 goto err

rem шифрование одного байта корректное
%PROGRAM% crypt test_files\input_file_one_byte.txt test_files\output_file_one_byte.txt 150 > "%TEMP%\output_err.txt"
if ERRORLEVEL 1 goto err
fc.exe test_files\output_file_one_byte.txt test_files\crypt_one_byte_result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\empty_file.txt
if ERRORLEVEL 1 goto err

rem расшифрование байта обратно верно (с верным ключом)
%PROGRAM% decrypt test_files\crypt_one_byte_result.txt test_files\output_file_one_byte.txt 150 > "%TEMP%\output_err.txt"
if ERRORLEVEL 1 goto err
fc.exe test_files\output_file_one_byte.txt test_files\input_file_one_byte.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\empty_file.txt
if ERRORLEVEL 1 goto err

rem расшифрование байта обратно неверное (с неверным ключом)
%PROGRAM% decrypt test_files\crypt_one_byte_result.txt test_files\output_file_one_byte.txt 151 > "%TEMP%\output_err.txt"
if ERRORLEVEL 1 goto err
fc.exe test_files\output_file_one_byte.txt test_files\input_file_one_byte.txt
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\empty_file.txt
if ERRORLEVEL 1 goto err

rem файл для шифрования пустой 
%PROGRAM% crypt test_files\empty_file.txt test_files\output_file_one_byte.txt 100 > "%TEMP%\output_err.txt"
if ERRORLEVEL 1 goto err
fc.exe test_files\output_file_one_byte.txt test_files\empty_file.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\empty_file.txt
if ERRORLEVEL 1 goto err

rem текст шифруется и дешифруется с верным ключом.
%PROGRAM% crypt test_files\input_file_text.txt test_files\output_file_text.txt 255 > "%TEMP%\output_err.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\empty_file.txt
if ERRORLEVEL 1 goto err

%PROGRAM% decrypt test_files\output_file_text.txt test_files\output_file_text_result.txt 255 > "%TEMP%\output_err.txt"
if ERRORLEVEL 1 goto err
fc.exe test_files\output_file_text_result.txt test_files\input_file_text.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\empty_file.txt
if ERRORLEVEL 1 goto err

rem текст шифруется, но не дешифруется с другим ключом.
%PROGRAM% crypt test_files\input_file_text.txt test_files\output_file_text.txt 255 > "%TEMP%\output_err.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\empty_file.txt
if ERRORLEVEL 1 goto err

%PROGRAM% decrypt test_files\output_file_text.txt test_files\output_file_text_result.txt 253 > "%TEMP%\output_err.txt"
if ERRORLEVEL 1 goto err
fc.exe test_files\output_file_text_result.txt test_files\input_file_text.txt
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output_err.txt" test_files\empty_file.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1