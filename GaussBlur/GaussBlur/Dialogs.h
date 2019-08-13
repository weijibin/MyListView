#pragma once

//定义对话框窗口过程

//
// TextBox
//

//选中全部文本
#define TextBox_SelectAll(hDlg, ctlId) \
	SendDlgItemMessage(hDlg, ctlId, EM_SETSEL, 0, -1)

#define TextBox_UnselectAll(hDlg, ctlId) \
	SendDlgItemMessage(hDlg, ctlId, EM_SETSEL, -1, 0)

//设置最多可输入的单字节字符数
#define TextBox_SetMaxLength(hDlg, ctlId, nLength) \
	SendDlgItemMessage(hDlg, ctlId, EM_SETLIMITTEXT, (WPARAM)(nLength), 0)

//设置文本输入框是否只读
#define TextBox_SetReadOnly(hDlg, ctlId, bReadOnly) \
	SendDlgItemMessage(hDlg, ctlId, EM_SETREADONLY, (WPARAM)(bReadOnly), 0)


//
// UpDown : 带有两个方向箭头的控件，用于调整数值
//

#define UpDown_SetBuddy(hwndCtl, hBuddy) \
	SendMessage((hwndCtl), UDM_SETBUDDY, (WPARAM)(hBuddy), 0)

#define UpDown_GetBuddy(hwndCtl) \
	((HWND)SendMessage((hwndCtl), UDM_GETBUDDY, 0, 0))

#define UpDown_SetRange32(hwndCtl, iLow, iHigh) \
	SendMessage((hwndCtl), UDM_SETRANGE32, (WPARAM)(iLow), (LPARAM)(iHigh))

#define UpDown_GetRange32(hwndCtl, pLow, pHigh) \
	SendMessage((hwndCtl), UDM_GETRANGE32, (WPARAM)(pLow), (LPARAM)(pHigh))

#define UpDown_SetPos32(hwndCtl, nPos) \
	SendMessage((hwndCtl), UDM_SETPOS32, 0, (LPARAM)(nPos))

#define UpDown_GetPos32(hwndCtl, pfError) \
	((int)SendMessage((hwndCtl), UDM_GETPOS32, 0, (LPARAM)(pfError)))

#define UpDown_SetPos(hwndCtl, nPos) \
	SendMessage((hwndCtl), UDM_SETPOS, 0, (LPARAM)MAKELONG((short)(nPos), 0))

#define UpDown_GetPos(hwndCtl) \
	((int)SendMessage((hwndCtl), UDM_GETPOS, 0, 0))

#define UpDown_SetBase(hwndCtl, nBase) \
	((int)SendMessage((hwndCtl), UDM_SETBASE, (WPARAM)(int)(nBase), 0))

#define UpDown_GetBase(hwndCtl) \
	((int)SendMessage((hwndCtl), UDM_GETBASE, 0, 0))

//
// 函数声明
//
void FocusDlgItem(HWND hDlg, int ctlId);
BOOL CALLBACK CtrlPanelDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);