#include<windows.h>
#include"resource.h"
// hInstance Ч это дескриптор текущего экземпл€ра программы.
// hPrevInstance Ч в 32-битных верси€х Windows не используетс€ (всегда NULL), но раньше указывал на предыдущий экземпл€р программы.
// lpCmdLine Ч строка команд, переданна€ программе (без имени программы).
// nCmdShow Ч указывает, как нужно отображать окно (например, свернутое, развернутое и т.д.).

//#define MESSAGE_BOX

BOOL CALLBACK DlgProc(HWND hwnd, UINT Umsg, WPARAM wParam, LPARAM lPAram);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
#ifdef MESSAGE_BOX
	MessageBox(
		NULL,
		"Hello WinAPI!\n Ёто окно сообщени€",
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
		case IDOK:MessageBox(hwnd, "Ѕыла нажата кнопка ќ ", "info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		//EndDialog(hwnd, IDCANCEL);
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;

}
