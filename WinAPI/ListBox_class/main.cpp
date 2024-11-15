//#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include"resource.h"
#include<cstdio>
#include<string>
CONST CHAR* g_VALUES[] = { "This","is","my","first","List","Box" };

BOOL CALLBACK DlgProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
INT_PTR CALLBACK DlgProcAddItem(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		// Загружаем иконку из ресурсов
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		// Устанавливаем иконку для окна диалога
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		// Получаем дескриптор ListBox
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
		// Заполняем ListBox начальными значениями из массива
		for (int i = 0; i < sizeof(g_VALUES) / sizeof(g_VALUES[0]); ++i)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)g_VALUES[i]);	// Добавляем строку в список
		}
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_ADD:	// Обработка нажатия кнопки "Добавить"
			// Открываем диалог добавления нового элемента
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD_ITEM), hwnd, DlgProcAddItem, (LPARAM)LB_ERR);
			break;
		case IDC_BUTTON_REMOVE:// Обработка нажатия кнопки "Удалить"
		{
			// Получаем дескриптор ListBox
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
			
			// Получаем индекс выбранного элемента
			if((SendMessage(hListBox, LB_GETCURSEL, 0, 0))!=LB_ERR)
				SendMessage(hListBox, LB_DELETESTRING, SendMessage(hListBox, LB_GETCURSEL, 0, 0), 0);	// Удаляем выбранный элемент
			else
				MessageBox(hwnd, "Выберите элемент для удаления.", "Ошибка", MB_OK | MB_ICONERROR);		// Сообщение об ошибке
		}
		break;
		case IDOK:
		{
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST);			// Получаем дескриптор ListBox
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};								// Буфер для хранения текста элемента
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);	// Получаем индекс выбранного элемента
			if (i != LB_ERR)
			{
			SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);	// Получаем текст выбранного элемента

			/*
			//MessageBox(hwnd, sz_buffer, "Info", MB_OK|MB_ICONINFORMATION);
			CHAR sz_message[SIZE]{};
			sprintf(sz_message, "Вы выбрали пункт N%i со занчением \"%s\"", i, sz_buffer);
			MessageBox(hwnd, sz_message, "Selection value", MB_OK | MB_ICONINFORMATION);
			*/

			// Создаем сообщение для отображения информации о выбранном элементе
			std::string sz_message = "Вы выбрали пункт N" + std::to_string(i) + " со значением \"" + sz_buffer + "\"";
			MessageBox(hwnd, sz_message.c_str(), "Selection value", MB_OK | MB_ICONINFORMATION);	// Отображаем сообщение
			}
			else
				MessageBox(hwnd, "Выберите элемент.", "Ошибка", MB_OK | MB_ICONERROR);				// Сообщение об ошибке, если ничего не выбрано
		}
			break;
			case IDCANCEL: EndDialog(hwnd, 0); break;// Закрываем диалог
	case IDC_LIST:								// Обработка уведомлений от ListBox
		{
			if (HIWORD(wParam) == LBN_DBLCLK)	// Обработка двойного щелчка по элементу списка
			{
				HWND hListBox = GetDlgItem(hwnd, IDC_LIST);				// Получаем дескриптор ListBox
				INT index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);// Получаем индекс выбранного элемента
				if (index != LB_ERR)
				{
					// Открываем диалог редактирования элемента (передаем индекс элемента как lParam)
					DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD_ITEM), hwnd, DlgProcAddItem, (LPARAM)index);
				}
			}
		}
			break;
		}
		break;
	case WM_CLOSE:// Обработка закрытия диалога (например, нажатие на крестик)
		EndDialog(hwnd,0);break;
		//EndDialog(hwnd, IDCANCEL);break;

	}
	return FALSE;// Возвращаем FALSE, чтобы указать, что сообщение не было полностью обработано
}
INT_PTR CALLBACK DlgProcAddItem(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{

		INT editIndex = (INT)lParam;								// Получаем индекс редактируемого элемента
		if (editIndex != LB_ERR)									// Если редактируется существующий элемен
		{	
			HWND hParent = GetParent(hwnd);							// Получаем дескриптор родительского окна
			HWND hListBox = GetDlgItem(hParent, IDC_LIST);			// Получаем дескриптор ListBox

			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage(hListBox, LB_GETTEXT, editIndex, (LPARAM)sz_buffer);	// Получаем текст редактируемого элемента

			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_ADD_ITEM);					// Получаем дескриптор Edit Control
			SetWindowText(hEdit, sz_buffer);									// Устанавливаем текст в Edit Control
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)lParam);				// Сохраняем индекс редактируемого элемента
		
		//HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_ADD_ITEM);
		//SetFocus(hEdit);
		SetFocus(GetDlgItem(hwnd, IDC_EDIT_ADD_ITEM));							// Устанавливаем фокус на поле ввода
		return FALSE;															// Возвращаем FALSE, так как фокус уже установлен
	}
		//break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			//1)Читаем текст из EditControl
			CONST INT SIZE = 256;
			CHAR sz_buffer[256]{};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_ADD_ITEM);					// Получаем дескриптор Edit Control
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);			// Читаем текст из Edit Control
			//2) Получаем родительское окно
			HWND hParent = GetParent(hwnd);										// Получаем дескриптор родительского окна
			//3)Получаем дискриптор ListBox
			HWND hListBox = GetDlgItem(hParent, IDC_LIST);						// Получаем дескриптор ListBox
			//4)Добавляем текст в ListBox:
			INT editIndex = (INT)GetWindowLongPtr(hwnd, GWLP_USERDATA);			// Получаем индекс редактируемого элемента
			INT foundIndex = SendMessage(hListBox, LB_FINDSTRINGEXACT, -1, (LPARAM)sz_buffer);	// Проверяем на дубликаты
			if (foundIndex != LB_ERR && foundIndex != editIndex)		// Если такой элемент уже существует и это не текущий элемент
			{
				MessageBox(hwnd, "Такое значение уже существует в списке.", "Ошибка", MB_OK | MB_ICONERROR);
				return TRUE;											// Прерываем обработку
			}
			if (editIndex != LB_ERR)									// Если редактируем существующий элемент
			{
				SendMessage(hListBox, LB_DELETESTRING, editIndex, 0);					// Удаляем старый элемент
				SendMessage(hListBox, LB_INSERTSTRING, editIndex, (LPARAM)sz_buffer);	// Вставляем новый текст на то же место
			}
			else															// Если добавляем новый элемент//
			{
				SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)sz_buffer);	// Добавляем новый элемент в конец списка
			}
		}
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}