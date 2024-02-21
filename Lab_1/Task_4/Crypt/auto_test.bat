rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem проверка ключа

	rem ожидаем нулевой код, если шифрование и дешифрование c ключём = 0.
		%PROGRAM% encrypt test_files\input_file_text.txt "%TEMP%\result.txt" 0 > "%TEMP%\output.txt"
		if ERRORLEVEL 1 goto err
		fc.exe "%TEMP%\result.txt" test_files\result_file_text_0.txt
		if ERRORLEVEL 1 goto err
		fc.exe "%TEMP%\output.txt" test_files\output_encrypt_successfully.txt
		if ERRORLEVEL 1 goto err

		%PROGRAM% decrypt "%TEMP%\result.txt" "%TEMP%\result_reverse.txt" 0 > "%TEMP%\output.txt"
		if ERRORLEVEL 1 goto err
		fc.exe "%TEMP%\result_reverse.txt" test_files\input_file_text.txt
		if ERRORLEVEL 1 goto err
		fc.exe "%TEMP%\output.txt" test_files\output_decrypt_successfully.txt
		if ERRORLEVEL 1 goto err

	rem ожидаем нулевой код, если шифрование и дешифрование c ключём = 255.
		%PROGRAM% encrypt test_files\input_file_text.txt "%TEMP%\result.txt" 255 > "%TEMP%\output.txt"
		if ERRORLEVEL 1 goto err
		fc.exe "%TEMP%\result.txt" test_files\result_file_text_255.txt
		if ERRORLEVEL 1 goto err
		fc.exe "%TEMP%\output.txt" test_files\output_encrypt_successfully.txt
		if ERRORLEVEL 1 goto err

		%PROGRAM% decrypt "%TEMP%\result.txt" "%TEMP%\result_reverse.txt" 255 > "%TEMP%\output.txt"
		if ERRORLEVEL 1 goto err
		fc.exe "%TEMP%\result_reverse.txt" test_files\input_file_text.txt
		if ERRORLEVEL 1 goto err
		fc.exe "%TEMP%\output.txt" test_files\output_decrypt_successfully.txt
		if ERRORLEVEL 1 goto err

	rem ожидаем ненулевой код, если ключ = 256
		%PROGRAM% encrypt test_files\input_one_byte.txt "%TEMP%\result.txt" 256 > "%TEMP%\output.txt"
		if NOT ERRORLEVEL 1 goto err
		fc.exe "%TEMP%\output.txt" test_files\output_key_range.txt
		if ERRORLEVEL 1 goto err

	rem ожидаем ненулевой код, если ключ = -1
		%PROGRAM% encrypt test_files\input_file_one_byte.txt "%TEMP%\result.txt" -1 > "%TEMP%\output.txt"
		if NOT ERRORLEVEL 1 goto err
		fc.exe "%TEMP%\output.txt" test_files\output_key_range.txt
		if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код, если нет ключа
	%PROGRAM% encrypt test_files\input_one_byte.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код, если ключ не число
	%PROGRAM% encrypt test_files\input_one_byte.txt "%TEMP%\result.txt" str > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_key_string.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код, если файла несуществует
	%PROGRAM% encrypt test_files\input_non_existent.txt "%TEMP%\result.txt" 170 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_no_file_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код, если файл для шифрования/дешифрования пустой
	%PROGRAM% encrypt test_files\input_empty_file.txt "%TEMP%\result.txt" 150 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_empty_file.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_encrypt_successfully.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код, если файл для дешифрования пустой
	%PROGRAM% decrypt test_files\input_empty_file.txt "%TEMP%\result.txt" 150 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_empty_file.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_decrypt_successfully.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код, если шифрование и дешифрование 1 байта c ключём 150 корректно
	%PROGRAM% encrypt test_files\input_one_byte.txt "%TEMP%\result.txt" 150 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_one_byte_150.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_encrypt_successfully.txt
	if ERRORLEVEL 1 goto err

	%PROGRAM% decrypt "%TEMP%\result.txt" "%TEMP%\result_reverse.txt" 150 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result_reverse.txt" test_files\input_one_byte.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_decrypt_successfully.txt
	if ERRORLEVEL 1 goto err

	rem ожидаем ненулевой код, если дешифрование 1 байта c ключём != 150
	%PROGRAM% decrypt "%TEMP%\result.txt" "%TEMP%\result_reverse.txt" 149 > "%TEMP%\output_err.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result_reverse.txt" test_files\input_one_byte.txt
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output_err.txt" test_files\output_decrypt_successfully.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1