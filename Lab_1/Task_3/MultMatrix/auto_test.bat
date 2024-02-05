rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ������� ������� ��� ���������� ��������� ���� ������� ���������.
	%PROGRAM% test_files\matrix_1.txt test_files\matrix_2.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_matrix_1_2.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���������� ��������� ���� ������� ����������.
	%PROGRAM% test_files\matrix_1.txt test_files\matrix_zero.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\matrix_zero.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���������� ��������� ���� ������� ���������� �� ��������� �������.
	%PROGRAM% test_files\matrix_1.txt test_files\matrix_ones.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_matrix_1_ones.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���������� ��������� ���� ������� ������������� �� ���� ����.
	%PROGRAM% test_files\matrix_1.txt test_files\matrix_1.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_matrix_1_1.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���������� ��������� ���� ������� �� ������ ����� 3 ��������.
	%PROGRAM% test_files\matrix_1.txt test_files\matrix_3.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_matrix_1_3.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���������� ��������� ���� ������� �� ��� ���������.
	%PROGRAM% test_files\matrix_1.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���������� ��������� ���� ������� 2x3.
	%PROGRAM% test_files\matrix_1.txt test_files\matrix_2x3.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_size_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���������� ��������� ���� ������� ������.
	%PROGRAM% test_files\matrix_1.txt test_files\matrix_empty.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_matrix_empty_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���������� ��������� ���� ����� � �������� �� ����������.
	%PROGRAM% test_files\matrix_non_exist_file.txt test_files\matrix_1.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_file_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���������� ��������� ���� ������� ������ �� ���������.
	%PROGRAM% test_files\matrix_coef_error.txt test_files\matrix_1.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_coef_error.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1