rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ������� ������� ��� ���������� ��������� ���� ������� 0 � �������� 10 �� 20 ���������.
	%PROGRAM% test_files\input.txt "%TEMP%\result.txt" 0 10 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_half.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\extract_successfully.txt
	if ERRORLEVEL 1 goto err

rem 2) ������� ������� ��� ���������� ��������� ���� ������� 0 � �������� 20 �� 20 ��������� ����.
	%PROGRAM% test_files\input.txt "%TEMP%\result.txt" 0 20 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_full.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\extract_successfully.txt
	if ERRORLEVEL 1 goto err

rem 3) ������� ��������� ��� ���������� ��������� ���� �������� = 0 �� 20 ��������� ����.
	%PROGRAM% test_files\input.txt "%TEMP%\result.txt" 0 0 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\extract_incorrect_range.txt
	if ERRORLEVEL 1 goto err

rem 4) ������� ��������� ��� ���������� ��������� ���� ��������� ������� -1.
	%PROGRAM% test_files\input.txt "%TEMP%\result.txt" -1 10 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\extract_incorrect_position.txt
	if ERRORLEVEL 1 goto err

rem 5) ������� ��������� ��� ���������� ��������� ���� ��������� ������� 30 ������ ��� ���� 20 ����.
	%PROGRAM% test_files\input.txt "%TEMP%\result.txt" 30 10 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\extract_incorrect_position.txt
	if ERRORLEVEL 1 goto err

rem 6) ������� ��������� ��� ���������� ��������� ���� �������� 30 �� 20 ��������� ����.
	%PROGRAM% test_files\input.txt "%TEMP%\result.txt" 0 30 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\extract_incorrect_range.txt
	if ERRORLEVEL 1 goto err

rem 7) ������� ��������� ��� ���������� ��������� ���� ����������� ���-�� ����������.
	%PROGRAM% test_files\input.txt 0 30 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\extract_incorrect_argv.txt
	if ERRORLEVEL 1 goto err

rem 8) ������� ��������� ��� ���������� ��������� ���� �������� ����� �� ����������.
	%PROGRAM% test_files\input_no_exist.txt "%TEMP%\result.txt" 0 30 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\no_file.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1