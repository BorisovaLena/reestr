#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<malloc.h>
#include <time.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	HKEY hKey = NULL;
	if (RegOpenKeyW(HKEY_CURRENT_USER, NULL, &hKey) != ERROR_SUCCESS) return 1; //�������� ������� HKEY_CURRENT_USER
	HKEY tmp = NULL;
	if (RegCreateKey(hKey, L"MyKey", &tmp) == ERROR_SUCCESS) //�������� �����
	{
		MessageBox(NULL, L"���� ������", L"����������", MB_OK);
	}

	if (RegSetValueW(hKey, L"MyKey", REG_SZ,L"��������",22* sizeof(WCHAR)) == ERROR_SUCCESS) //��������� �������� �� ���������
	{
		MessageBox(NULL, L"��������� �������� ��������� �� ��������� ������� ��������", L"����������", MB_OK);
	}

	time_t t = time(NULL);
	char* tchar = ctime(&t);
	LPSTR s = tchar;

	if (RegSetValueExW(tmp, L"MyTextParam", NULL, REG_SZ, &s, 10) == ERROR_SUCCESS) //�������� ���������� ��������� � ������������ ��������
	{
		MessageBox(NULL, L"�������� ������ � ��� ��������� ��������", L"����������", MB_OK);
	}

	LPSTR DwValue = "";
	DWORD DataType = 0;
	DWORD DataLen = 512;

	if (RegGetValueW(hKey, L"Mykey", L"MyTextParam", RRF_RT_ANY, &DataType, &DwValue, &DataLen) == ERROR_SUCCESS) //����� �������� ���������
	{
		MessageBox(NULL, DwValue, L"�������� ���������", MB_OK);
	}
	else
	{
		MessageBox(NULL, L"���-�� ����� �� ���", L"����������", MB_OK);
	}

	if (RegDeleteValue(tmp, L"MyTextParam") == ERROR_SUCCESS) //�������� ���������
	{
		MessageBox(NULL, L"�������� ������", L"����������", MB_OK);
	}

	if (RegDeleteKey(hKey, L"MyKey") == ERROR_SUCCESS) //�������� �����
	{
		MessageBox(NULL, L"���� ������", L"����������", MB_OK);
	}

	RegCloseKey(tmp);
	RegCloseKey(hKey);

	return 0;
}