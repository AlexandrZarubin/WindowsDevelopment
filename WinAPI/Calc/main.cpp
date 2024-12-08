#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<string.h>
#include"resource.h"
#include"Dimensions.h"


CONST CHAR g_sz_WINDOW_CLASS[] = "CALC_VPD_311";
CONST CHAR* g_OPERATIONS[] = { "+","-","*","/" };

struct CalculatorState
{
	DOUBLE operand1;
	DOUBLE operand2;
	CHAR operation;
}g_calcState = { 0.0,0.0,'\0' };

INT CALLBACK  WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPrama);
INT GetTitlVarHeight(HWND hwnd)
{
	RECT window_rect;
	RECT client_rect;
	GetWindowRect(hwnd, &window_rect);
	GetClientRect(hwnd, &client_rect);
	int title_bar_height = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);
	return title_bar_height;
}
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1)Регистрация класса окна
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_ARROW));
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	//wClass.hbrBackground = CreateSolidBrush(RGB(217, 228, 241));
	
	wClass.hInstance = hInstance;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpfnWndProc = (WNDPROC)WndProc;

	//Регистрация окна
	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	//2)Создание окна:
	HWND hwnd = CreateWindowEx(
		NULL,
		g_sz_WINDOW_CLASS,
		g_sz_WINDOW_CLASS,
		WS_OVERLAPPEDWINDOW ^WS_THICKFRAME ^WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		g_i_WINDOW_WIDTH+16, g_i_window_HIGHT+39,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//3)Запуск цикла сообщения:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
INT CALLBACK  WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hEdit = CreateWindowEx(
			NULL, "Edit", "0",
			WS_CHILD | WS_VISIBLE | WS_BORDER|ES_RIGHT,
			10, 10,
			g_i_SCREEN_WIDTH, g_i_SCREEN_HEIGHT,
			hwnd,
			(HMENU)999,
			GetModuleHandle(NULL),
			NULL
		);
		CHAR sz_digit[2] = {};
		for (int i = 6; i >= 0; i -= 3)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = i + j+'1';
				CreateWindowEx
				(
					NULL, "Button", sz_digit,
					WS_CHILD | WS_VISIBLE,
					BUTTON_SHIFT_X(j), BUTTON_SHIFT_Y(2 - i / 3),
					//g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * j,
					//g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (2-i/3),
					g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_1 + (i + j)),
					GetModuleHandle(NULL),
					NULL
				);
			}
		}
		CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE,
			BUTTON_SHIFT_X(0), BUTTON_SHIFT_Y(3),
			//g_i_BUTTON_START_X ,
			//g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE,
			BUTTON_SHIFT_X(2), BUTTON_SHIFT_Y(3),
			//g_i_BUTTON_START_X+(g_i_BUTTON_SIZE+g_i_INTERVAL)*2,
			//g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL),
			NULL
		);
		for (int i = 0; i < 4; i++)
		{
			CreateWindowEx
			(
				NULL, "Button", g_OPERATIONS[i],
				WS_CHILD | WS_VISIBLE,
				BUTTON_SHIFT_X(3),BUTTON_SHIFT_Y(3-i),
				//g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (3-i),
				g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
				hwnd,
				(HMENU)(IDC_BUTTON_PLUS+i),
				GetModuleHandle(NULL),
				NULL
			);
		}
		CreateWindowEx
		(
			NULL, "Button", "<-",
			WS_CHILD | WS_VISIBLE,
			BUTTON_SHIFT_X(4),BUTTON_SHIFT_Y(0),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_BSP,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "C",
			WS_CHILD | WS_VISIBLE,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(1),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLR,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(2),
			g_i_BUTTON_SIZE, g_i_BUTTON_DOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);
	}
		break;
	case WM_COMMAND:
	{

		HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
		CONST INT SIZE = 256;
		CHAR sz_display[SIZE]{};
		 CHAR sz_digit[2]{};
		 if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)	// цифры
		 {
			 sz_digit[0] = LOWORD(wParam) - IDC_BUTTON_0 + '0';
			 SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			 if (strlen(sz_display) == 1 && sz_display[0] == '0')
				 sz_display[0] = sz_digit[0];
			 else
			 {
				 strcat(sz_display, sz_digit);
			 }
			 SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		 }
		 else if (LOWORD(wParam) == IDC_BUTTON_POINT)									// .
		 {
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if(strchr(sz_display, '.'))break;
			strcat(sz_display, ".");
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);

		 }
		 else if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
		 {

			 SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			 g_calcState.operand1 = atof(sz_display);
			 INT operationIndex = LOWORD(wParam) - IDC_BUTTON_PLUS;
			 if (operationIndex >= 0 && operationIndex < 4)
			 {
				 g_calcState.operation = g_OPERATIONS[operationIndex][0];
			 }
			 SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0");				// Сбросить отображение
			 
		 }
		 else if (LOWORD(wParam) == IDC_BUTTON_BSP)										//<-
		 {
			 SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			 if (strlen(sz_display) > 1) sz_display[strlen(sz_display) - 1] = '\0';
			 else
				 strcpy(sz_display, "0");
			 SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		 }
		 else if (LOWORD(wParam) == IDC_BUTTON_CLR)										//cclr
		 {
			 SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0");	
			 g_calcState = { 0.0, 0.0, '\0'};
		 }
		 else if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		 {
			 SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			 g_calcState.operand2 = atof(sz_display);
			 DOUBLE result{ 0.0 };
			 switch (g_calcState.operation)
			 {
			 case'+':
				 result = g_calcState.operand1 + g_calcState.operand2;
				 break;
			 case'-':
				 result = g_calcState.operand1 - g_calcState.operand2;
				 break;
			 case'*':
				 result = g_calcState.operand1 * g_calcState.operand2;
				 break;
			 case'/':
				 if (g_calcState.operand2 != 0)
					 result = g_calcState.operand1 / g_calcState.operand2;
				 else
					 MessageBox(hwnd, "Division by zero!", "Error", MB_OK | MB_ICONERROR);
				 break;
			 default:
				 break;
			 }
			 sprintf(sz_display, "%g", result);
			 SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		 }
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}