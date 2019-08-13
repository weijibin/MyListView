#include "stdafx.h"
#include "Resource.h"
#include "Dialogs.h"
#include <commctrl.h>
#include <windowsx.h>

//对话框窗口过程的模板
/*
BOOL CALLBACK XxxDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch(wmId)
		{
		case IDCANCEL:
			EndDialog(hDlg, wmId);
			return TRUE;
		case IDOK:
			EndDialog(hDlg, wmId);
			return TRUE;
		}
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hDlg, &ps);
			EndPaint(hDlg, &ps);
		}
		break;

	case WM_DESTROY:
		return TRUE;
	}
	return FALSE;
}
*/


//设置对话框控件为焦点
void FocusDlgItem(HWND hDlg, int ctlId)
{
	HWND hwndControl = GetDlgItem(hDlg, ctlId);
	SendMessage(hDlg, WM_NEXTDLGCTL, (WPARAM)hwndControl, TRUE);
}

BOOL CALLBACK CtrlPanelDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (message)
	{
	case WM_INITDIALOG:
		{
			HWND hComboBox = GetDlgItem(hDlg, IDC_CB_FLOATTYPE);
			ComboBox_AddString(hComboBox, _T("float"));
			ComboBox_AddString(hComboBox, _T("double"));
			ComboBox_SetCurSel(hComboBox, 1); //默认选择double

			CheckDlgButton(hDlg, IDC_CHECK_MULTITHREAD, BST_CHECKED);
			int nProcessorCount = (int)lParam;

			if(nProcessorCount <= 1)
				nProcessorCount = 2;
			if(nProcessorCount > 16)
				nProcessorCount = 16;

			SetDlgItemInt(hDlg, IDC_THREADCOUNT, nProcessorCount, TRUE);
			SetDlgItemText(hDlg, IDC_SIGMA, _T("3.5"));

			HWND hUpdown = GetDlgItem(hDlg, IDC_SPIN1);
			UpDown_SetBuddy(hUpdown, GetDlgItem(hDlg, IDC_THREADCOUNT));
			UpDown_SetBase(hUpdown, 10);
			UpDown_SetRange32(hUpdown, 2, 16);
			UpDown_SetPos(hUpdown, nProcessorCount);
		}
		return TRUE;

	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch(wmId)
		{
		case IDCANCEL:
			EndDialog(hDlg, wmId);
			return TRUE;
		case IDOK:
			EndDialog(hDlg, wmId);
			return TRUE;

		case IDC_CHECK_MULTITHREAD:
			{
				BOOL bEnabled = (IsDlgButtonChecked(hDlg, wmId) == BST_CHECKED);
				EnableWindow(GetDlgItem(hDlg, IDC_THREADCOUNT), bEnabled);
				EnableWindow(GetDlgItem(hDlg, IDC_SPIN1), bEnabled);
			}
			return TRUE;

		case IDM_GAUSSBLUR:
			//将此消息转发到父窗口
			SendMessage(GetParent(hDlg), message, wParam, lParam);
			return TRUE;
		}
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hDlg, &ps);
			EndPaint(hDlg, &ps);
		}
		break;

	case WM_DESTROY:
		return TRUE;
	}
	return FALSE;
}