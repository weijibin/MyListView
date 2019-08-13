// GaussBlur.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "GaussBlurDemo.h"

#include <stdio.h>
#include <atlimage.h>
#include <commctrl.h>
#include <windowsx.h>		//for ComboBox_XXX Macros;
#include "MulSelCtl.h"		//for Slider Control
#include "GetFileName.h"
#include "Dialogs.h"
#include "ImgViewWnd.h"
#include "GaussBlurFilter.hpp"

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "MulSelCtl.lib")	//for Slider Control

//�Ը�˹��άģ����ӻ�������Ƿ�洢��һ�� BMP λͼ�ļ�
#define SAVE_TO_FILE			0
#define FNAME_VISUALIZATION		_T("E:\\GaussTempl.BMP") //ģ����ӻ�ʱ����� BMP �ļ���
#define MAX_LOADSTRING			128
#define MSGBOX_TITLE			_T("��˹ģ�� DEMO")

//
// �������
//

#define SLIDER_WIDTH			4
#define TOOLBAR_HEIGHT			29
#define STATUSBAR_HEIGHT		22

typedef struct tagLAYOUT
{
	int nView1_Width;	//���View1 �� ��ǰ���
	int nClientWidth;	//��ʱ�ͻ����Ŀ��
	int nPanelHeight;	//�ײ�Panel �����ʱ�߶�
} LAYOUT, *LPLAYOUT;

//
// ״̬���� Parts ����
//
enum StatusBarParts
{
	SBP_STATUS = 0,
	SBP_PROCESSOR_COUNT,
	SBP_IMAGESIZE,
	SBP_BPP,
	SBP_TIMESPAN,
};

//
// �Ӵ��ڵ�����
//

enum ChildWndIndex
{
	IDX_TOOLBAR = 0,
	IDX_VIEW1,
	IDX_SLIDER,
	IDX_VIEW2,
	IDX_PANEL,
	IDX_STATUSBAR,
};

#define IDX_LAST				IDX_STATUSBAR

//
// �Ӵ��ڵ� ID
//

enum ChildWndId
{
	IDC_TOOLBAR = 10001,
	IDC_VIEW1,
	IDC_SLIDER,
	IDC_VIEW2,
	IDC_PANEL,
	IDC_STATUSBAR,
};

#define IDC_FIRST				IDC_TOOLBAR

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

int g_nProcessors;		//��ǰ�����Ĵ�����������
HIMAGELIST g_hImageList; //ToolBar ��ͼƬ�б�

HWND g_hwnds[IDX_LAST + 1];	//�����Ӵ���
RECT g_rects[IDX_LAST + 1]; //�Ӵ��ڵ� Bounds
LAYOUT g_layout;

CImage g_Img;			//��ֻ���������ػ򱣴�ͼ�񣬲������κ�������;
IMG_INFO g_ImgInfo[2];	//�ֱ��Ӧԭͼ��ģ������
IFilter* g_pFilters[2]; //��˹ģ���㷨����Ӧ�����������ͣ�0-float; 1-double)

// �˴���ģ���а����ĺ�����ǰ������:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
BOOL OpenPicFile(HWND hWnd, LPCTSTR fname);
BOOL DoFilter(HWND hWnd, LPTSTR pErrMsg, UINT nBufSize);

// ���������
void ArrangeStatusBarParts(HWND hStatusBar, int totalWidth);
void UpdateStatusBar(HWND hStatusBar, int iPart, LPCTSTR szText);
void InitStatusBar(HWND hStatusBar);
void InitToolBar(HWND hToolBar);
BOOL LayoutChildren(HWND hWnd);
void SetSlidersSpace();
void OnSize(HWND hWnd, BOOL bEventFromSlider);
void OnDestroy();

