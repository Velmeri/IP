//Main.cpp
#include <iostream>
#include "Socket.h"
#include "resource1.h"
#include <windows.H>
#include <windowsX.h>
#include <commctrl.h>

using namespace std;

enum comands
{
	InvalidСommand,
	GetPrice,
	HELP,
	END
};

int GetComand(string comand) {
	if ("GetPrice" == comand) return GetPrice;
	if ("help" == comand) return HELP;
	if ("end" == comand) return END;
	return InvalidСommand;
}

#pragma comment(lib,"comctl32")
#pragma comment(lib, "winmm.lib")

HINSTANCE hInst;
Socket Server;
Socket User;

HWND EDIT1;

BOOL CALLBACK dlgProc1(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg)
    {
    case WM_COMMAND:
        switch (msg)
        {
        case WM_INITDIALOG:
        {
            EDIT1 = GetWindow(hWnd, IDC_EDIT3);
        }
        break;
        case WM_CLOSE:
        {
            EndDialog(hWnd, 0);
        }
        break;
        case WM_COMMAND:
        {
        case IDC_SEND:
            WCHAR buf[1024];
            GetDlgItemText(hWnd, IDC_EDIT3, buf, 1024);
            char I_hate_winAPI[1024];
            for (int i = 0; i < 1024; i++)
                I_hate_winAPI[i] = buf[i];
            Server.SendData(I_hate_winAPI);
        }
        break;
        case IDC_END:
        {
            Server.SendData("end");
            Server.CloseConnection();
        }
        }

    }
    return FALSE;
}

BOOL CALLBACK dlgProc1(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg)
    {
    case WM_COMMAND:
        switch (msg)
        {
        case WM_INITDIALOG:
        {
            EDIT1 = GetWindow(hWnd, IDC_EDIT3);
        }
        break;
        case WM_CLOSE:
        {
            EndDialog(hWnd, 0);
        }
        break;
        case WM_COMMAND:
        {
        case IDC_SEND:
            WCHAR buf[1024];
            GetDlgItemText(hWnd, IDC_EDIT3, buf, 1024);
            char I_hate_winAPI[1024];
            for (int i = 0; i < 1024; i++)
                I_hate_winAPI[i] = buf[i];
            User.SendData(I_hate_winAPI);
        }
        break;
        case IDC_BREAK:
            User.SendData("end");
        }
    }
    return FALSE;
}

int main() {
    unsigned short res;
    cin >> res;
    switch (res)
    {
    case 1:
    {
        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SERVER), NULL, dlgProc1);
    }
    break;
    case 2:
    {
        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SERVER), NULL, dlgProc2);
    }
    break;

    }

}