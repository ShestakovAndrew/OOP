rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ������� ������� ��� ���������� ��������� ���� num = 110010000.
	%PROGRAM% 110010000 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_400.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���������� ��������� ���� binStr == 32 ������� ����.
	%PROGRAM% 00000000000000000000000000000000 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_0.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���������� ��������� ���� binStr == 32 ��������� ����.
	%PROGRAM% 11111111111111111111111111111111 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_4294967295.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���������� ��������� ���� binStr ����� ���������.
	%PROGRAM% 10101010101010101010101010101010 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_2863311530.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���������� ��������� ���� binStr ����� ���� ������� ����.
	%PROGRAM% 00010101010101010101010101010101 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_357913941.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���������� ��������� ���� binStr ��������� ������.
	%PROGRAM% string > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_binstr_arg_err.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���������� ��������� ���� binStr ������ 32.
	%PROGRAM% 0001010101010101010101010101010111 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_binstr_arg_err.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���������� ��������� ���� binStr ������ 32.
	%PROGRAM% > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1