//
// ���ӻ����
//
double* GetTempl(double sigma, int r);
void WriteBufToFile(LPVOID lpBuf, int nBufSize, FILE *fp);
int GetAbs(int x);
void TemplVisualize(HWND hWnd, double sigma, int cellSize, BOOL bGridLines);


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HACCEL hAccelTable;

	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icc.dwICC = ICC_STANDARD_CLASSES | ICC_UPDOWN_CLASS | ICC_BAR_CLASSES;
	InitCommonControlsEx(&icc);

	//ע��splitter�ؼ�
	InitMulSelControls(IMSC_SLIDER);

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GAUSSBLUR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if(!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAUSSBLUR));

	while(GetMessage(&msg, NULL, 0, 0))
	{
		if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= 0; //CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAUSSBLUR));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GAUSSBLUR);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	ATOM retval = RegisterClassEx(&wcex);

	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LPVOID);
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_MENUBAR + 1); //����ˢ�����ؼ������õ�
	wcex.lpszMenuName = NULL;
	wcex.hIconSm = NULL;
	
	// ���Զ���ؼ����� DLL �У�����������ʹ�ã�������������������
	//
	//��1���� ClassStyle ��ָ�� CS_GLOBALCLASS
	//��2�������� DLL ����ʱ��ע�ᴰ���࣡
	//��3���ؼ��ڳߴ�ı�ʱ�Ƿ���Ҫ�ػ棿��CS_HREDRAW / CS_VREDRAW����
	//     ���ñ���ˢ����ʱ�ᵼ����˸

	wcex.style = 0; //CS_HREDRAW | CS_VREDRAW; �� WM_SIZE ���ػ�
	wcex.lpfnWndProc = ImgViewWndProc;
	wcex.lpszClassName = WC_IMGVIEW;
	RegisterClassEx(&wcex);

	return retval;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	g_nProcessors = sysInfo.dwNumberOfProcessors;

	//����IFilter
	g_pFilters[0] = new CGaussBlurFilter<float>();
	g_pFilters[1] = new CGaussBlurFilter<double>();

	//�����Ӵ���
	LPCTSTR pNames[] =
	{
		TOOLBARCLASSNAME,		_T("ToolBar"),
		WC_IMGVIEW,				_T("ImgView1"),
		WC_SLIDER,				_T("VBSlider"),
		WC_IMGVIEW,				_T("ImgView2"),
		NULL,					_T("CtrlPanel"), //Panel ���⴦��
		STATUSCLASSNAME,		_T("StatusBar"),
	};

	DWORD dwStyles[] =
	{
		//ToolBar:
		TBSTYLE_EX_DOUBLEBUFFER,	//˫������ڴ����ã� ������չ��ʽӦ���ڴ����������󣬷�����Ϣȥ���á�MixedButtons ����� List ��ʽһ�����á�
		WS_BORDER | CCS_ADJUSTABLE | TBSTYLE_TOOLTIPS | TBSTYLE_LIST, // (������ø����ԣ����ı���ʾ�ڰ�ť�ҷ�) 

		//View1
		0,
		WS_VSCROLL | WS_HSCROLL | WS_VISIBLE,

		//slider
		0,
		WS_VISIBLE,

		//View2
		0,
		WS_VSCROLL | WS_HSCROLL | WS_VISIBLE,

		//panel: ���⴦��
		0,
		0,
		
		//StatusBar
		0,
		SBARS_SIZEGRIP,		//SBARS_TOOLTIPS
	};

	//���� panel ���
	g_hwnds[IDX_PANEL] = CreateDialogParam(hInstance,
		MAKEINTRESOURCE(IDD_CTRLPANEL),
		hWnd,
		(DLGPROC)CtrlPanelDlgProc,
		(LPARAM)g_nProcessors);

	RECT rcPanel;
	GetClientRect(g_hwnds[IDX_PANEL], &rcPanel);
	g_layout.nPanelHeight = rcPanel.bottom;

	LayoutChildren(hWnd);

	int i;
	for(i = 0; i <= IDX_LAST; i++)
	{
		if(i == IDX_PANEL)
			continue;

		g_hwnds[i] = CreateWindowEx(dwStyles[i * 2],
			pNames[i * 2],
			pNames[i * 2 + 1],
			dwStyles[i * 2 + 1] | WS_CHILD, //window styles,
			g_rects[i].left,
			g_rects[i].top,
			g_rects[i].right - g_rects[i].left,
			g_rects[i].bottom - g_rects[i].top,
			hWnd,
			(HMENU)(IDC_FIRST + i),
			hInstance,
			0); //lParam;
	}

	InitToolBar(g_hwnds[IDX_TOOLBAR]);
	InitStatusBar(g_hwnds[IDX_STATUSBAR]);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		case IDM_OPEN: //��һ��ͼƬ�ļ�
			{
				TCHAR fname[MAX_PATH];
				if(GetFileName_Open(hWnd, _T("��ͼƬ�ļ�"), 
					fname, 
					5, //nFilterIndex
					_T("JPEG (*.JPG;*.JPEG;*.JPE)\0*.JPG;*.JPEG;*.JPE\0")
					_T("BMP (*.BMP;*.RLE;*.DIB)\0*.BMP;*.RLE;*.DIB\0")
					_T("PNG (*.PNG)\0*.PNG\0")
					_T("GIF (*.GIF)\0*.GIF\0")
					_T("ͼ���ļ�\0*.JPG;*.JPEG;*.JPE;*.BMP;*.RLE;*.DIB;*.PNG;*.GIF\0")
					_T("�����ļ� (*.*)\0*.*\0\0"),
					NULL, TRUE))
				{
					OpenPicFile(hWnd, fname);
				}
			}
			break;

		case IDM_SAVE:
			{
				TCHAR fname[MAX_PATH];

				HBITMAP hBitmap2 = (HBITMAP)SendMessage(g_hwnds[IDX_VIEW2],
					WM_GETIMGHANDLE, 0, 0);

				if(hBitmap2 == NULL)
				{
					MessageBox(hWnd, _T("��û��ִ�и�˹ģ����û�н���ɱ��棡"), 
						MSGBOX_TITLE, MB_ICONWARNING);
					return TRUE;
				}

				if(GetFileName_Open(hWnd, _T("���洦����"), 
					fname, 
					5, //nFilterIndex
					_T("JPEG (*.JPG;*.JPEG;*.JPE)\0*.JPG;*.JPEG;*.JPE\0")
					_T("BMP (*.BMP;*.RLE;*.DIB)\0*.BMP;*.RLE;*.DIB\0")
					_T("PNG (*.PNG)\0*.PNG\0")
					_T("GIF (*.GIF)\0*.GIF\0")
					_T("ͼ���ļ�\0*.JPG;*.JPEG;*.JPE;*.BMP;*.RLE;*.DIB;*.PNG;*.GIF\0")
					_T("�����ļ� (*.*)\0*.*\0\0"),
					_T("JPG"), FALSE))
				{					
					g_Img.Attach(hBitmap2);
					HRESULT hr = g_Img.Save(fname);
					g_Img.Detach();

					if(SUCCEEDED(hr))
						UpdateStatusBar(g_hwnds[IDX_STATUSBAR], SBP_STATUS, _T("����ɹ���"));
					else
						MessageBox(hWnd, _T("����ʧ�ܣ�"), MSGBOX_TITLE, MB_ICONWARNING);
				}
			}
			break;

		case IDM_CLOSE: //�ر�ͼ��
			{
				if(g_ImgInfo[0].hBitmap != NULL)
					DeleteObject(g_ImgInfo[0].hBitmap);
				
				if(g_ImgInfo[1].hBitmap != NULL)
					DeleteObject(g_ImgInfo[1].hBitmap);

				memset(&g_ImgInfo[0], 0, sizeof(IMG_INFO));
				memset(&g_ImgInfo[1], 0, sizeof(IMG_INFO));

				SendMessage(g_hwnds[IDX_VIEW1], WM_SETIMGINFO, 0, (LPARAM)(&g_ImgInfo[0]));
				SendMessage(g_hwnds[IDX_VIEW2], WM_SETIMGINFO, 0, (LPARAM)(&g_ImgInfo[1]));

				UpdateStatusBar(g_hwnds[IDX_STATUSBAR], SBP_IMAGESIZE, _T(""));
				UpdateStatusBar(g_hwnds[IDX_STATUSBAR], SBP_BPP, _T(""));
				UpdateStatusBar(g_hwnds[IDX_STATUSBAR], SBP_TIMESPAN, _T("��ʱ:"));
			}
			break;

		case IDM_GAUSSBLUR: //��˹ģ��
			{
				TCHAR errmsg[256];
				if(!DoFilter(hWnd, errmsg, _ARRAYSIZE(errmsg)))
					MessageBox(hWnd, errmsg, MSGBOX_TITLE, MB_ICONWARNING);
			}
			break;

		case IDM_VISUALIZE: //���ӻ���άģ��
			{
				TCHAR szText[32];
				GetDlgItemText(g_hwnds[IDX_PANEL], IDC_SIGMA, szText, _ARRAYSIZE(szText));
				double sigma = _tcstod(szText, NULL);
				int r = (int)(sigma * 3.0 + 0.5);

				if(r < 1 || r > 18)
				{
					MessageBox(hWnd, _T("��˹�뾶������Χ���������� [0.200 - 5.999] ֮�䣡"), 
						MSGBOX_TITLE, MB_ICONWARNING);
					return TRUE;
				}
				TemplVisualize(hWnd, sigma, (r <= 9)? 16 : 8, TRUE);
			}
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc;
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		break;

	case WM_ERASEBKGND:
		return TRUE;

	case WM_NOTIFY:
		{
			LPNMHDR pNMHDR = (LPNMHDR)lParam;
			//if(pNMHDR->code == TTN_GETDISPINFO)
			//{
			//	OnNotify_ToolTip(hWnd, pNMHDR);
			//	break;
			//}
			switch(pNMHDR->idFrom)
			{
			case IDC_SLIDER: //�϶���ֱ��
				{
					LPNMSLHDR pHdr = (LPNMSLHDR)lParam;
					//g_data.nWidth_TreeView += pHdr->diff;
					g_layout.nView1_Width += pHdr->diff;
					//���������ӿؼ������ǲ���ʵ���ƶ����ǣ��������SetWindowPos��Ӧλ�ñ仯������
					LayoutChildren(hWnd);
					OnSize(hWnd, TRUE); //onsize �ں����� sliders �ƶ���Χ�ĵ��á�
				}
				break;			
			}
		};
		break;

	case WM_GETMINMAXINFO:
		{
			//�趨���ڵ���С�ߴ�Ϊ 800 * 600
			MINMAXINFO* pMMInfo = (MINMAXINFO*)lParam;
			pMMInfo->ptMinTrackSize.x = 400;
			pMMInfo->ptMinTrackSize.y = 300;
			return TRUE;
		}
		break;

	case WM_SIZE:
		OnSize(hWnd, FALSE);
		break;

	case WM_DESTROY:
		OnDestroy();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


