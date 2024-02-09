rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ������� ������� ��� ���� bmp 1 ��� �� �������
	%PROGRAM% test_files\input_1.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_1.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� bmp 4 ���� �� �������
	%PROGRAM% test_files\input_4.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_4.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� bmp 8 ��� �� �������
	%PROGRAM% test_files\input_8.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_8.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� bmp 24 ���� �� �������
	%PROGRAM% test_files\input_24.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_24.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� ������������ RLE ���������� ������.
	%PROGRAM% test_files\input_8_rle.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_8_rle.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� � bfReserved �� �������� ����
	%PROGRAM% test_files\input_file_reserved_error.bmp > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_incorrect_reserved.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ���� ������
	%PROGRAM% test_files\input_empty_file.bmp > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_empty_file_error.txt
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