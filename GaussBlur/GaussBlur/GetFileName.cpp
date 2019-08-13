#include "stdafx.h"
#include <CommDlg.h>					//for GetOpenFileName
#include <shlobj.h>						//for SHBrowseForFolder
//#include <Cderr.h>

#pragma comment(lib, "Comdlg32.lib")	//for GetOpenFileName
#pragma comment(lib, "shell32.lib")		//for SHBrowseForFolder

//获取打开的文件名
//bOpenForRead: TRUE-打开文件; FALSE-保存文件
BOOL GetFileName_Open(HWND hWnd, LPCTSTR szTitle, LPTSTR szBuf_FileName, 
	int nFilterIndex, LPCTSTR pFilter, LPCTSTR pDefExt, BOOL bOpenForRead)
{
	szBuf_FileName[0] = 0;
	OPENFILENAME ofn;

	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = pFilter; //_T("Text Files(*.txt)\0*.txt\0\0");
	ofn.lpstrDefExt = pDefExt; //3字符默认后缀（不包括.），如果用户没有写后缀，则补充这个后缀
	ofn.nFilterIndex = nFilterIndex; // 1 based index
	ofn.lpstrFile = szBuf_FileName;
	ofn.lpstrInitialDir = NULL;

	ofn.lpstrTitle = szTitle;
	ofn.nMaxFile = MAX_PATH;

	//ofn.hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
	//ofn.lpTemplateName = MAKEINTRESOURCE(129);

	//ofn.lpstrDefExt = NULL; //_T("TXT");
	ofn.Flags = OFN_ENABLESIZING 
		| OFN_LONGNAMES
		| OFN_PATHMUSTEXIST
		| OFN_HIDEREADONLY; //隐藏“以只读方式打开”CheckBox

		//| OFN_OVERWRITEPROMPT //覆盖警告
		//| OFN_DONTADDTORECENT //不要添加到最近打开的文档列表
		//| OFN_NONETWORKBUTTON //没有网络按钮
		//| OFN_FILEMUSTEXIST
		//| OFN_EXPLORER
		//| OFN_ENABLETEMPLATEHANDLE
	
	BOOL bRet = FALSE;
	if(bOpenForRead)
	{
		ofn.Flags |= OFN_FILEMUSTEXIST;
		bRet = GetOpenFileName(&ofn);
	}
	else
	{
		ofn.Flags |= (OFN_OVERWRITEPROMPT | OFN_DONTADDTORECENT);
		bRet = GetSaveFileName(&ofn);
	}
	//DWORD nErr = CDERR_DIALOGFAILURE;
	//if(!bRet)
	//	nErr = CommDlgExtendedError();
	return bRet;
}

//用户选取一个文件夹
BOOL SelectDir(HWND hWnd, LPCTSTR lpszTitle, LPTSTR szBuf)
{
	BROWSEINFO bi; 
	LPITEMIDLIST pIDL = NULL; 

	if(szBuf != NULL)
		szBuf[0] = 0;

	bi.hwndOwner = hWnd; 
	bi.pidlRoot = NULL; 
	bi.pszDisplayName = szBuf; 
	bi.lpszTitle = lpszTitle; 

	//如果com以多线程模式初始化，则不能指定BIF_USENEWUI，会导致其失败！
	//Note: If COM is initialized using CoInitializeEx with the COINIT_MULTITHREADED flag, 
	//SHBrowseForFolder fails if the caller uses the BIF_USENEWUI or BIF_NEWDIALOGSTYLE flag
	//in the BROWSEINFO structure.
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
		//| BIF_EDITBOX //显示一个文本框
		// | BIF_USENEWUI;

	bi.lpfn = NULL; 
	bi.lParam = 0; 
	bi.iImage = 0; 

	//显示浏览文件夹的对话框
	pIDL = SHBrowseForFolder(&bi);

	if (pIDL == NULL) 
		return FALSE;

	BOOL bRet = SHGetPathFromIDList(pIDL, szBuf);
	//if(bRet)
	//{
		//SetDlgItemText(hDlg, textboxId, dir);
	//}
	CoTaskMemFree(pIDL);
	return bRet;
}