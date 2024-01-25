rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� �������
rem (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��������� ����������� ������� ����� (�������� ��� �� ��������� ����� �������� ������������)
%PROGRAM% test_files\empty.txt %TEMP%\empty.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\empty.txt test_files\empty.txt
if ERRORLEVEL 1 goto err

rem ��������� ����������� ����� �� ����� ������
%PROGRAM% test_files\one-line.txt %TEMP%\one-line.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\one-line.txt test_files\one-line.txt
if ERRORLEVEL 1 goto err

rem ��������� ����������� ����� �� ���������� �����
%PROGRAM% test_files\multiline.txt %TEMP%\multiline.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\multiline.txt test_files\multiline.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ��� ����������� ��������������� �����
%PROGRAM% non-existing-file-name.txt %TEMP%\non-existing-file-name.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test_files\expected-output-when-input-file-is-missing.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ��� ������������� ������ � �������� ���� (� ����������� ���� ���������)
%PROGRAM% test_files\multiline.txt %PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1