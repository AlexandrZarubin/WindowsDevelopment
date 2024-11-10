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
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
		for (int i = 0; i < sizeof(g_VALUES) / sizeof(g_VALUES[0]); ++i)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)g_VALUES[i]);	// ��������� ������ � ������
		}
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_ADD:
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD_ITEM), hwnd, DlgProcAddItem, 0);
			break;

		case IDOK:
		{
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
			//MessageBox(hwnd, sz_buffer, "Info", MB_OK|MB_ICONINFORMATION);
			/*
			CHAR sz_message[SIZE]{};
			sprintf(sz_message, "�� ������� ����� N%i �� ��������� \"%s\"", i, sz_buffer);
			MessageBox(hwnd, sz_message, "Selection value", MB_OK | MB_ICONINFORMATION);
			*/
			std::string sz_message = "�� ������� ����� N" + std::to_string(i) + " �� ��������� \"" + sz_buffer + "\"";
			MessageBox(hwnd, sz_message.c_str(), "Selection value", MB_OK | MB_ICONINFORMATION);
		}
			break;
			case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd,0);break;
		//EndDialog(hwnd, IDCANCEL);break;

	}
	return FALSE;
}
INT_PTR CALLBACK DlgProcAddItem(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			//1)������ ����� �� EditControl
			CONST INT SIZE = 256;
			CHAR sz_buffer[256]{};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_ADD_ITEM);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			//2) �������� ������������ ����
			HWND hParent = GetParent(hwnd);
			//3)�������� ���������� ListBox
			HWND hListBox = GetDlgItem(hParent, IDC_LIST);
			//4)��������� ����� � ListBox:
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
		}
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}