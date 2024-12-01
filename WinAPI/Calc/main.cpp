#include<Windows.h>
#include"resource.h"


#define IDC_EDIT_DISPLAY 999
#define IDC_BUTTON_0 1000	
#define IDC_BUTTON_1 1001
#define IDC_BUTTON_2 1002
#define IDC_BUTTON_3 1003
#define IDC_BUTTON_4 1004
#define IDC_BUTTON_5 1005
#define IDC_BUTTON_6 1006
#define IDC_BUTTON_7 1007
#define IDC_BUTTON_8 1008
#define IDC_BUTTON_9 1009

#define IDC_BUTTON_ADD 1010			// +
#define IDC_BUTTON_SUB 1011			// -
#define IDC_BUTTON_MUL 1012			// *
#define IDC_BUTTON_DIV 1013			// /
#define IDC_BUTTON_EQ 1014			// =
#define IDC_BUTTON_CLEAR 1015		// clr
#define IDC_BUTTON_BACKSPACE 1016	// <-
#define IDC_BUTTON_DOT 1017			// ,

CONST CHAR g_sz_WINDOW_CLASS[] = "CALC_VPD_311";


CONST INT g_i_SCREEN_WIDTH = 400;	// дисплэй ширина
CONST INT g_i_SCREEN_HEIGHT = 44;	//дисплэй высота

CONST INT g_i_BUTTON_SIZE_WIDTH = 96;	//Размер кнопки в пикселах
CONST INT g_i_BUTTON_SIZE_HEIGHT = 60;	//Размер кнопки в пикселах
CONST INT g_i_INTERVAL = 5;		//Растояние между кнопками

CONST INT g_i_START_X = 10;
CONST INT g_i_START_Y = 10;


CONST INT g_i_BUTTON_START_X = g_i_START_X;
CONST INT g_i_BUTTON_START_Y = g_i_START_Y+g_i_SCREEN_HEIGHT+g_i_INTERVAL;

CONST INT g_i_CALCULATOR_WIDTH = g_i_SCREEN_WIDTH+ g_i_START_X *2;
CONST INT g_i_CALCULATOR_HEIGHT = g_i_SCREEN_HEIGHT+ g_i_START_Y*2+ (g_i_BUTTON_SIZE_HEIGHT + g_i_INTERVAL)*5;

INT CALLBACK  WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPrama);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1)Регистрация класса окна
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CALC));
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CALC));
	wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_ARROW));
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

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
	RECT rect = { 0, 0, g_i_CALCULATOR_WIDTH, g_i_CALCULATOR_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	
	INT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	INT screenHeight = GetSystemMetrics(SM_CYSCREEN);
	INT xPos = (screenWidth - (rect.right - rect.left)) / 2;
	INT yPos = (screenHeight - (rect.bottom - rect.top)) / 2;

	HWND hwnd = CreateWindowEx(
		NULL,
		g_sz_WINDOW_CLASS,
		g_sz_WINDOW_CLASS,
		//WS_OVERLAPPED| WS_MINIMIZEBOX| WS_CAPTION| WS_SYSMENU,
		WS_OVERLAPPEDWINDOW &~WS_THICKFRAME &~WS_MAXIMIZEBOX,
		xPos, yPos,
		rect.right - rect.left, rect.bottom - rect.top,
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
		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit", "0",
			WS_CHILD | WS_VISIBLE | WS_BORDER|ES_RIGHT,
			10, 10,
			g_i_SCREEN_WIDTH, g_i_SCREEN_HEIGHT,
			hwnd,
			(HMENU)1000,
			GetModuleHandle(NULL),
			NULL
		);
		HFONT hFont = CreateFont
		(
			38,								// Высота шрифта — 24.
			0,								// Ширина шрифта — 0 (по умолчанию, автоматически рассчитывается).
			0,								// Угол наклона текста (escapement и orientation) — 0.
			0,
			FW_MEDIUM,						// Толщина шрифта — FW_BOLD (жирный).
			FALSE, FALSE, FALSE,			// Флаги: курсив (FALSE), подчеркивание (FALSE), зачеркнутый текст (FALSE).
			DEFAULT_CHARSET,				// Кодовая страница символов — стандартная (DEFAULT_CHARSET).
			OUT_DEFAULT_PRECIS,				// Точность вывода — по умолчанию.
			CLIP_DEFAULT_PRECIS,			// Точность отсечения — по умолчанию.
			DEFAULT_QUALITY,				// Качество шрифта — по умолчанию.
			DEFAULT_PITCH | FF_SWISS,		// Шаг (по умолчанию) и семейство шрифтов (швейцарское, например Arial).
			"Arial"							// Имя шрифта — "Arial".
		);
		SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
		//
		// Создание кнопок:
		CONST CHAR* buttonLabels[5][4] = {
			{ "", "", "clr", "<-" },
			{ "7", "8", "9", "/" },
			{ "4", "5", "6", "*" },
			{ "1", "2", "3", "-" },
			{ "0", ".", "=", "+" }
		};

		INT buttonIds[5][4] = 
		{
			{ 0,0,IDC_BUTTON_CLEAR, IDC_BUTTON_BACKSPACE },
			{ IDC_BUTTON_7, IDC_BUTTON_8, IDC_BUTTON_9,  IDC_BUTTON_DIV },
			{ IDC_BUTTON_4, IDC_BUTTON_5, IDC_BUTTON_6,IDC_BUTTON_MUL  },
			{ IDC_BUTTON_1, IDC_BUTTON_2, IDC_BUTTON_3,IDC_BUTTON_SUB  },
			{ IDC_BUTTON_0,IDC_BUTTON_DOT , IDC_BUTTON_EQ, IDC_BUTTON_ADD}
		};

		for (int row = 0; row < 5; ++row)
		{
			for (int col = 0; col < 4; ++col)
			{
				if (strlen(buttonLabels[row][col]) > 0)
				{
					CreateWindowEx(
						NULL , "Button", buttonLabels[row][col],
						WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON| WS_BORDER,
						g_i_BUTTON_START_X + col * (g_i_BUTTON_SIZE_WIDTH + g_i_INTERVAL),
						g_i_BUTTON_START_Y + row * (g_i_BUTTON_SIZE_HEIGHT + g_i_INTERVAL),
						g_i_BUTTON_SIZE_WIDTH, g_i_BUTTON_SIZE_HEIGHT,
						hwnd,
						(HMENU)buttonIds[row][col],
						GetModuleHandle(NULL),
						NULL
					);
				}
			}
		}
		//
	} break;

	
		break;
	case WM_COMMAND:

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