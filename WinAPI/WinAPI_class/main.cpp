#include<windows.h>
#include"resource.h"
#include<string>
// hInstance � ��� ���������� �������� ���������� ���������.
// hPrevInstance � � 32-������ ������� Windows �� ������������ (������ NULL), �� ������ �������� �� ���������� ��������� ���������.
// LPSTR -longPointer to string (��������� �� ������ ��������� const char*)
// lpCmdLine � ������ ������, ���������� ��������� (��� ����� ���������). ��������� ������ ������� ����������� 
// nCmdShow � ���������, ��� ����� ���������� ���� (��������, ���������, ����������� � �.�.).

//#define MESSAGE_BOX

BOOL CALLBACK DlgProc(HWND hwnd, UINT Umsg, WPARAM wParam, LPARAM lPAram);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
#ifdef MESSAGE_BOX
	MessageBox(
		NULL,
		"Hello WinAPI!\n ��� ���� ���������",
		"info/���������",
		MB_YESNOCANCEL | MB_ICONQUESTION | MB_HELP | MB_DEFBUTTON2 | MB_SYSTEMMODAL
	);
#endif // MESSAGE_BOX
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}


//HWND hwnd: ���������� (�������������) ���� �������. ���� �������� ������������ ��� ���������� � ��������� ������� ����.

//UINT uMsg: ��� ���������, ������������� ����. ��� ����� ���� ����� ���������, ����� ��� WM_INITDIALOG (������������� ����������� ����),
//  WM_COMMAND (�������, ��������� � ���������� ����������, �������� ��������), WM_CLOSE (�������� ����) � ������.

//WPARAM wParam: �������������� ����������, ��������� �� ����������� ���������.
//��������, ���� ��������� � ��� WM_COMMAND, wParam ����� ��������� ������������� �������� ���������� (��������, ������).

//LPARAM lParam: �������������� ����������, ����� ��������� �� ����������� ���������.
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
		case IDOK:MessageBox(hwnd, "���� ������ ������ ��", "info", MB_OK | MB_ICONINFORMATION); break;
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