//��һ��ͼƬ�ļ�ʱ��ִ�еĶ���
BOOL OpenPicFile(HWND hWnd, LPCTSTR fname)
{
	HRESULT hr = g_Img.Load(fname);
	if(!SUCCEEDED(hr) || g_Img.IsNull())
	{
		MessageBox(hWnd, _T("��ͼƬʧ�ܣ�"), MSGBOX_TITLE, MB_ICONWARNING);
		return FALSE;
	}

	if(g_ImgInfo[0].hBitmap != NULL)
		DeleteObject(g_ImgInfo[0].hBitmap);

	if(g_ImgInfo[1].hBitmap != NULL)
		DeleteObject(g_ImgInfo[1].hBitmap);

	g_ImgInfo[0].bmWidth = g_Img.GetWidth();
	g_ImgInfo[0].bmHeight = g_Img.GetHeight();
	g_ImgInfo[0].bpp = g_Img.GetBPP();

	//bottom-up: ����GetBits�������صĲ��������ݿ��ͷ�������ǿ���β��
	if(g_Img.GetPitch() < 0)
		g_ImgInfo[0].lpBits = g_Img.GetPixelAddress(0, g_Img.GetHeight() - 1);
	else
		g_ImgInfo[0].lpBits = g_Img.GetBits();
	g_ImgInfo[0].hBitmap = g_Img.Detach();

	//
	// ������ͼ
	//
	memset(&g_ImgInfo[1], 0, sizeof(IMG_INFO));
	SendMessage(g_hwnds[IDX_VIEW1], WM_SETIMGINFO, 0, (LPARAM)(&g_ImgInfo[0]));
	SendMessage(g_hwnds[IDX_VIEW2], WM_SETIMGINFO, 0, (LPARAM)(&g_ImgInfo[1]));

	//��¡һ����ͬ��С��λͼ�����ڱ����˹ģ���Ľ��
	g_Img.Create(g_ImgInfo[0].bmWidth, g_ImgInfo[0].bmHeight, g_ImgInfo[0].bpp);


	//����ǻҶ�ͼ������ͼ�񣩣���������õ�ɫ��
	if(g_ImgInfo[0].bpp == 8)
	{
		//������ɫ��
		RGBQUAD colors[256];
		for(int i = 0; i < 256; i++)
		{
			colors[i].rgbRed = i;
			colors[i].rgbGreen = i;
			colors[i].rgbBlue = i;
			colors[i].rgbReserved = 0;
		}
		g_Img.SetColorTable(0, 256, colors);
	}
	memcpy(&g_ImgInfo[1], &g_ImgInfo[0], sizeof(IMG_INFO));

	if(g_Img.GetPitch() < 0)
		g_ImgInfo[1].lpBits = g_Img.GetPixelAddress(0, g_Img.GetHeight() - 1);
	else
		g_ImgInfo[1].lpBits = g_Img.GetBits();

	g_ImgInfo[1].hBitmap = g_Img.Detach();

	//����״̬��
	TCHAR szText[48];
	_stprintf_s(szText, _ARRAYSIZE(szText), _T("ͼƬ�ߴ�: %ld x %ld"), 
		g_ImgInfo[0].bmWidth,
		g_ImgInfo[0].bmHeight);
	UpdateStatusBar(g_hwnds[IDX_STATUSBAR], SBP_IMAGESIZE, szText);

	_stprintf_s(szText, _ARRAYSIZE(szText), _T("BPP: %d"), g_ImgInfo[0].bpp);
	UpdateStatusBar(g_hwnds[IDX_STATUSBAR], SBP_BPP, szText);

	return TRUE;
}

