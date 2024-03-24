rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem �� ��� ���������
	%PROGRAM% test_files\input_fill_1.txt > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

rem �������������� ������� ����
	%PROGRAM% test_files\input_no_file.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_no_file.txt
	if ERRORLEVEL 1 goto err

rem � ����� ��������� ������
	%PROGRAM% test_files\input_fill_1.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_fill_1.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_no_error.txt
	if ERRORLEVEL 1 goto err

rem � ����� ���������� �������
	%PROGRAM% test_files\input_fill_2.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_fill_2.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_no_error.txt
	if ERRORLEVEL 1 goto err

rem � ����� ���������� �������
	%PROGRAM% test_files\input_fill_3.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_fill_3.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_no_error.txt
	if ERRORLEVEL 1 goto err

rem 100x100
	%PROGRAM% test_files\input_fill_4.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_fill_4.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_no_error.txt
	if ERRORLEVEL 1 goto err

rem 101x100 ���������� � ���������
	%PROGRAM% test_files\input_fill_5.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_fill_5.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_file_was_cut.txt
	if ERRORLEVEL 1 goto err

rem ���� ������ � ����� ��������� ������
	%PROGRAM% test_files\input_fill_7.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_fill_7.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_no_error.txt
	if ERRORLEVEL 1 goto err

rem ��� ��������� �����
	%PROGRAM% test_files\input_fill_0.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_empty_file.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_no_start_point.txt
	if ERRORLEVEL 1 goto err

rem ���� ������
	%PROGRAM% test_files\input_empty_file.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_empty_file.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_file_empty.txt
	if ERRORLEVEL 1 goto err

rem �������� 101x100 ��������� ��������� ����� � ���������� ����������
	%PROGRAM% test_files\input_fill_6.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_empty_file.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_cut_and_no_start_point.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1