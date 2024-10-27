#include<windows.h>
#include"resource.h"
// hInstance — это дескриптор текущего экземпляра программы.
// hPrevInstance — в 32-битных версиях Windows не используется (всегда NULL), но раньше указывал на предыдущий экземпляр программы.
// lpCmdLine — строка команд, переданная программе (без имени программы).
// nCmdShow — указывает, как нужно отображать окно (например, свернутое, развернутое и т.д.).

//#define MESSAGE_BOX

BOOL CALLBACK DlgProc(HWND hwnd, UINT Umsg, WPARAM wParam, LPARAM lPAram);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
#ifdef MESSAGE_BOX
	MessageBox(
		NULL,
		"Hello WinAPI!\n Это окно сообщения",
		"info/заголовок",
		MB_YESNOCANCEL | MB_ICONQUESTION | MB_HELP | MB_DEFBUTTON2 | MB_SYSTEMMODAL
	);
#endif // MESSAGE_BOX
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPAram)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:MessageBox(hwnd, "Была нажата кнопка ОК", "info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		//EndDialog(hwnd, IDCANCEL);
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
	//
}