BOOL DoFilter(HWND hWnd, LPTSTR pErrMsg, UINT nBufSize)
{
	if(g_ImgInfo[0].hBitmap == NULL)
	{
		_tcscpy_s(pErrMsg, nBufSize, _T("���ȴ�һ��ͼƬ��"));
		return FALSE;
	}

	GdiFlush();

	TCHAR szText[48];
	float sigma0 = 0;
	double sigma1 = 0;
	LPVOID pInfo[2] = { &sigma0, &sigma1 };
	BOOL bTranslated = FALSE;
	HWND hComboBox = GetDlgItem(g_hwnds[IDX_PANEL], IDC_CB_FLOATTYPE);
	int nFilter = ComboBox_GetCurSel(hComboBox);

	bool bMultiThread = 
		(IsDlgButtonChecked(g_hwnds[IDX_PANEL], IDC_CHECK_MULTITHREAD) == BST_CHECKED);

	int nThreadCount = GetDlgItemInt(g_hwnds[IDX_PANEL], IDC_THREADCOUNT, &bTranslated, FALSE);

	if(nThreadCount < 2 || nThreadCount > 16)
	{
		SetDlgItemInt(g_hwnds[IDX_PANEL], IDC_THREADCOUNT,
			(nThreadCount < 2)? 2 : 16,
			FALSE);

		_tcscpy_s(pErrMsg, nBufSize, _T("�߳�����Ч��Χ��[2, 16];\r\n�Ѳ�����ӽ�����ֵ��"));
		MessageBox(hWnd, pErrMsg, MSGBOX_TITLE, MB_ICONWARNING);

		TextBox_SelectAll(g_hwnds[IDX_PANEL], IDC_THREADCOUNT);
		FocusDlgItem(g_hwnds[IDX_PANEL], IDC_THREADCOUNT);

		return TRUE;
	}

	GetDlgItemText(g_hwnds[IDX_PANEL], IDC_SIGMA, szText, _ARRAYSIZE(szText));
	sigma1 = _tcstod(szText, NULL);
	sigma0 = (float)sigma1;

	if(sigma1 < 0.1 || sigma1 > 250.0)
	{
		if(sigma1 < 0.1)
			SetDlgItemText(g_hwnds[IDX_PANEL], IDC_SIGMA, _T("0.1"));
		else
			SetDlgItemText(g_hwnds[IDX_PANEL], IDC_SIGMA, _T("250.0"));

		_tcscpy_s(pErrMsg, nBufSize, _T("��˹�뾶��Ч��Χ��[0.1, 250.0];\r\n�Ѳ�����ӽ�����ֵ��"));
		MessageBox(hWnd, pErrMsg, MSGBOX_TITLE, MB_ICONWARNING);

		TextBox_SelectAll(g_hwnds[IDX_PANEL], IDC_SIGMA);
		FocusDlgItem(g_hwnds[IDX_PANEL], IDC_SIGMA);

		return TRUE;
	}

	g_pFilters[nFilter]->SetMultiThreads(bMultiThread, nThreadCount);

	DWORD dwTickBegin = GetTickCount();

	//���ø�˹�뾶
	g_pFilters[nFilter]->Init(pInfo[nFilter]);

	g_pFilters[nFilter]->Filter(
		g_ImgInfo[0].lpBits, 
		g_ImgInfo[1].lpBits,
		g_ImgInfo[0].bmWidth, g_ImgInfo[0].bmHeight, g_ImgInfo[0].bpp);

	DWORD dwTickEnd = GetTickCount();

	//������ͼ2
	HANDLE hBitmap2 = (HANDLE)SendMessage(g_hwnds[IDX_VIEW2], WM_GETIMGHANDLE, 0, 0);
	if(hBitmap2 == NULL)
		SendMessage(g_hwnds[IDX_VIEW2], WM_SETIMGINFO, 0, (LPARAM)(&g_ImgInfo[1]));
	else
		InvalidateRect(g_hwnds[IDX_VIEW2], NULL, FALSE);

	//����״̬���ĺ�ʱʱ��
	int msec = dwTickEnd - dwTickBegin;
	_stprintf_s(szText, _ARRAYSIZE(szText), 
		_T("��ʱ: %ld.%03ld sec"),
		msec / 1000,
		msec - msec / 1000 * 1000);
	UpdateStatusBar(g_hwnds[IDX_STATUSBAR], SBP_TIMESPAN, szText);

	return TRUE;
}

