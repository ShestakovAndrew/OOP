rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem �� ��� ���������
	%PROGRAM% test_files\input_labyrinth_1.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

rem �������������� ������� ����
	%PROGRAM% test_files\input_no_file.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_no_file.txt
	if ERRORLEVEL 1 goto err

rem �������� ��� ��������� ����� 
	%PROGRAM% test_files\input_non_starting_point.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_start_end_point_error.txt
	if ERRORLEVEL 1 goto err

rem �������� ��� �������� ����� 
	%PROGRAM% test_files\input_non_ending_point.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_start_end_point_error.txt
	if ERRORLEVEL 1 goto err

rem �������� � ����� ��������� �������
	%PROGRAM% test_files\input_two_ending_point.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_start_end_point_error.txt
	if ERRORLEVEL 1 goto err

rem �������� � ����� ���������� �������
	%PROGRAM% test_files\input_two_starting_point.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_start_end_point_error.txt
	if ERRORLEVEL 1 goto err

rem ������������� ��������
	%PROGRAM% test_files\input_labyrinth_1.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_labyrinth_1.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_empty_file.txt
	if ERRORLEVEL 1 goto err

rem �������� ������������ �����
	%PROGRAM% test_files\input_labyrinth_2.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_labyrinth_2.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_empty_file.txt
	if ERRORLEVEL 1 goto err

rem ���������� ��������
	%PROGRAM% test_files\input_labyrinth_3.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_labyrinth_3.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_empty_file.txt
	if ERRORLEVEL 1 goto err

rem �������� 100x100
	%PROGRAM% test_files\input_labyrinth_4.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_labyrinth_4.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_empty_file.txt
	if ERRORLEVEL 1 goto err

rem ������ ��� ��������� 101x100
	%PROGRAM% test_files\input_labyrinth_5.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_error_size.txt
	if ERRORLEVEL 1 goto err

rem ���� �� ����������
	%PROGRAM% test_files\input_labyrinth_6.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\input_labyrinth_6.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_empty_file.txt
	if ERRORLEVEL 1 goto err

rem ���� c ���������� ������ 
	%PROGRAM% test_files\input_empty_file.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_empty_file_error.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1