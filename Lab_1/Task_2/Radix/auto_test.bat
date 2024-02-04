rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ������� ������� ��� ���� ��������� �� ������� �������
	%PROGRAM% 16 10 1F > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_31.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� ��������� ����������
	%PROGRAM% 10 10 8371973193 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_8371973193.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� ������ ��������� ������ �������
	%PROGRAM% 20 12 8371973193 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_57657A5120B3.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���� ������ ��������� ������ �������
	%PROGRAM% 12 27 8371973193 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_42EDH6FC.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ���, ���� �������� ����� 0 ��� ��������.
	%PROGRAM% 15 10 0 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_0.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ���, ���� �������� ��������� �� ������������ ��������� � ������������.
	%PROGRAM% 2 36 10101011101010101111111111010101011 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_AL1Y46J.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ���, ���� �������� ��������� �� ������������� ��������� � �����������.
	%PROGRAM% 36 2 AL1Y46J > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_10101011101010101111111111010101011.txt
	if ERRORLEVEL 1 goto err

rem ������� ������� ���, ���� �������� ������������� �����.
	%PROGRAM% 11 30 -8371973193 > "%TEMP%\output.txt"
	if ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_negative_QSEO8TL.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ���, ���� ���������� ���������� �� ������.
	%PROGRAM% 5 26 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_argv_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ���, ���� ������ �������� �� �����.
	%PROGRAM% str 20 8371973193 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_first_notation_no_digits.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ���, ���� ������ �������� = 1.
	%PROGRAM% 1 20 8371973193 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_first_notation_out_of_range.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ���, ���� ������ �������� = 37.
	%PROGRAM% 37 20 8371973193 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_first_notation_out_of_range.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ���, ���� ������ �������� �� �����.
	%PROGRAM% 20 str 8371973193 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_second_notation_no_digits.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ���, ���� ������ �������� = 1.
	%PROGRAM% 20 1 8371973193 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_second_notation_out_of_range.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ���, ���� ������ �������� = 37.
	%PROGRAM% 20 37 8371973193 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_second_notation_out_of_range.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ���, ���� ����� �� ������������� ������� ���������.
	%PROGRAM% 5 26 867859487213 > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_value_error.txt
	if ERRORLEVEL 1 goto err

rem ������� ��������� ���, ���� ����� �������� �� ���������� �������.
	%PROGRAM% 36 26 AL1-Y4!6J > "%TEMP%\output.txt"
	if NOT ERRORLEVEL 1 goto err
	fc.exe "%TEMP%\output.txt" test_files\output_value_error.txt
	if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1