//����״̬������ parts ��λ��
void ArrangeStatusBarParts(HWND hStatusBar, int totalWidth)
{
	int i;

	//width[0] ȡʣ��ߴ磻���� parts ���Ҷ���
	int widths[5] = 
	{
		0,
		90,
		160,
		60,
		150,
	};
	widths[0] = totalWidth;
	for(i = 1; i < _ARRAYSIZE(widths); i++)
	{
		widths[0] = widths[0] - widths[i];
	}
	for(i = 1; i < _ARRAYSIZE(widths) - 1; i++)
	{
		widths[i] = widths[i - 1] + widths[i];
	}
	widths[i] = -1; //���һ��
	SendMessage(hStatusBar, SB_SETPARTS, _ARRAYSIZE(widths), (LPARAM)widths);
}

void UpdateStatusBar(HWND hStatusBar, int iPart, LPCTSTR szText)
{
	SendMessage(hStatusBar, SB_SETTEXT, (WPARAM)(iPart), (LPARAM)(szText));
}

void InitStatusBar(HWND hStatusBar)
{
	//״̬��������ұ�Ե���ꡣ��-1Ϊ�ִ����Ե��
	RECT rc;
	HWND hwnd = GetParent(hStatusBar);
	GetWindowRect(hwnd, &rc);
	ArrangeStatusBarParts(hStatusBar, rc.right - rc.left);

	//��ʼ��״̬���Ĺ̶���ʾ
	TCHAR szText[128];
	_tcscpy_s(szText, _ARRAYSIZE(szText), _T("����"));
	UpdateStatusBar(hStatusBar, SBP_STATUS, szText);

	
	_stprintf_s(szText, _ARRAYSIZE(szText), _T("��������: %d"),	g_nProcessors);
	UpdateStatusBar(hStatusBar, SBP_PROCESSOR_COUNT, szText);
	UpdateStatusBar(hStatusBar, SBP_TIMESPAN, _T("��ʱ:"));

	SendMessage(hStatusBar, WM_SIZE, 0, 0);
	ShowWindow(hStatusBar, SW_SHOW);
}

