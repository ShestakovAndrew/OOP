rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ������� ������� ��� ���� ������� 2x2
	%PROGRAM% test_files\input_matrix_2x2.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_matrix_2x2.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� ������� 3x3
	%PROGRAM% test_files\input_matrix_3x3.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_matrix_3x3.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� ������� 4x4
	%PROGRAM% test_files\input_matrix_4x4.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_matrix_4x4.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� ������� 50x50
	%PROGRAM% test_files\input_matrix_50x50.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_matrix_50x50.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ������� �� ����������.
	%PROGRAM% test_files\input_matrix_not_square.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_matrix_square_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ���� ������
	%PROGRAM% test_files\input_empty_file.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_empty_file_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ������� ����������� � �� ����� �������� �������
	%PROGRAM% test_files\input_no_invert_matrix.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_no_invert_matrix_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ������� �� ������ �����
	%PROGRAM% test_files\input_single_number.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_size_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ����� � �������� �� ����������
	%PROGRAM% test_files\file_non_exist.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_no_file_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ��� ���������
	%PROGRAM% > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1