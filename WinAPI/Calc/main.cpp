#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<float.h>
#include<Windows.h>
#include<string.h>
#include"resource.h"
#include"Dimensions.h"

struct g_calcState {
	DOUBLE a;
	DOUBLE b;
	WORD   operation;
	BOOL   input;
	BOOL   operation_input;
	BOOL equal_pressed;
}g_calcstate {DBL_MIN,DBL_MIN,0,false,false,false};

CONST CHAR g_sz_WINDOW_CLASS[] = "CALC_VPD_311";
CONST CHAR* g_OPERATIONS[] = { "+","-","*","/" };

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

VOID SetSkin(HWND hwnd, CONST CHAR skin[]);
HFONT SetCustomFont(HWND hwnd, CONST CHAR* fontName, INT fontSize, INT fonwWeight, BOOL addFontFromFile, CONST CHAR* fontPath);
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
		//CONST CHAR* customFontPatch = "FONT\\Digital-7.ttf";
		/*HFONT hFont = SetCustomFont
		(
			hwnd,
			"Digital-7",
			24,
			FW_BOLD,
			TRUE,
			customFontPatch
		);*/
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
		/*SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);*/

		CHAR sz_digit[2] = {};
		for (int i = 6; i >= 0; i -= 3)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = i + j+'1';
				CreateWindowEx
				(
					NULL, "Button", sz_digit,
					WS_CHILD | WS_VISIBLE | BS_BITMAP,
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
		HWND hButton_0=CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE|BS_BITMAP,
			BUTTON_SHIFT_X(0), BUTTON_SHIFT_Y(3),
			//g_i_BUTTON_START_X ,
			//g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		//HBITMAP bmpButton_0=
		//(HBITMAP) LoadImage(NULL, "ImageBMP\\ZERO.bmp", IMAGE_BITMAP, g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,LR_LOADFROMFILE);

		//SendMessage(hButton_0, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpButton_0);

		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_BITMAP,
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
				WS_CHILD | WS_VISIBLE| BS_BITMAP,
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
			WS_CHILD | WS_VISIBLE | BS_BITMAP,
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
			WS_CHILD | WS_VISIBLE | BS_BITMAP,
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
			WS_CHILD | WS_VISIBLE | BS_BITMAP,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(2),
			g_i_BUTTON_SIZE, g_i_BUTTON_DOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);
		//SetSkin(hwnd, "square_blue");
		SetSkin(hwnd, "metal_mistral");
	}
		break;
	case WM_COMMAND:
	{
		static DOUBLE a { DBL_MIN};
		static DOUBLE b { DBL_MIN};
		static WORD	operation {0};
		static BOOL input {FALSE };
		static BOOL operation_input {FALSE};
		static BOOL equal_pressed {FALSE};

		SetFocus(hwnd);

		HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
		CONST INT SIZE = 256;
		CHAR sz_display[SIZE]{};
		 CHAR sz_digit[2]{};
		 if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)	// =
		 {
			 if (operation_input||equal_pressed)
			 {
				SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"");
				operation_input =equal_pressed= false;
			 }
			 sz_digit[0] = LOWORD(wParam) - IDC_BUTTON_0 + '0';
			 SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			 if (strlen(sz_display) == 1 && sz_display[0] == '0')
				 sz_display[0] = sz_digit[0];
			 else
			 {
				 strcat(sz_display, sz_digit);
			 }
			 SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			 input = TRUE;

		 }
		 if (LOWORD(wParam) == IDC_BUTTON_POINT)									// .
		 {
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if(strchr(sz_display, '.'))break;
			strcat(sz_display, ".");
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);

		 }
		 if (LOWORD(wParam) == IDC_BUTTON_BSP)										//<-
		 {
			 SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);

			 if (strlen(sz_display) > 1) sz_display[strlen(sz_display) - 1] = 0;
			 else
				 sz_display[0] = '0';
			 SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			 ///
			 INT length = SendMessage(hEditDisplay, WM_GETTEXTLENGTH, 0, 0);
			 SendMessage(hEditDisplay, EM_SETSEL, length, length);
			 ////
		 }
		 if (LOWORD(wParam) == IDC_BUTTON_CLR)										//cclr
		 {
			 a = b = DBL_MIN;
			 operation = 0;
			 input = operation_input = FALSE;
			 SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0");
		 }
		 /////////////////////////////////////////////////////////////////////////
		 if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
		 {
			 SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			 if (input&&a == DBL_MIN)a = atof(sz_display);
			 //input = FALSE;
			 if (operation&&input)SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_EQUAL), 0);
			 operation = LOWORD(wParam);
			 operation_input = TRUE;
			 equal_pressed = FALSE;
		 }
		 if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		 {

			 SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			 if (input)b = atof(sz_display);
			 input = FALSE;
			 switch (operation)
			 {
			 case IDC_BUTTON_PLUS:	a += b; break;
			 case IDC_BUTTON_MINUS:	a -= b; break;
			 case IDC_BUTTON_ASTER:	a *= b; break;
			 case IDC_BUTTON_SLASH:	a /= b; break;
			 }
			 operation_input = FALSE;
			 equal_pressed = TRUE;
			 sprintf(sz_display, "%g", a);
			 SendMessage(hEditDisplay, WM_SETTEXT, 0, LPARAM(sz_display));
		 }
	}
		break;
	case WM_KEYDOWN:
	{
		if (GetKeyState(VK_SHIFT) < 0 && wParam == 0x38)
		{
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, 0);
		}
		else if (wParam >= '0' && wParam <= '9')
		{
			//SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - '0' + IDC_BUTTON_0), 0);
			SendMessage(GetDlgItem(hwnd, wParam - '0' + IDC_BUTTON_0), BM_SETSTATE, TRUE, 0);
		}
		else if (wParam >= 0x60 && wParam <= 0x69)
		{
			//SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - 0x60 + IDC_BUTTON_0), 0);
			SendMessage(GetDlgItem(hwnd, wParam-0x60 + IDC_BUTTON_0), BM_SETSTATE, TRUE, 0);
		}
		switch (wParam)
		{
		case VK_OEM_PERIOD:case VK_DECIMAL: 
			//SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_POINT), 0); 
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_POINT), BM_SETSTATE, TRUE, 0);
			break;
		case VK_BACK: 
			//SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_BSP), 0); 
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_BSP), BM_SETSTATE, TRUE, 0);
			break;
		case VK_ESCAPE:
			//SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_CLR), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_CLR), BM_SETSTATE, TRUE, 0);
			break;

		case VK_MULTIPLY:
			//SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_ASTER), 0); 
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, 0);

			break;
		case VK_OEM_PLUS:case VK_ADD:		
			//SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_PLUS), 0); 
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, TRUE, 0);
			break;
		case VK_OEM_MINUS:case VK_SUBTRACT: 
			//SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_MINUS), 0); 
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_MINUS), BM_SETSTATE, TRUE, 0);
			break;
		case VK_DIVIDE:case VK_OEM_2:
			//SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_SLASH), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_SLASH), BM_SETSTATE, TRUE, 0);
			break;
		case VK_RETURN:
			//SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_EQUAL), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETSTATE, TRUE, 0);
			break;
		}
		break;
	}
	case WM_KEYUP:
	{
		if (GetKeyState(VK_SHIFT) < 0 && wParam == 0x38)
		{
			SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, FALSE, 0);
		}
		else if (wParam >= '0' && wParam <= '9')
		{
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - '0' + IDC_BUTTON_0), 0);
			SendMessage(GetDlgItem(hwnd, wParam - '0' + IDC_BUTTON_0), BM_SETSTATE, FALSE, 0);
		}
		else if (wParam >= 0x60 && wParam <= 0x69)
		{
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - 0x60 + IDC_BUTTON_0), 0);
			SendMessage(GetDlgItem(hwnd, wParam - 0x60 + IDC_BUTTON_0), BM_SETSTATE, FALSE, 0);
		}
		switch (wParam)
		{
		case VK_OEM_PERIOD:case VK_DECIMAL:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_POINT), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_POINT), BM_SETSTATE, FALSE, 0);
			break;
		case VK_BACK:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_BSP), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_BSP), BM_SETSTATE, FALSE, 0);
			
			break;
		case VK_ESCAPE:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_CLR), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_CLR), BM_SETSTATE, FALSE, 0);
			break;

		case VK_MULTIPLY:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_ASTER), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, FALSE, 0);

			break;
		case VK_OEM_PLUS:case VK_ADD:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_PLUS), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, FALSE, 0);
			break;
		case VK_OEM_MINUS:case VK_SUBTRACT:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_MINUS), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_MINUS), BM_SETSTATE, FALSE, 0);
			break;
		case VK_DIVIDE:case VK_OEM_2:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_SLASH), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_SLASH), BM_SETSTATE, FALSE, 0);
			break;
		case VK_RETURN:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_EQUAL), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETSTATE, FALSE, 0);
			break;
		}
		
	}
	break;
		/////////
		/*case WM_CONTEXTMENU:
		{
			HMENU hMainMenu{ CreatePopupMenu() };
			HMENU hSubMenuSkins{ CreatePopupMenu() };
			HMENU hSubMenuFonts{ CreatePopupMenu() };
			AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenuSkins, "Skins");
			AppendMenu(hSubMenuSkins, MF_STRING, CM_SQUARE_BLUE, "Square Blue");
			AppendMenu(hSubMenuSkins, MF_STRING, CM_METAL_MISTRAL, "metal_mistral");

			AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenuFonts, "Fonts");
			AppendMenu(hSubMenuFonts, MF_STRING, CM_FONT_DIGITAL7, "Digital-7");
			AppendMenu(hSubMenuFonts, MF_STRING, CM_FONT_ARIAL, "Arial");

			POINT pt;
			if (GetCursorPos(&pt))
			{
				INT command = TrackPopupMenuEx(hMainMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN | TPM_RETURNCMD, pt.x, pt.y, hwnd, NULL);
				switch (command)
				{
				case CM_SQUARE_BLUE:
					SetSkin(hwnd, "square_blue");
					break;
				case CM_METAL_MISTRAL:
					SetSkin(hwnd, "metal_mistral");
					break;
				case CM_FONT_DIGITAL7:
				{
					HFONT hFont = SetCustomFont(hwnd, "Digital-7", 24, FW_BOLD, TRUE, "FONT\\Digital-7.ttf");
					HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
					SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
				}
				break;
				case CM_FONT_ARIAL:
				{
					HFONT hFont = SetCustomFont(hwnd, "Arial", 24, FW_NORMAL, FALSE,NULL);
					HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
					SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
				}
				}
			}
			else
				MessageBox(NULL, "Failed to get cursor position.", "Error", MB_OK | MB_ICONERROR);
		}
		break;
		*/
	case WM_CONTEXTMENU:
	{

		//1) Создаем всплывающее меню
		HMENU hMenu{ CreatePopupMenu() };
		//2) Добавляем пункты в созданий меню
		InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING, IDR_EXIT, "Exit");
		InsertMenu(hMenu, 0, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);

		InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING, IDR_METAL_MISTRAL, "Meatal mistral");
		InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING, IDR_SQUARE_BLUE, "Square blue");
		//3) Использование контекстного меню
		//INT command{ TrackPopupMenu(hMenu,NULL,0,0,0,hwnd,NULL) };
		//switch (command)
		
		switch (TrackPopupMenu(hMenu, TPM_RETURNCMD|TPM_RIGHTALIGN | TPM_BOTTOMALIGN, LOWORD(lParam), HIWORD(lParam), 0, hwnd, NULL))
		{
		case IDR_SQUARE_BLUE:SetSkin(hwnd, "square_blue"); break;
		case IDR_METAL_MISTRAL:SetSkin(hwnd, "metal_mistral"); break;
		case IDR_EXIT: SendMessage(hwnd, WM_CLOSE, 0, 0); break;
		}
		DestroyMenu(hMenu);
	}
		break;
	case WM_DESTROY:
		 RemoveFontResourceEx("FONT\\Digital7.ttf", FR_PRIVATE, NULL);
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
CONST CHAR* g_BUTTONS[]{
	"button_0.bmp",
	"button_1.bmp",
	"button_2.bmp",
	"button_3.bmp",
	"button_4.bmp",
	"button_5.bmp",
	"button_6.bmp",
	"button_7.bmp",
	"button_8.bmp",
	"button_9.bmp",
	"button_point.bmp",
	"button_plus.bmp",
	"button_minus.bmp",
	"button_aster.bmp",
	"button_slash.bmp",
	"button_bsp.bmp",
	"button_clr.bmp",
	"button_equal.bmp",
};
VOID SetSkin(HWND hwnd, CONST CHAR skin[])
{
	CHAR sz_filename[MAX_PATH]{};
	for (int i = IDC_BUTTON_0; i <= IDC_BUTTON_EQUAL; ++i)
	{
		HWND hButton{ GetDlgItem(hwnd,i) };
		sprintf(sz_filename, "ImageBMP\\%s\\%s", skin, g_BUTTONS[i-IDC_BUTTON_0]);
		HBITMAP bmpButton
		{ (HBITMAP)LoadImage
		(	NULL,
			sz_filename,
			IMAGE_BITMAP,
			i == IDC_BUTTON_0 ? g_i_BUTTON_DOUBLE_SIZE : g_i_BUTTON_SIZE,
			i == IDC_BUTTON_EQUAL ? g_i_BUTTON_DOUBLE_SIZE : g_i_BUTTON_SIZE,
			LR_LOADFROMFILE
			) 
		};
		SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpButton);
	}
}
/*
VOID SetSkin(HWND hwnd, CONST CHAR skin[])
{
	CHAR sz_file[MAX_PATH]{};
	HANDLE hImage = NULL;

	for (int i = IDC_BUTTON_0; i <= IDC_BUTTON_9; ++i)
	{
		HWND hButton = GetDlgItem(hwnd, i);
		INT buttonWidth;
		if(i==IDC_BUTTON_0) buttonWidth = g_i_BUTTON_DOUBLE_SIZE;
		else				buttonWidth = g_i_BUTTON_SIZE;
		sprintf(sz_file, "ImageBMP\\%s\\button_%i.bmp", skin, i - IDC_BUTTON_0);
		hImage = LoadImage
		(
			GetModuleHandle(NULL),
			sz_file,
			IMAGE_BITMAP,
			buttonWidth,
			g_i_BUTTON_SIZE,
			LR_LOADFROMFILE
		);
		if (hImage && hButton)
		{
			SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
		}
		else
		{
			sprintf(sz_file, "Failed to load image: %s", sz_file);
			MessageBox(hwnd, sz_file, "Error", MB_OK | MB_ICONERROR);
		}
	}
	for (int i = IDC_BUTTON_PLUS; i <= IDC_BUTTON_SLASH; ++i)
	{
		HWND hButton = GetDlgItem(hwnd, i);
		CONST CHAR* operationName = NULL;
		switch (i)
		{
		case IDC_BUTTON_PLUS: operationName = "plus"; break;
		case IDC_BUTTON_MINUS: operationName = "minus"; break;
		case IDC_BUTTON_ASTER: operationName = "aster"; break;
		case IDC_BUTTON_SLASH: operationName = "slash"; break;
		}
		if (operationName)
		{
			sprintf(sz_file, "ImageBMP\\%s\\button_%s.bmp", skin, operationName);
			hImage = LoadImage
			(
				GetModuleHandle(NULL),
				sz_file,
				IMAGE_BITMAP,
				g_i_BUTTON_SIZE,
				g_i_BUTTON_SIZE,
				LR_LOADFROMFILE
			);
			if (hImage && hButton)
			{
				SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
			}
			else
			{
				sprintf(sz_file, "Failed to load image: %s", sz_file);
				MessageBox(hwnd, sz_file, "Error", MB_OK | MB_ICONERROR);
			}

		}
	}
	struct
	{
		WORD id;
		CONST CHAR* name;
		INT width;
	}
	specialButtons[]=
	{
		{IDC_BUTTON_EQUAL,	"equal", g_i_BUTTON_DOUBLE_SIZE},
		{IDC_BUTTON_CLR,	"clr", g_i_BUTTON_SIZE},
		{IDC_BUTTON_BSP,	"bsp",	 g_i_BUTTON_SIZE }
	};
	for (int i = 0; i < sizeof(specialButtons) / sizeof(specialButtons[0]); ++i)
	{
		HWND hButton= GetDlgItem(hwnd, specialButtons[i].id);
		sprintf(sz_file, "ImageBMP\\%s\\button_%s.bmp", skin, specialButtons[i].name);
		hImage = LoadImage
		(
			GetModuleHandle(NULL),
			sz_file,
			IMAGE_BITMAP,
			g_i_BUTTON_SIZE,
			specialButtons[i].width,
			LR_LOADFROMFILE
		);
		if (hImage && hButton)
		{
			SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
		}
		else
		{
			sprintf(sz_file, "Failed to load image: %s", sz_file);
			MessageBox(hwnd, sz_file, "Error", MB_OK | MB_ICONERROR);
		}
	}
	HWND hButton = GetDlgItem(hwnd, IDC_BUTTON_POINT);
	sprintf(sz_file, "ImageBMP\\%s\\button_point.bmp", skin);
	HBITMAP bmpButton_point=
		(HBITMAP) LoadImage
		(
			GetModuleHandle(NULL),
			sz_file,
			IMAGE_BITMAP,
			g_i_BUTTON_SIZE,
			g_i_BUTTON_SIZE,
			LR_LOADFROMFILE);
		if (bmpButton_point)
		SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpButton_point);
		else
		{
			sprintf(sz_file, "Failed to load image: %s", sz_file);
			MessageBox(hwnd, sz_file, "Error", MB_OK | MB_ICONERROR);
		}
}
*/
HFONT SetCustomFont(HWND hwnd, CONST CHAR* fontName, INT fontSize, INT fontWeight, BOOL addFontFromFile, CONST CHAR* fontPath = NULL)
{
	if (addFontFromFile && fontPath)
	{
		if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) == 0)
		{
			MessageBox(hwnd, "Failed to add font from file.", "Error", MB_OK | MB_ICONERROR);
			return (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		}
	}
	HFONT hFont = CreateFont
	(
		fontSize,              // Высота шрифта
		0,                     // Ширина шрифта (авто)
		0,                     // Угол наклона текста (в 0.1 градусах)
		0,                     // Угол наклона шрифта
		fontWeight,            // Вес шрифта (FW_BOLD, FW_NORMAL и т.д.)
		FALSE,                 // Курсив
		FALSE,                 // Подчёркивание
		FALSE,                 // Зачёркивание
		DEFAULT_CHARSET,       // Набор символов
		OUT_DEFAULT_PRECIS,    // Точность вывода
		CLIP_DEFAULT_PRECIS,   // Точность отсечения
		DEFAULT_QUALITY,       // Качество шрифта
		DEFAULT_PITCH | FF_SWISS, // Тип шрифта
		fontName               // Имя шрифта
	);
	if (!hFont)
	{
		MessageBox(hwnd, "Failed to create font.", "Error", MB_OK | MB_ICONERROR);
		return (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	}
	return hFont;
}