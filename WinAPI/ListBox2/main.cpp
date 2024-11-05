#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<cstdio>
#include"resource.h"
#include<string>
#include<vector>
#include <algorithm>

CONST CHAR* init_values[] = { "This","is","my","first","Combo","Box" };

INT_PTR CALLBACK DlgProc(HWND jwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK InputDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT mCmdShow)
{
	// Создаем модальное диалоговое окно с идентификатором IDD_DIALOG1 и функцией обратного вызова DlgProc
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}
INT_PTR CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hList = GetDlgItem(hwnd, IDC_LIST_BOX);		// Получаем дескриптор

		if (!hList)											// Если не удалось получить дескриптор
		{
			MessageBox(hwnd, "Ошибка: IDC_LIST_BOX не найден.", "Ошибка", MB_OK | MB_ICONERROR);
			return FALSE;
		}

		HFONT hFont = (HFONT)GetStockObject(SYSTEM_FONT);	// Получаем дескриптор стандартного системного шрифта

		SendMessage(hList, WM_SETFONT, (WPARAM)hFont, TRUE);// Устанавливаем шрифт для списка
		/*
		for (int i = 0; i < sizeof(init_values) / sizeof(init_values[0]); ++i)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)init_values[i]);	// Добавляем строку в список
		}
		*/

		int num_items = sizeof(init_values) / sizeof(init_values[0]);
		for (int i = num_items - 1; i >= 0; i--)
		{
			SendMessage(hList, LB_INSERTSTRING, 0, (LPARAM)init_values[i]);
		}
		return TRUE;
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case IDC_ADD:						// Если нажата кнопка Добавить
		{
			CHAR input_text[256] = { 0 };	// Создаем буфер для ввода текста

			// Открываем модальное диалоговое окно для ввода текста (IDD_INPUT_DIALOG)
			// Передаем буфер input_text в качестве параметра lParam
			if (DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INPUT_DIALOG), hwnd, InputDlgProc, reinterpret_cast<LPARAM>(input_text)) == IDOK)
			{
				if (strlen(input_text) > 0)	// Если введенный текст не пустой
				{
				HWND hList = GetDlgItem(hwnd, IDC_LIST_BOX);			// Получаем дескриптор
				///
				//SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)input_text);// Добавляем введенный текст
				///
				SendMessage(hList, LB_INSERTSTRING, 0, (LPARAM)input_text);	// Вставляем новый элемент в начало списка
				SendMessage(hList, LB_SETCURSEL, 0, 0);						// Фокус на новый элемент
				}
				else						// Если введенный текст пустой
				{
					MessageBox(hwnd, "Пожалуйста, введите непустую строку.", "Ошибка", MB_OK | MB_ICONERROR);
				}
			}
			break;
		}
		case IDC_DELETE:										// Если нажата кнопка Удалить
		{
			HWND hList = GetDlgItem(hwnd, IDC_LIST_BOX);		// Получаем дескриптор
			INT index = SendMessage(hList, LB_GETCURSEL, 0, 0);	// Получаем индекс выбранного элемента в списке
			if (index != LB_ERR)								// Если элемент выбран (индекс не равен ошибке), удаляем его из списка
				SendMessage(hList, LB_DELETESTRING, index, 0);
			break;
		}
		case IDOK:													// Если нажата кнопка "OK"
		{

			HWND hCombo = GetDlgItem(hwnd, IDC_LIST_BOX);			// Получаем дескриптор
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};									// Буфер для хранения текста выбранного элемента
			CHAR sz_message[SIZE]{};								// Буфер для сообщения пользователю
			INT i = SendMessage(hCombo, LB_GETCURSEL, 0, 0);		// Получаем индекс выбранного элемента
			SendMessage(hCombo, LB_GETTEXT, i, (LPARAM)sz_buffer);	// Получаем текст выбранного элемента и сохраняем в sz_buffer
			sprintf(sz_message, "Вы выбрали пункт N%i со занчением \"%s\"", i, sz_buffer);	// Формируем сообщение с информацией о выборе пользователя
			MessageBox(hwnd, sz_message, "Selection value", MB_OK | MB_ICONINFORMATION);	// Показываем сообщение с информацией о выбранном элементе
			break;
		}
		case IDCANCEL:EndDialog(hwnd, 0); break;					// Если нажата кнопка Отмена, Закрываем диалоговое окно
		case IDC_SORT:
		{
			HWND hList = GetDlgItem(hwnd, IDC_LIST_BOX);			// Получаем дескриптор ListBox
			int itemCount = SendMessage(hList, LB_GETCOUNT, 0, 0);	// Получаем количество элементов в списке
			if (itemCount > 1)
			{
				std::vector<std::string> items;						// Создаем вектор
				CHAR buffer[256];									//
				for (int i = 0; i < itemCount; i++)
				{
					SendMessage(hList, LB_GETTEXT, i, (LPARAM)buffer);
					items.push_back(buffer);
				}
				std::sort(items.begin(), items.end());				// Сортируем элементы
				SendMessage(hList, LB_RESETCONTENT, 0, 0);			// Очищаем ListBox

				for (const auto& item : items)
				{
					SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)item.c_str());// Добавляем отсортированные элементы обратно
				}
			}
		}
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;													// Возвращаем FALSE, если сообщение не было обработано
}
INT_PTR CALLBACK InputDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CHAR* sz_buffer;																	// Указатель на буфер для ввода текста
	switch (uMsg)
	{
	case WM_INITDIALOG:																	// инициализации диалогового окна
		sz_buffer = reinterpret_cast<CHAR*>(lParam);									// Преобразуем lParam в указатель на CHAR и сохраняем его в sz_buffer
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(sz_buffer));	// Сохраняем указатель sz_buffer в данных окна, чтобы иметь к нему доступ позже
		SetDlgItemText(hwnd, IDC_INPUT_TEXT, "default text");							// Устанавливаем текст по умолчанию в поле ввода (IDC_INPUT_TEXT)
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_INPUT_OK:																// Если нажата кнопка OK
		{
			sz_buffer = reinterpret_cast<CHAR*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));	// Получаем сохраненный указатель на буфер из данных окна
			
			if (!sz_buffer)																// Если указатель недоступен
			{
				MessageBox(hwnd, "Ошибка: указатель sz_buffer недоступен.", "Ошибка", MB_OK | MB_ICONERROR);
				return FALSE;
			}

			HWND hEdit = GetDlgItem(hwnd, IDC_INPUT_TEXT);								// Получаем дескриптор
			
			if (!hEdit)																	// Если не удалось получить дескриптор
			{
				MessageBox(hwnd, "Ошибка: IDC_INPUT_TEXT не найден или не доступен.", "Ошибка", MB_OK | MB_ICONERROR);
				return FALSE;
			}

			GetDlgItemText(hwnd, IDC_INPUT_TEXT, sz_buffer, 256);						// Получаем текст из поля ввода и сохраняем в sz_buffer

			if (strlen(sz_buffer) == 0)													// Если введенный текст пустой
			{
				MessageBox(hwnd, "Пустое поле!", "Диагностика", MB_OK | MB_ICONWARNING);
				return TRUE;
			}
			EndDialog(hwnd, IDOK);
			return TRUE;
		}
		case IDC_INPUT_CANCEL:															// Если нажата кнопка Отмена
			EndDialog(hwnd, IDCANCEL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}