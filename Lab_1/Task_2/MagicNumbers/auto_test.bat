rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ������� ����� Non_magic ���� ����� 0.
	%PROGRAM% < test_files\input_0.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_non_magic.txt
	if ERRORLEVEL 1 goto err

rem ������� ����� Non_magic ���� ����� 1.
	%PROGRAM% < test_files\input_1.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_non_magic.txt
	if ERRORLEVEL 1 goto err

rem ������� ����� Non_magic ���� ����� 18446744073709551615.
	%PROGRAM% < test_files\input_18446744073709551615.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_non_magic.txt
	if ERRORLEVEL 1 goto err

rem ������� ����� Error ���� ����� 18446744073709551616.
	%PROGRAM% < test_files\input_18446744073709551616.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ����� Error ���� ����� �� �����.
	%PROGRAM% < test_files\input_string.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ����� Error ���� ������ �� �������.
	%PROGRAM% < test_files\input_empty.txt > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ���������� ��������� ���� �������� ������ ��������� � N = 20.
	%PROGRAM% --find 20 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_N_20.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ���������� ��������� ���� �������� ������ �� ���������.
	%PROGRAM% --find > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1