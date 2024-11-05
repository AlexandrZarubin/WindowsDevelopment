#define _CRT_SECURE_NO_WARNINGS		// Отключает предупреждения о небезопасных функциях
#include<windows.h>					// Включает функции Windows API
#include<cstdio>					// Библиотека C для работы с вводом/выводом
#include"resource.h"				
#include<string>

// Массив строк, которые будут добавлены в ComboBox (выпадающий список)
CONST CHAR* init_values[] = { "This","is","my","first","Combo","Box" };

// Объявление функции обработки сообщений диалогового окна
BOOL CALLBACK DlgProc(HWND jwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// hInstance — это дескриптор текущего экземпляра программы.
// hPrevInstance — в 32-битных версиях Windows не используется (всегда NULL), но раньше указывал на предыдущий экземпляр программы.
// LPSTR -longPointer to string (Указатель на строку наподобие const char*)
// lpCmdLine — строка команд, переданная программе (без имени программы). командная строка запуска приложенеия 
// nCmdShow — указывает, как нужно отображать окно (например, свернутое, развернутое и т.д.).
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT mCmdShow)
{
	DialogBoxParam  // Создаем модальное диалоговое окно, используя функцию-обработчик DlgProc для обработки сообщений
	(
		hInstance,						// hInstance: Дескриптор текущего экземпляра приложения
		MAKEINTRESOURCE(IDD_DIALOG1),	// MAKEINTRESOURCE(IDD_DIALOG1): ID диалогового окна, преобразованный в указатель на строку
		NULL,							// NULL: Родительское окно не задается
		(DLGPROC)DlgProc, 0				// Указатель на функцию-обработчик сообщений DlgProc
	);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)			// Обрабатываем различные сообщения, которые приходят в диалоговое окно
	{
	case WM_INITDIALOG:		// Сообщение, которое приходит при инициализации диалогового окна
	{
		// Инициализируем ComboBox (выпадающий список) при открытии диалога
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);	// Получаем дескриптор ComboBox по его ID (IDC_COMBO1)
			for (int i = 0; i < sizeof(init_values) / sizeof(init_values[0]); ++i)	// Добавляем каждую строку из массива init_values в ComboBox
			{
				SendMessage					// Отправляем сообщение CB_ADDSTRING для добавления строки в ComboBox
				(
					hCombo,					// Дескриптор ComboBox, куда добавляется строка
					CB_ADDSTRING,			// Код сообщения для добавления строки в ComboBox
					0,						// wParam: для CB_ADDSTRING не используется, поэтому ставим 0
					(LPARAM)init_values[i]	// lParam: строка, которая будет добавлена
				);
			}
			
	}
		break;
	case WM_COMMAND:		// Обработка командных сообщений, таких как нажатие кнопок
		switch (LOWORD(wParam))	// Получаем низшее слово (LOWORD) параметра wParam для определения команды
		{
		case IDOK:			// Если нажата кнопка "OK"
		{

			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);		// Получаем дескриптор ComboBox
			CONST INT SIZE = 256;							// Определяем размер буфера
			CHAR sz_buffer[SIZE]{};							// Буфер для хранения текста выбранного элемента
			//CHAR sz_message[SIZE]{};
			
			INT i = SendMessage								// Получаем индекс выбранного элемента в ComboBox
			(
				hCombo,										// Дескриптор ComboBox
				CB_GETCURSEL,								// Код сообщения для получения текущего выбранного элемента
				0,											// wParam: не используется для CB_GETCURSEL
				0											// lParam: не используется для CB_GETCURSEL
			);												//сообщение cb_getcursel (current selection) возвращает номер выбранного пункта combobox

			SendMessage
			(
				hCombo,										// Дескриптор ComboBox
				CB_GETLBTEXT,								// Код сообщения для получения текста элемента по индексу
				i,											// wParam: индекс выбранного элемента
				(LPARAM)sz_buffer							// lParam: буфер для хранения текста элемента
			);

			// Создаем строку с сообщением, включающим индекс и текст выбранного элемента
			std::string sz_message = "Вы выбрали пункт N" + std::to_string(i) + " со значением \"" + sz_buffer + "\"";
			//sprintf(sz_message, "Вы выбрали пункт N%i со занчением \"%s\"", i,sz_buffer);
			//MessageBox(hwnd, sz_message, "Selection value", MB_OK | MB_ICONINFORMATION);

			MessageBox										// Отображаем сообщение с выбранным элементом в MessageBo
			(
				hwnd,										// Дескриптор окна-родителя (текущего диалога)
				sz_message.c_str(),							// Текст сообщения
				"Selection value",							// Заголовок окна сообщения
				MB_OK | MB_ICONINFORMATION					// Флаги: MB_OK — добавить кнопку OK, MB_ICONINFORMATION — значок информации
			);
			break;
		}
		case IDCANCEL:EndDialog(hwnd, 0); break;			// Если нажата кнопка "Cancel"
		}
		break;
	case WM_CLOSE:											// Обработка закрытия окна (кнопка "X" в заголовке окна)
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}

/*
CB_ADDSTRING — сообщение для добавления строки в ComboBox:

hCombo: Дескриптор ComboBox, куда добавляется строка.
CB_ADDSTRING : Код сообщения для добавления строки.
wParam : Не используется для CB_ADDSTRING, поэтому указываем 0.
lParam : Указатель на строку, которую нужно добавить, т.е., init_values[i].
-------------------------------------------------------------------------------
CB_GETCURSEL — сообщение для получения индекса текущего выбранного элемента :

hCombo: Дескриптор ComboBox.
CB_GETCURSEL : Код сообщения для получения индекса выбранного элемента.
wParam : Не используется для CB_GETCURSEL, поэтому 0.
lParam : Не используется для CB_GETCURSEL, поэтому 0.
-------------------------------------------------------------------------------
CB_GETLBTEXT — сообщение для получения текста элемента по индексу :

hCombo: Дескриптор ComboBox.
CB_GETLBTEXT : Код сообщения для получения текста.
wParam : Индекс элемента, текст которого нужно получить(в данном случае, i).
lParam : Указатель на буфер для хранения текста, т.е., sz_buffer.
*/




