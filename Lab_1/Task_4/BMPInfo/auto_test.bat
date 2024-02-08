rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ������� ������� ��� ���� HEADER ���������
	%PROGRAM% test_files\input_correct_file.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_correct_file.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� HEADER mono ��������� 
	%PROGRAM% test_files\input_file_mono.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_file_mono.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� ������������ RLE ���������� ������.
	%PROGRAM% test_files\input_file_RLE_compression.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_file_RLE_compression.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� � HEADER little-endian
	%PROGRAM% test_files\input_file_LE.bmp > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_LE.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� � HEADER bfReserved1 �� �������� ����
	%PROGRAM% test_files\input_file_reserved_error.bmp > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_incorrect_file.txt
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