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

	SYSTEMTIME t;
	GetLocalTime(&t);
	LPWSTR s = calloc(512, sizeof(WCHAR));
	swprintf(s, 512,  L"%d.%d.%d %d:%d:%d", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond);

	if (RegSetValueExW(tmp, L"MyTextParam", NULL, REG_SZ, s, 512) == ERROR_SUCCESS) //�������� ���������� ��������� � ������������ ��������
	{
		MessageBox(NULL, L"�������� ������ � ��� ��������� ��������", L"����������", MB_OK);
	}

	LPWSTR DwValue = calloc(512,sizeof(WCHAR));
	DWORD DataType = 0;
	DWORD DataLen = 512;

	if (RegGetValueW(hKey, L"Mykey", L"MyTextParam", RRF_RT_ANY, &DataType, DwValue, &DataLen) == ERROR_SUCCESS) //����� �������� ���������
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