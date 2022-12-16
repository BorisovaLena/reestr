#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<malloc.h>
#include <time.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	HKEY hKey = NULL;
	if (RegOpenKeyW(HKEY_CURRENT_USER, NULL, &hKey) != ERROR_SUCCESS) return 1; //открытие раздела HKEY_CURRENT_USER
	HKEY tmp = NULL;
	if (RegCreateKey(hKey, L"MyKey", &tmp) == ERROR_SUCCESS) //создание ключа
	{
		MessageBox(NULL, L"Ключ создан", L"Информация", MB_OK);
	}

	if (RegSetValueW(hKey, L"MyKey", REG_SZ,L"Значение",22* sizeof(WCHAR)) == ERROR_SUCCESS) //изменение значения по умолчанию
	{
		MessageBox(NULL, L"Изменение значения параметра по умолчанию успешно изменено", L"Информация", MB_OK);
	}

	SYSTEMTIME t;
	GetLocalTime(&t);
	LPWSTR s = calloc(512, sizeof(WCHAR));
	swprintf(s, 512,  L"%d.%d.%d %d:%d:%d", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond);

	if (RegSetValueExW(tmp, L"MyTextParam", NULL, REG_SZ, s, 512) == ERROR_SUCCESS) //создание строкового параметра и присваивание значения
	{
		MessageBox(NULL, L"Параметр создан и ему присвоено значение", L"Информация", MB_OK);
	}

	LPWSTR DwValue = calloc(512,sizeof(WCHAR));
	DWORD DataType = 0;
	DWORD DataLen = 512;

	if (RegGetValueW(hKey, L"Mykey", L"MyTextParam", RRF_RT_ANY, &DataType, DwValue, &DataLen) == ERROR_SUCCESS) //вывод значение параметра
	{
		MessageBox(NULL, DwValue, L"Значение параметра", MB_OK);
	}
	else
	{
		MessageBox(NULL, L"Что-то пошло не так", L"Информация", MB_OK);
	}

	if (RegDeleteValue(tmp, L"MyTextParam") == ERROR_SUCCESS) //удаление параметра
	{
		MessageBox(NULL, L"Параметр удален", L"Информация", MB_OK);
	}

	if (RegDeleteKey(hKey, L"MyKey") == ERROR_SUCCESS) //удаление ключа
	{
		MessageBox(NULL, L"Ключ удален", L"Информация", MB_OK);
	}

	RegCloseKey(tmp);
	RegCloseKey(hKey);

	return 0;
}