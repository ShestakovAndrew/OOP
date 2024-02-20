rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem ожидаем нулевой код если файл нулевой длины
	%PROGRAM% pack test_files\input_file_empty.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\input_file_empty.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_pack_successfully.txt
	if ERRORLEVEL 1 goto err

	%PROGRAM% unpack test_files\input_file_empty.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\input_file_empty.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_unpack_successfully.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код если файл содержит 255 байт одинаковых символов подряд 
	%PROGRAM% pack test_files\input_255_insuccession.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_255_insuccession.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_pack_successfully.txt
	if ERRORLEVEL 1 goto err

	%PROGRAM% unpack test_files\result_255_insuccession.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\input_255_insuccession.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_unpack_successfully.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код если файл содержит 256 байт одинаковых символов подряд 
	%PROGRAM% pack test_files\input_256_insuccession.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_256_insuccession.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_pack_successfully.txt
	if ERRORLEVEL 1 goto err

	%PROGRAM% unpack test_files\result_256_insuccession.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\input_256_insuccession.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_unpack_successfully.txt
	if ERRORLEVEL 1 goto err

rem ожидаем нулевой код если файл содержит 257 байт одинаковых символов подряд 
	%PROGRAM% pack test_files\input_257_insuccession.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_257_insuccession.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_pack_successfully.txt
	if ERRORLEVEL 1 goto err

	%PROGRAM% unpack test_files\result_257_insuccession.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\input_257_insuccession.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_unpack_successfully.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код если длина запакованного файла нечётная
	%PROGRAM% unpack test_files\input_odd_pack.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_odd_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код если нет аргумента
	%PROGRAM% test_files\input_255_insuccession.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код если аргумент не корректный
	%PROGRAM% unpock test_files\input_255_insuccession.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_rle_mode_error.txt
	if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код если в запакованном файле кол-во повторений символа, равное нулю
	%PROGRAM% unpack test_files\input_alpha_zero_pack.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_zero_pack_error.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1