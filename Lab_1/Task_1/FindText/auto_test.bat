rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
chcp 1251
set PROGRAM="%~1"

rem ������� ������� ��� ���������� ��������� ���� ���� 1 ���������� � ������.
%PROGRAM% test_files\one_match_in_string.txt cat > "%TEMP%\one_match_in_string_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\one_match_in_string_output.txt" test_files\one_match_in_string_result.txt
if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���������� ��������� ���� ���� ������ ������ ���������� � ������.
%PROGRAM% test_files\more_match_in_string.txt cat > "%TEMP%\more_match_in_string_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\more_match_in_string_output.txt" test_files\more_match_in_string_result.txt
if ERRORLEVEL 1 goto err

rem ������� ������� ��� ���������� ��������� ���� ���� ��������� ���������� � ������ �������.
%PROGRAM% test_files\more_match_in_multi_string.txt cat > "%TEMP%\more_match_in_multi_string_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\more_match_in_multi_string_output.txt" test_files\more_match_in_multi_string_result.txt
if ERRORLEVEL 1 goto err

rem �������� ������ �� ������� �����.
%PROGRAM% test_files\yevganiy_onegin.txt "� � ��� ����" > "%TEMP%\yevganiy_onegin_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\yevganiy_onegin_output.txt" test_files\yevganiy_onegin_result.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ���, ���� � ����� ��� ������.
%PROGRAM% test_files\file_empty.txt cat > "%TEMP%\file_empty_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\file_empty_output.txt" test_files\file_empty_result.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ���, ���� ��� ���������� � �����-�������� �����.
%PROGRAM% test_files\non_match_in_string.txt dog > "%TEMP%\non_match_in_string_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\non_match_in_string_output.txt" test_files\file_empty_result.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ���, ���� ��� ���������� � �����-�������� �����.
%PROGRAM% test_files\non_match_in_multi_string.txt dog > "%TEMP%\non_match_in_multi_string_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\non_match_in_multi_string_output.txt" test_files\file_empty_result.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ���, ���� �� ������ ���������
%PROGRAM% test_files\one_match_in_string.txt > "%TEMP%\file_missing_argv_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\file_missing_argv_output.txt" test_files\file_missing_argv_result.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ���, ���� ����� �� ����������.
%PROGRAM% non-existing-file-name.txt arg > "%TEMP%\non_existing_file_name_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\non_existing_file_name_output.txt" test_files\file_missing_result.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1