void InitToolBar(HWND hToolBar)
{
	//ע�⣺TBSTYLE_EX_MIXEDBUTTONS ���봴�� ToolBar ֮������
	//TBSTYLE_EX_DOUBLEBUFFER : ˫����
	SendMessage(hToolBar, TB_SETEXTENDEDSTYLE, 0, TBSTYLE_EX_MIXEDBUTTONS);

	TBBUTTON btns[4];
	int idCmds[4] = { IDM_OPEN, IDM_SAVE, IDM_GAUSSBLUR, IDM_ABOUT };
	BYTE fsStyles[4] = 
	{
		BTNS_BUTTON, // | BTNS_SHOWTEXT,
		BTNS_BUTTON, // | BTNS_SHOWTEXT
		BTNS_BUTTON,
		BTNS_BUTTON
	};
	LPTSTR szStrs[4] = 
	{ 
		_T("��ͼ��"), 
		_T("���洦���Ľ��ͼ��"), 
		_T("ִ�и�˹ģ��"), 
		_T("����"),
	};

	int i;
	for(i = 0; i < _ARRAYSIZE(btns); i++)
	{
		btns[i].iBitmap = i; //iBitmap[i] ;
		btns[i].idCommand = idCmds[i];
		btns[i].fsState = TBSTATE_ENABLED;
		btns[i].fsStyle = fsStyles[i];
		btns[i].iString = (INT_PTR)szStrs[i];
	}

	g_hImageList = ImageList_LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP3),
		16, 4, RGB(0xFF, 0, 0xFF), IMAGE_BITMAP, 
		LR_DEFAULTCOLOR); //| LR_CREATEDIBSECTION);

	SendMessage(hToolBar, TB_SETIMAGELIST, 0, (LPARAM)g_hImageList);
	//SendMessage(hToolBar, TB_SETDISABLEDIMAGELIST, 0, (LPARAM)g_data.hIL_ToolBar_Gray);
	//SendMessage(hToolBar, TB_LOADIMAGES, (WPARAM)IDB_STD_SMALL_COLOR, (LPARAM)HINST_COMMCTRL);

	SendMessage(hToolBar, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);
	
	SendMessage(hToolBar, TB_ADDBUTTONS, _ARRAYSIZE(btns), (LPARAM) &btns[0]);
	SendMessage(hToolBar, TB_AUTOSIZE, 0, 0);
	ShowWindow(hToolBar, SW_SHOW); 
}

//�����ӽڵ�
BOOL LayoutChildren(HWND hWnd)
{
	RECT rc;
	GetClientRect(hWnd, &rc);

	//ע�������С���Ժ�õ��� ClientRect �� { 0, 0, 0, 0 }, ��ʱ��Ҫ��ᣡ����
	if(IsRectEmpty(&rc))
		return FALSE;

	//toolbar �� statusbar ����Ҫ���֣�ֻ��Ҫָ���߶ȼ��ɣ�
	int gap = 4; //���
	int index;

	//toolbar
	index = IDX_TOOLBAR;
	g_rects[index].left = 0;
	g_rects[index].top = 0;
	g_rects[index].right = rc.right;
	g_rects[index].bottom = TOOLBAR_HEIGHT;

	//view1
	index = IDX_VIEW1;
	g_rects[index].left = 0;
	g_rects[index].top = TOOLBAR_HEIGHT;

	if(g_layout.nClientWidth == 0)
	{
		g_layout.nClientWidth = rc.right;
		g_layout.nView1_Width = (rc.right - gap)/2;
		g_rects[index].right = g_layout.nView1_Width;

	}
	else
	{
		//�ȱ�����
		g_layout.nView1_Width = rc.right * g_layout.nView1_Width / g_layout.nClientWidth;
		g_layout.nClientWidth = rc.right;
		g_rects[index].right = g_rects[index].left + g_layout.nView1_Width;
	}
	g_rects[index].bottom = rc.bottom - g_layout.nPanelHeight - STATUSBAR_HEIGHT;

	//����View1��λ�ã�������С��32��������������
	if(g_rects[index].right - g_rects[index].left <= 32)
	{
		g_rects[index].right = g_rects[index].left;
	}

	
	//splitter
	index = IDX_SLIDER;
	g_rects[index].left = g_rects[IDX_VIEW1].right;
	g_rects[index].top = g_rects[IDX_VIEW1].top;
	g_rects[index].right = g_rects[index].left + gap;
	g_rects[index].bottom = g_rects[IDX_VIEW1].bottom;

	//view2
	index = IDX_VIEW2;
	g_rects[index].left = g_rects[IDX_SLIDER].right;
	g_rects[index].top = g_rects[IDX_VIEW1].top;
	g_rects[index].right = rc.right;
	g_rects[index].bottom = g_rects[IDX_VIEW1].bottom;

	//���� View2 ��λ�ã�������С��32����������
	if(g_rects[index].right - g_rects[index].left <= 32)
	{
		g_rects[index].left = g_rects[index].right;

		//View1 �� Slider ͬʱ������
		g_rects[IDX_SLIDER].right = g_rects[index].left;
		g_rects[IDX_SLIDER].left = g_rects[IDX_SLIDER].right - gap;
		g_rects[IDX_VIEW1].right = g_rects[IDX_SLIDER].left;
	}

	//panel
	index = IDX_PANEL;
	g_rects[index].left = 0;
	g_rects[index].top = g_rects[IDX_VIEW1].bottom;
	g_rects[index].right = rc.right;
	g_rects[index].bottom = rc.bottom - STATUSBAR_HEIGHT;
	
	return TRUE;
}

