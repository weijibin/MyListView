#include "stdafx.h"
#include <CommDlg.h>					//for GetOpenFileName
#include <shlobj.h>						//for SHBrowseForFolder
//#include <Cderr.h>

#pragma comment(lib, "Comdlg32.lib")	//for GetOpenFileName
#pragma comment(lib, "shell32.lib")		//for SHBrowseForFolder

//��ȡ�򿪵��ļ���
//bOpenForRead: TRUE-���ļ�; FALSE-�����ļ�
BOOL GetFileName_Open(HWND hWnd, LPCTSTR szTitle, LPTSTR szBuf_FileName, 
	int nFilterIndex, LPCTSTR pFilter, LPCTSTR pDefExt, BOOL bOpenForRead)
{
	szBuf_FileName[0] = 0;
	OPENFILENAME ofn;

	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = pFilter; //_T("Text Files(*.txt)\0*.txt\0\0");
	ofn.lpstrDefExt = pDefExt; //3�ַ�Ĭ�Ϻ�׺��������.��������û�û��д��׺���򲹳������׺
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
		| OFN_HIDEREADONLY; //���ء���ֻ����ʽ�򿪡�CheckBox

		//| OFN_OVERWRITEPROMPT //���Ǿ���
		//| OFN_DONTADDTORECENT //��Ҫ��ӵ�����򿪵��ĵ��б�
		//| OFN_NONETWORKBUTTON //û�����簴ť
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

//�û�ѡȡһ���ļ���
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

	//���com�Զ��߳�ģʽ��ʼ��������ָ��BIF_USENEWUI���ᵼ����ʧ�ܣ�
	//Note: If COM is initialized using CoInitializeEx with the COINIT_MULTITHREADED flag, 
	//SHBrowseForFolder fails if the caller uses the BIF_USENEWUI or BIF_NEWDIALOGSTYLE flag
	//in the BROWSEINFO structure.
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
		//| BIF_EDITBOX //��ʾһ���ı���
		// | BIF_USENEWUI;

	bi.lpfn = NULL; 
	bi.lParam = 0; 
	bi.iImage = 0; 

	//��ʾ����ļ��еĶԻ���
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