rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ������� ������� ��� ���� ���� �������� 255 ���� ���������� �������� ������ 
	%PROGRAM% pack test_files\input_255_insuccession.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_255_insuccession.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_successfully.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� ���� �������� 256 ���� ���������� �������� ������ 
	%PROGRAM% pack test_files\input_256_insuccession.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_256_insuccession.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_successfully.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� ���� �������� 257 ���� ���������� �������� ������ 
	%PROGRAM% pack test_files\input_257_insuccession.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\result_257_insuccession.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_successfully.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ���� �������� ������ � ����� 255
	%PROGRAM% pack test_files\input_alpha_255.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_alpha_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ����� ������������� ����� ��������
	%PROGRAM% unpack test_files\input_odd_pack.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_odd_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� � ������������ ����� ���-�� ���������� �������, ������ ����
	%PROGRAM% unpack test_files\input_alpha_zero_pack.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_zero_pack_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ���� ������� �����
	%PROGRAM% pack test_files\input_file_empty.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\result.txt" test_files\input_file_empty.txt
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_empty_file.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���� ��� ���������
	%PROGRAM% test_files\input_255_insuccession.txt "%TEMP%\result.txt" > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1