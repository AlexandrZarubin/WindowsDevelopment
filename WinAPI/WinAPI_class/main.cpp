#include<windows.h>
#include"resource.h"
#include<string>
// hInstance Ч это дескриптор текущего экземпл€ра программы.
// hPrevInstance Ч в 32-битных верси€х Windows не используетс€ (всегда NULL), но раньше указывал на предыдущий экземпл€р программы.
// LPSTR -longPointer to string (”казатель на строку наподобие const char*)
// lpCmdLine Ч строка команд, переданна€ программе (без имени программы). командна€ строка запуска приложенеи€ 
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


//HWND hwnd: ƒескриптор (идентификатор) окна диалога. Ётот параметр используетс€ дл€ управлени€ и изменени€ свойств окна.

//UINT uMsg:  од сообщени€, отправленного окну. Ёто может быть любое сообщение, такое как WM_INITDIALOG (инициализаци€ диалогового окна),
//  WM_COMMAND (событие, св€занное с элементами управлени€, например кнопками), WM_CLOSE (закрытие окна) и другие.

//WPARAM wParam: ƒополнительна€ информаци€, завис€ща€ от конкретного сообщени€.
//Ќапример, если сообщение Ч это WM_COMMAND, wParam будет содержать идентификатор элемента управлени€ (например, кнопки).

//LPARAM lParam: ƒополнительна€ информаци€, также завис€ща€ от конкретного сообщени€.
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
		/*case IDC_BUTTON_COPY:
		{
			char buffer[256];
			GetDlgItemText(hwnd, IDC_EDIT1, buffer, sizeof(buffer));
			SetDlgItemText(hwnd, IDC_EDIT2, buffer);
		}*/
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);

		}
		break;
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
	//
}
