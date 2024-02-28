rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ������� ������� ��� ���� ������ �� �������
	%PROGRAM% test_files\input_1.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_1.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_successfully.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ���� ������
	%PROGRAM% test_files\input_file_empty.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_file_empty.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_livestate_length_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� �������� ���� �� �������
	%PROGRAM% test_files\input_1.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_1.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ��������� ����� �� ����������
	%PROGRAM% test_files\input_1.txt test_files\result_non_exist.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_result_file_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� ���� �������� 256 �������� � ������
	%PROGRAM% test_files\input_2_256.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_2_256.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_successfully.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ���� �������� 257 �������� � ������ 
	%PROGRAM% test_files\input_3_257.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_file_empty.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_read_size_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� ���� �������� 256 �������� � �������
	%PROGRAM% test_files\input_4_256.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_4_256.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_successfully.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ���� �������� 257 �������� � �������
	%PROGRAM% test_files\input_5_257.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_file_empty.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_read_size_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ���� �������� �� ��������� ������
	%PROGRAM% test_files\input_no_wall.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_file_empty.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_wall_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ���� �������� ������������ ������
	%PROGRAM% test_files\input_symbol_error.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_file_empty.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_symbol_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� ���������� ��������� ��������
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