//���� Sliders ���ƶ���Χ
void SetSlidersSpace()
{
	//treeview1 �� ��С��� �� 40 ����
	int leftSpace = g_rects[IDX_VIEW1].right - g_rects[IDX_VIEW1].left;
	int rightSpace = g_rects[IDX_VIEW2].right - g_rects[IDX_VIEW2].left;
	Slider_SetSpace(g_hwnds[IDX_SLIDER], SLSPACE_BOTH, leftSpace, rightSpace);
}

void OnSize(HWND hWnd, BOOL bEventFromSlider)
{
	int i, width, height;
	UINT nFlags;
	BOOL bResult = LayoutChildren(hWnd);
	if(bResult)
	{
		for(i = IDX_VIEW1; i <= IDX_PANEL; i++)
		{
			width = g_rects[i].right - g_rects[i].left;
			height = g_rects[i].bottom - g_rects[i].top;

			nFlags = SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_SHOWWINDOW;
			if(width <= 32 && (i == IDX_VIEW1 || i == IDX_VIEW2))
				nFlags = SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_HIDEWINDOW;				

			SetWindowPos(g_hwnds[i], NULL,
				g_rects[i].left,
				g_rects[i].top,
				width, height,
				nFlags); // | (bEventFromSlider? 0 : SWP_NOREDRAW));
		}
		SetSlidersSpace();
	}

	if(!bEventFromSlider)
	{
		SendMessage(g_hwnds[IDX_TOOLBAR], WM_SIZE, 0, 0);
		SendMessage(g_hwnds[IDX_STATUSBAR], WM_SIZE, 0, 0);

		RECT rcStatusBar;
		GetWindowRect(g_hwnds[IDX_STATUSBAR], &rcStatusBar);
		ArrangeStatusBarParts(g_hwnds[IDX_STATUSBAR], rcStatusBar.right - rcStatusBar.left);
	}
}

void OnDestroy()
{
	int i;
	delete g_pFilters[0];
	delete g_pFilters[1];
	
	for(i = 0; i <= IDX_LAST; i++)
		DestroyWindow(g_hwnds[i]);
	
	ImageList_Destroy(g_hImageList);
	
	if(g_ImgInfo[0].hBitmap != NULL)
		DeleteObject(g_ImgInfo[0].hBitmap);
	if(g_ImgInfo[1].hBitmap != NULL)
		DeleteObject(g_ImgInfo[1].hBitmap);
}


//
// �����Ǹ�˹��άģ����ӻ����
//

//��̬����ģ�壬������ģ���ֵ
double* GetTempl(double sigma, int r)
{
	//int r = (int)(sigma * 3 + 0.5);
	double *p = (double*)malloc((r + 1) * (r + 1) * sizeof(double));
	int row, col;

	double a1 = (-0.5) / (sigma * sigma);
	double a2 = - a1 * M_1_PI; //-a1 / pi;
	
	for(row = 0; row <= r; ++row)
	{
		for(col = 0; col <= r; ++col)
		{
			p[row * (r + 1) + col] = a2 * exp(a1 * (row * row + col * col));
		}
	}
	return p;
}

//�� 2KB Ϊ��λд���ڴ�
void WriteBufToFile(LPVOID lpBuf, int nBufSize, FILE *fp)
{
	LPBYTE lpBytes = (LPBYTE)lpBuf;
	int nRemain = nBufSize;
	int toWrite, written;
	while(nRemain > 0)
	{
		toWrite = min(nRemain, 2048);
		written = (int)fwrite(lpBytes, 1, toWrite, fp);
		fflush(fp);

		nRemain -= written;
		lpBytes += written;
	}
}

int GetAbs(int x)
{
	if(x >= 0)
		return x;
	else
		return -x;
}

