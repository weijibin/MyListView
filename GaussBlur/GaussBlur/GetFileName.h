#pragma once

BOOL GetFileName_Open(HWND hWnd, LPCTSTR szTitle, LPTSTR szBuf_FileName, 
	int nFilterIndex, LPCTSTR pFilter, LPCTSTR pDefExt, BOOL bOpenForRead);

BOOL SelectDir(HWND hWnd, LPCTSTR lpszTitle, LPTSTR szBuf);