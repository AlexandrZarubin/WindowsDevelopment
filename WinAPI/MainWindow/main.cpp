#include <iostream>

#include <sstream>
#include"resource.h"
#include<windows.h>
#define IDC_STATIC 1000
#define IDC_EDIT 1001
#define IDC_BUTTON 1002
//названием класса окна
CONST CHAR g_sz_WINDOW_CLASS[] = "My Main Window";

//функцию обработки сообщений окна
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Основная функция программы
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wClass;						// Создаем структуру WNDCLASSEX для регистрации класса окна
	ZeroMemory(&wClass, sizeof(wClass));	// Обнуляем структуру для инициализации всех полей значениями по умолчанию
	
	// Устанавливаем стиль окна
	wClass.style = 0;									// Стиль класса (0 - без дополнительных стилей)
	wClass.cbSize = sizeof(wClass);						// Размер структуры WNDCLASSEX
	wClass.cbClsExtra = 0;								// Дополнительная память для класса не используется
	wClass.cbWndExtra = 0;								// Дополнительная память для окна не используется

								// Загружаем крупную иконку для окна
	//wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);		
	wClass.hIcon = (HICON)LoadImage(
		NULL,					    //hInstance,					// Дескриптор ресурса (NULL, если загружаем из файла)
		"ICO\\HomeServer.ico",		//MAKEINTRESOURCE(IDI_ICON),	// Полный путь к крупному значку
		IMAGE_ICON,											// Тип изображения - значок
		LR_DEFAULTSIZE,													// Ширина значка
		LR_DEFAULTSIZE,													// Высота значка
		LR_LOADFROMFILE										// Флаг, указывающий на загрузку из файла
	);

								// Загружаем маленькую иконку для окна
	//wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));	
	wClass.hIconSm = (HICON)LoadImage(
		hInstance,										// Дескриптор текущего окна
		MAKEINTRESOURCE(IDI_ICON1),						// Идентификатор ресурса иконки
		IMAGE_ICON,										// Тип изображения - значок
		0,												// Ширина значка//16
		0,												// Высота значка//16
		LR_SHARED										// Флаг, указывающий на использование ресурса
	);
								// Загружаем курсор для окна
	//wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));
	//wClass.hCursor = (HCURSOR)(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));
	wClass.hCursor = (HCURSOR)LoadImage(
		hInstance,										// Дескриптор текущего окна
		//"CUR\\HOI4\\Busy Cursor.ani",
		MAKEINTRESOURCE(IDC_CURSOR1),					// Идентификатор ресурса курсора
		IMAGE_CURSOR,									// Тип ресурса - курсор
		0,									// Ширина (0 для использования размера по умолчанию)
		0,									// Высота (0 для использования размера по умолчанию)
		LR_SHARED										// Флаг совместного использования ресурса
		//LR_LOADFROMFILE								// Флаг совместного использования ресурса
	);		

	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;		// Цвет фона окна

	wClass.hInstance = hInstance;						// Дескриптор текущего приложения
	wClass.lpszMenuName = NULL;							// Указываем, что меню у окна нет
	wClass.lpszClassName = g_sz_WINDOW_CLASS;			// Имя класса окна
	wClass.lpfnWndProc = (WNDPROC)WndProc;				// Устанавливаем функцию обработки сообщений окна
												
								// Регистрируем класс окна
	if (!RegisterClassEx(&wClass))						
	{
		// Выводим сообщение об ошибке, если регистрация не удалась
		MessageBox(NULL, "Class registrtion failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}

	//	Получаем размеры экрана
	INT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	INT screenHeight = GetSystemMetrics(SM_CYSCREEN);
	// Рассчитываем размеры окна (75% экрана)
	INT windowWidth = static_cast<int>(screenWidth * 0.75);
	INT windowHeight = static_cast<int>(screenHeight * 0.75);
	// Рассчитываем координаты, чтобы окно было по центру
	INT windowPosX = (screenWidth - windowWidth) / 2;
	INT windowPosY = (screenHeight - windowHeight) / 2;
	//

	//2)Создание окна:
	HWND hwnd = CreateWindowEx
	(
		NULL,											// Расширенные стили окна (EX-styles)
		g_sz_WINDOW_CLASS,								// Имя класса окна
		g_sz_WINDOW_CLASS,								// Заголовок окна
		WS_OVERLAPPEDWINDOW,							//window style,такой стиль всегда задается для главного окна
		//CW_USEDEFAULT, CW_USEDEFAULT,					//Postion - положения окна при запуске
		//CW_USEDEFAULT, CW_USEDEFAULT,					//Size - размер создоваемго окна
		windowPosX, windowPosY,							//Postion - положения окна при запуске
		windowWidth, windowHeight,						//Size - размер создоваемго окна
		NULL,											// Родительское окно (NULL для главного окна)
		NULL,	//hMenu - для галвного окна это resourceID главного меню, (// Дескриптор меню)
		//для дочернего окна(Элемента какого-то окна) это resourceID соотвествующего элемента
		//По этому ResorceID нужный элемент всега можно получить GetDlgItem()
		//кроме того, этот ResorceID будет прилетать в параметре LOWORD(wParam) при воздеиствий пользователя
		hInstance,										// Дескриптор экземпляра приложения
		NULL											// Дополнительные параметры (NULL для главного окна)
	);
	if (hwnd == NULL)									// Если окно не удалось создать, выводим сообщение об ошибке
	{
		MessageBox(NULL, "Window create failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);	//Задает режим отображение окна(Развернуто на весь экран,Свернуто в окно, вернуто на пеньль задач)
	UpdateWindow(hwnd);			// Прорисовывает окно,
	
	//3)создание цикла сообщений
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		if (!IsDialogMessage(hwnd, &msg))
		{
			TranslateMessage(&msg);							// Преобразуем сообщения клавиатуры в удобный для обработки вид
			DispatchMessage(&msg);							// Отправляем сообщение в функцию обработки сообщений
		}
		
		//IsDialogMessage(hwnd, &msg);
	}

	return msg.wParam;									// Возвращаем код завершения программы
}
// Функция для обновления заголовка окна
void UpdateWindowTitle(HWND hwnd)
{
	RECT rect;											// Создаем структуру RECT для хранения координат окна
	//GetWindowRect заполняет структуру rect координатами окна hwnd относительно экрана.(0-неудача)
	if (GetWindowRect(hwnd, &rect))						// Получаем координаты окна на экране
	{
		/* 
		std::ostringstream: Используется для вывода данных в строку.
		std::istringstream: Используется для ввода данных из строки.
		std::stringstream: Поддерживает как ввод, так и вывод операций на строках.
		std::ifstream: Поток ввода из файла, для чтения из файлов.
		std::ofstream: Поток вывода в файл, для записи в файлы.
		std::fstream: Поток файла, поддерживающий как ввод, так и вывод.
		*/
		std::ostringstream oss;							// Создаем поток для формирования строки
		// rect.left и rect.top — координаты верхнего левого угла окна относительно экрана.
		oss << g_sz_WINDOW_CLASS <<" \"Position: (" << rect.left << ", " << rect.top << ") "
			//rect.right - rect.left вычисляет ширину окна. rect.bottom - rect.top вычисляет высоту окна.
			<< "Size: (" << rect.right - rect.left << "x" << rect.bottom - rect.top << ")\"";
		//SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)oss.str().c_str());
		SetWindowText(hwnd, oss.str().c_str());			// Устанавливаем новый заголовок окна
	}
}
INT WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:										// Сообщение о создании окна
	{

		HWND hStatic = CreateWindowEx(
			NULL,
			"Static",
			"Этот статический текст создан функцией CreateWindwosEX()",
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			10, 10,
			800, 22,
			hwnd,
			(HMENU)1000,
			GetModuleHandle(NULL),
			NULL

		);

		HWND hStaticText = CreateWindowEx(
			NULL,
			"EDIT",
			"",
			WS_CHILD | WS_VISIBLE|WS_BORDER|ES_CENTER | WS_TABSTOP,
			10, 32,
			500, 22,
			hwnd,
			(HMENU)1001,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hButton = CreateWindowEx(
			NULL,
			"BUTTON",
			"Применить",
			WS_CHILD | WS_VISIBLE|BS_PUSHBUTTON|WS_TABSTOP,
			410, 58,
			100, 32,
			hwnd,
			(HMENU)1002,
			GetModuleHandle(NULL),
			NULL
		);
	}
		break;
	case WM_MOVE:										// Сообщение при перемещении окна (после завершения перемещения)
	//case WM_MOVING:										// Сообщение при процессе перемещения окна
	case WM_SIZE:										// Сообщение при изменении размера окна(после завершения изменения)
	//case WM_SIZING:										// Сообщение при процессе изменения размера окна
		UpdateWindowTitle(hwnd);						// Обновляем заголовок окна
		break;

	case WM_COMMAND:									// Сообщение о взаимодействии с элементами управления
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
		{
			HWND hStatic = GetDlgItem(hwnd, IDC_STATIC);
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			break;
		}

		}
		break;
	case WM_DESTROY:									// Сообщение о закрытии окна
		PostQuitMessage(0);								// Завершаем приложение
		break;
	case WM_CLOSE:										// Сообщение о запросе закрытия окна
		DestroyWindow(hwnd);							// Уничтожаем окно
		break;
		
		// Все не обрабатываемые сообщения отправляем на стандартную обработку
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam); 
	}
}
