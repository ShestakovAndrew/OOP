rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
chcp 1251
set PROGRAM="%~1"

rem ������� ������� ��� ���������� ��������� ���� ���� 1 ������� ����.
%PROGRAM% test_files\first_input_multiline.txt "%TEMP%\one_file_result.txt" > "%TEMP%\one_file_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\one_file_result.txt" test_files\first_input_multiline.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\one_file_output.txt" test_files\join_successfully.txt
if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���������� ��������� ���� ���� 2 ������� �����.
%PROGRAM% test_files\first_input_multiline.txt test_files\second_input_multiline.txt "%TEMP%\two_files_result.txt" > "%TEMP%\two_files_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\two_files_result.txt" test_files\two_files_result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\two_files_output.txt" test_files\join_successfully.txt
if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���������� ��������� ���� ���� 2 ������� ����� (������ ���� �� 1 ������).
%PROGRAM% test_files\first_input_multiline.txt test_files\second_input_line.txt "%TEMP%\two_files_result.txt" > "%TEMP%\two_files_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\two_files_result.txt" test_files\two_files_result_v2.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\two_files_output.txt" test_files\join_successfully.txt
if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���������� ��������� ���� ���� 3 ������� �����.
%PROGRAM% test_files\first_input_multiline.txt test_files\second_input_multiline.txt test_files\third_input_multiline.txt "%TEMP%\three_files_result.txt" > "%TEMP%\three_files_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\three_files_result.txt" test_files\three_files_result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\three_files_output.txt" test_files\join_successfully.txt
if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���������� ��������� ���� ���� 3 ������� ����� (������ ������� ���� ������).
%PROGRAM% test_files\first_input_multiline.txt test_files\second_input_empty.txt test_files\third_input_multiline.txt "%TEMP%\three_files_result_v2.txt" > "%TEMP%\three_files_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\three_files_result_v2.txt" test_files\three_files_result_v2.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\three_files_output.txt" test_files\join_successfully.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���������� ��������� ���� ���� 2 ������ ������� �����
%PROGRAM% test_files\first_input_empty.txt test_files\second_input_empty.txt "%TEMP%\two_files_empty_result.txt" > "%TEMP%\two_files_empty_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\two_files_empty_result.txt" test_files\file_empty_result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\two_files_empty_output.txt" test_files\nothing_to_join.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ���������� ��������� ���� ���� 1 �������������� ������� ����
%PROGRAM% test_files\non_exist_input_file.txt test_files\second_input_empty.txt "%TEMP%\non_exist_input_file_result.txt" > "%TEMP%\non_exist_input_file_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\non_exist_input_file_result.txt" test_files\file_empty_result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\non_exist_input_file_output.txt" test_files\file_missing_result.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ���, ���� �� ������ ���������
%PROGRAM% "%TEMP%\no_input_file_result.txt" > "%TEMP%\no_input_file_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\no_input_file_output.txt" test_files\file_missing_argv_result.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1