//����ά��˹ģ�壬����һ�����ӻ���λͼ����ʾ���Ҳ��Ӵ��ڣ����߱����һ�� BMP λͼ
//cellSize: ��Ԫ���С
void TemplVisualize(HWND hWnd, double sigma, int cellSize, BOOL bGridLines)
{
	TCHAR szText[512];

	int r = (int)(sigma * 3 + 0.5);
	double *p = GetTempl(sigma, r);

	int row, col;

//������½�ģ��
#if 1
	for(row = 0; row <= r; ++row)
	{
		for(col = 0; col <= r; ++col)
		{
			_stprintf_s(szText, _ARRAYSIZE(szText), _T("%.4lf "), p[row * (r + 1) + col]);
			OutputDebugString(szText);
		}
		OutputDebugString(_T("\n"));
	}
#endif

	LPBYTE lpBits = NULL;
	int bpp = 8; //����ͼ��
	int pixelSize = bpp / 8;
	int width = (r * 2 + 1) * cellSize + 1;
	int stride = (width * bpp + 31)/32 * 4;

	RGBQUAD colors[256];
	for(int i = 0; i < 256; i++)
	{
		colors[i].rgbRed = i;
		colors[i].rgbGreen = i;
		colors[i].rgbBlue = i;
		colors[i].rgbReserved = 0;
	}

#if(SAVE_TO_FILE)
	//����һ��λͼ~��~
	BITMAPFILEHEADER h1 = { 0 };
	BITMAPINFO h2 = { 0 };

	h1.bfType = 0x4D42;
	h1.bfReserved1 = 0;
	h1.bfReserved2 = 0;
	h1.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	//���bpp=8����ͼƬ���� 256 ɫ��ɫ��
	if(bpp == 8)
		h1.bfOffBits += sizeof(RGBQUAD) * 256;

	h2.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	h2.bmiHeader.biWidth = width;
	h2.bmiHeader.biHeight = width;
	h2.bmiHeader.biPlanes = 1;
	h2.bmiHeader.biBitCount = bpp;

	h2.bmiHeader.biSizeImage = stride * h2.bmiHeader.biHeight;
	h1.bfSize = h1.bfOffBits + h2.bmiHeader.biSizeImage;
	
	lpBits = (LPBYTE)malloc(h2.bmiHeader.biSizeImage);
#else

	//���͹ر�����رյ�ǰ�򿪵�ͼ���ļ���
	SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDM_CLOSE, 0), 0);

	g_Img.Create(width, width, bpp);

	if(bpp == 8)
		g_Img.SetColorTable(0, 256, colors);

	if(g_Img.GetPitch() < 0)
		g_ImgInfo[1].lpBits = g_Img.GetPixelAddress(0, g_Img.GetHeight() - 1);
	else
		g_ImgInfo[1].lpBits = g_Img.GetBits();

	g_ImgInfo[1].bmWidth = width;
	g_ImgInfo[1].bmHeight = width;
	g_ImgInfo[1].bpp = bpp;
	g_ImgInfo[1].hBitmap = g_Img.Detach();
	lpBits = (LPBYTE)(g_ImgInfo[1].lpBits);

#endif

	//����lpBits
	LPBYTE lpPixel;
	BYTE gray, clrBorder = 0x9F; //����߿�ɫ
	int subRow, subCol;


	//����һ���Ŵ����ӣ�ʹ�����ر�ø���һЩ��
	double factor = 254 / p[0]; 
	
	for(row = 0; row < (r * 2 + 1); ++row)
	{
		for(col = 0; col < (r * 2 + 1); ++col)
		{
			gray = (BYTE)(p[ GetAbs(row - r) * (r + 1) + GetAbs(col - r)] * factor); 
			for(subRow = 0; subRow < cellSize; ++subRow)
			{
				lpPixel = lpBits + (row * cellSize + subRow) * stride + col * cellSize * pixelSize;

				for(subCol = 0; subCol < cellSize * pixelSize; ++subCol)
				{
					if(bGridLines && (subRow == 0 || subCol < pixelSize))
						lpPixel[subCol] = clrBorder; //����߽���
					else
						lpPixel[subCol] = gray;
				}				
			}
		}
	}

	//�������һ����ɫ
	row = r * 2 + 1;
	lpPixel = lpBits + row * cellSize * stride;
	for(col = 0; col < width * pixelSize; ++col)
		lpPixel[col] = clrBorder;

	//�������һ����ɫ
	col = (r * 2 + 1) * cellSize;
	for(row = 0; row < width; ++row)
	{
		lpPixel = lpBits + row * stride + col * pixelSize;
		lpPixel[0] = clrBorder;
		if(pixelSize >= 3)
		{
			lpPixel[1] = clrBorder;
			lpPixel[2] = clrBorder;
		}
	}

	//�ͷ�ģ��
	free(p);

#if(SAVE_TO_FILE)

	FILE* fp = NULL;
	errno_t err = _tfopen_s(&fp, FNAME_VISUALIZATION, _T("wb"));

	//if(err == EMFILE)
	//	OutputDebugString(_T("Too many open files! \n"));

	fwrite(&h1, 1, sizeof(BITMAPFILEHEADER), fp);
	fwrite(&h2, 1, sizeof(BITMAPINFOHEADER), fp);
	if(bpp == 8)
		fwrite(colors, sizeof(RGBQUAD), 256, fp);
	//fwrite(lpBits, 1, h2.bmiHeader.biSizeImage, fp);
	WriteBufToFile(lpBits, h2.bmiHeader.biSizeImage, fp);
	fclose(fp);
	
	//�ͷ�������ڴ�
	free(lpBits);

	_stprintf_s(szText, _ARRAYSIZE(szText), 
		_T("���ӻ��ļ��ѱ����浽:\r\n%s"), FNAME_VISUALIZATION);
	MessageBox(hWnd, szText, MSGBOX_TITLE, MB_ICONINFORMATION);

#else
	SendMessage(g_hwnds[IDX_VIEW2], WM_SETIMGINFO, 0, (LPARAM)(&g_ImgInfo[1]));
	_stprintf_s(szText, _ARRAYSIZE(szText), _T("ͼƬ�ߴ�: %ld x %ld"), width, width);
	UpdateStatusBar(g_hwnds[IDX_STATUSBAR], SBP_IMAGESIZE, szText);
	_stprintf_s(szText, _ARRAYSIZE(szText), _T("BPP: %d"), bpp);
	UpdateStatusBar(g_hwnds[IDX_STATUSBAR], SBP_BPP, szText);
#endif

}