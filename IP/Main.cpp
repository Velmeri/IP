//Main.cpp
#include <iostream>
#include "Socket.h"

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

#pragma once

#include "resource1.h"
#include <windows.H>
#include <windowsX.h>
#include <commctrl.h>

#pragma comment(lib,"comctl32")
#pragma comment(lib, "winmm.lib")

HINSTANCE hInst;

BOOL CALLBACK dlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        case IDCANCEL:
            EndDialog(hWnd, 0);
            return TRUE;
        }
    }
    return FALSE;
}
DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SERVER), NULL, dlgProc);
