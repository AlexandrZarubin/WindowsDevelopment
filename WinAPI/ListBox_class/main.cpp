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
		// ��������� ������ �� ��������
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		// ������������� ������ ��� ���� �������
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		// �������� ���������� ListBox
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
		// ��������� ListBox ���������� ���������� �� �������
		for (int i = 0; i < sizeof(g_VALUES) / sizeof(g_VALUES[0]); ++i)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)g_VALUES[i]);	// ��������� ������ � ������
		}
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_ADD:	// ��������� ������� ������ "��������"
			// ��������� ������ ���������� ������ ��������
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD_ITEM), hwnd, DlgProcAddItem, (LPARAM)LB_ERR);
			break;
		case IDC_BUTTON_REMOVE:// ��������� ������� ������ "�������"
		{
			// �������� ���������� ListBox
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
			
			// �������� ������ ���������� ��������
			if((SendMessage(hListBox, LB_GETCURSEL, 0, 0))!=LB_ERR)
				SendMessage(hListBox, LB_DELETESTRING, SendMessage(hListBox, LB_GETCURSEL, 0, 0), 0);	// ������� ��������� �������
			else
				MessageBox(hwnd, "�������� ������� ��� ��������.", "������", MB_OK | MB_ICONERROR);		// ��������� �� ������
		}
		break;
		case IDOK:
		{
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST);			// �������� ���������� ListBox
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};								// ����� ��� �������� ������ ��������
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);	// �������� ������ ���������� ��������
			if (i != LB_ERR)
			{
			SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);	// �������� ����� ���������� ��������

			/*
			//MessageBox(hwnd, sz_buffer, "Info", MB_OK|MB_ICONINFORMATION);
			CHAR sz_message[SIZE]{};
			sprintf(sz_message, "�� ������� ����� N%i �� ��������� \"%s\"", i, sz_buffer);
			MessageBox(hwnd, sz_message, "Selection value", MB_OK | MB_ICONINFORMATION);
			*/

			// ������� ��������� ��� ����������� ���������� � ��������� ��������
			std::string sz_message = "�� ������� ����� N" + std::to_string(i) + " �� ��������� \"" + sz_buffer + "\"";
			MessageBox(hwnd, sz_message.c_str(), "Selection value", MB_OK | MB_ICONINFORMATION);	// ���������� ���������
			}
			else
				MessageBox(hwnd, "�������� �������.", "������", MB_OK | MB_ICONERROR);				// ��������� �� ������, ���� ������ �� �������
		}
			break;
			case IDCANCEL: EndDialog(hwnd, 0); break;// ��������� ������
	case IDC_LIST:								// ��������� ����������� �� ListBox
		{
			if (HIWORD(wParam) == LBN_DBLCLK)	// ��������� �������� ������ �� �������� ������
			{
				HWND hListBox = GetDlgItem(hwnd, IDC_LIST);				// �������� ���������� ListBox
				INT index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);// �������� ������ ���������� ��������
				if (index != LB_ERR)
				{
					// ��������� ������ �������������� �������� (�������� ������ �������� ��� lParam)
					DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD_ITEM), hwnd, DlgProcAddItem, (LPARAM)index);
				}
			}
		}
			break;
		}
		break;
	case WM_CLOSE:// ��������� �������� ������� (��������, ������� �� �������)
		EndDialog(hwnd,0);break;
		//EndDialog(hwnd, IDCANCEL);break;

	}
	return FALSE;// ���������� FALSE, ����� �������, ��� ��������� �� ���� ��������� ����������
}
INT_PTR CALLBACK DlgProcAddItem(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{

		INT editIndex = (INT)lParam;								// �������� ������ �������������� ��������
		if (editIndex != LB_ERR)									// ���� ������������� ������������ ������
		{	
			HWND hParent = GetParent(hwnd);							// �������� ���������� ������������� ����
			HWND hListBox = GetDlgItem(hParent, IDC_LIST);			// �������� ���������� ListBox

			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage(hListBox, LB_GETTEXT, editIndex, (LPARAM)sz_buffer);	// �������� ����� �������������� ��������

			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_ADD_ITEM);					// �������� ���������� Edit Control
			SetWindowText(hEdit, sz_buffer);									// ������������� ����� � Edit Control
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)lParam);				// ��������� ������ �������������� ��������
		
		//HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_ADD_ITEM);
		//SetFocus(hEdit);
		SetFocus(GetDlgItem(hwnd, IDC_EDIT_ADD_ITEM));							// ������������� ����� �� ���� �����
		return FALSE;															// ���������� FALSE, ��� ��� ����� ��� ����������
	}
		//break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			//1)������ ����� �� EditControl
			CONST INT SIZE = 256;
			CHAR sz_buffer[256]{};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_ADD_ITEM);					// �������� ���������� Edit Control
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);			// ������ ����� �� Edit Control
			//2) �������� ������������ ����
			HWND hParent = GetParent(hwnd);										// �������� ���������� ������������� ����
			//3)�������� ���������� ListBox
			HWND hListBox = GetDlgItem(hParent, IDC_LIST);						// �������� ���������� ListBox
			//4)��������� ����� � ListBox:
			INT editIndex = (INT)GetWindowLongPtr(hwnd, GWLP_USERDATA);			// �������� ������ �������������� ��������
			INT foundIndex = SendMessage(hListBox, LB_FINDSTRINGEXACT, -1, (LPARAM)sz_buffer);	// ��������� �� ���������
			if (foundIndex != LB_ERR && foundIndex != editIndex)		// ���� ����� ������� ��� ���������� � ��� �� ������� �������
			{
				MessageBox(hwnd, "����� �������� ��� ���������� � ������.", "������", MB_OK | MB_ICONERROR);
				return TRUE;											// ��������� ���������
			}
			if (editIndex != LB_ERR)									// ���� ����������� ������������ �������
			{
				SendMessage(hListBox, LB_DELETESTRING, editIndex, 0);					// ������� ������ �������
				SendMessage(hListBox, LB_INSERTSTRING, editIndex, (LPARAM)sz_buffer);	// ��������� ����� ����� �� �� �� �����
			}
			else															// ���� ��������� ����� �������//
			{
				SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)sz_buffer);	// ��������� ����� ������� � ����� ������
			}
		}
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}