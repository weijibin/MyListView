// GaussBlur.cpp : 定义应用程序的入口点。
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

//对高斯二维模板可视化结果，是否存储到一个 BMP 位图文件
#define SAVE_TO_FILE			0
#define FNAME_VISUALIZATION		_T("E:\\GaussTempl.BMP") //模板可视化时输出的 BMP 文件名
#define MAX_LOADSTRING			128
#define MSGBOX_TITLE			_T("高斯模糊 DEMO")

//
// 布局相关
//

#define SLIDER_WIDTH			4
#define TOOLBAR_HEIGHT			29
#define STATUSBAR_HEIGHT		22

typedef struct tagLAYOUT
{
	int nView1_Width;	//左侧View1 的 当前宽度
	int nClientWidth;	//此时客户区的宽度
	int nPanelHeight;	//底部Panel 的设计时高度
} LAYOUT, *LPLAYOUT;

//
// 状态栏的 Parts 索引
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
// 子窗口的索引
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
// 子窗口的 ID
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

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

int g_nProcessors;		//当前机器的处理器核心数
HIMAGELIST g_hImageList; //ToolBar 的图片列表

HWND g_hwnds[IDX_LAST + 1];	//所有子窗口
RECT g_rects[IDX_LAST + 1]; //子窗口的 Bounds
LAYOUT g_layout;

CImage g_Img;			//它只是用来加载或保存图像，不负责任何其他用途
IMG_INFO g_ImgInfo[2];	//分别对应原图和模糊后结果
IFilter* g_pFilters[2]; //高斯模糊算法（对应两个浮点类型：0-float; 1-double)

// 此代码模块中包含的函数的前向声明:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
BOOL OpenPicFile(HWND hWnd, LPCTSTR fname);
BOOL DoFilter(HWND hWnd, LPTSTR pErrMsg, UINT nBufSize);

// 进度条相关
void ArrangeStatusBarParts(HWND hStatusBar, int totalWidth);
void UpdateStatusBar(HWND hStatusBar, int iPart, LPCTSTR szText);
void InitStatusBar(HWND hStatusBar);
void InitToolBar(HWND hToolBar);
BOOL LayoutChildren(HWND hWnd);
void SetSlidersSpace();
void OnSize(HWND hWnd, BOOL bEventFromSlider);
void OnDestroy();

//
// 可视化相关
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

	//注册splitter控件
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
	wcex.hbrBackground = (HBRUSH)(COLOR_MENUBAR + 1); //背景刷，本控件不会用到
	wcex.lpszMenuName = NULL;
	wcex.hIconSm = NULL;
	
	// 把自定义控件放在 DLL 中，给其他进程使用，则必须符合以下条件：
	//
	//（1）在 ClassStyle 中指定 CS_GLOBALCLASS
	//（2）必须在 DLL 加载时，注册窗口类！
	//（3）控件在尺寸改变时是否需要重绘？（CS_HREDRAW / CS_VREDRAW），
	//     当用背景刷背景时会导致闪烁

	wcex.style = 0; //CS_HREDRAW | CS_VREDRAW; 在 WM_SIZE 中重绘
	wcex.lpfnWndProc = ImgViewWndProc;
	wcex.lpszClassName = WC_IMGVIEW;
	RegisterClassEx(&wcex);

	return retval;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // 将实例句柄存储在全局变量中

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	g_nProcessors = sysInfo.dwNumberOfProcessors;

	//创建IFilter
	g_pFilters[0] = new CGaussBlurFilter<float>();
	g_pFilters[1] = new CGaussBlurFilter<double>();

	//创建子窗口
	LPCTSTR pNames[] =
	{
		TOOLBARCLASSNAME,		_T("ToolBar"),
		WC_IMGVIEW,				_T("ImgView1"),
		WC_SLIDER,				_T("VBSlider"),
		WC_IMGVIEW,				_T("ImgView2"),
		NULL,					_T("CtrlPanel"), //Panel 特殊处理
		STATUSCLASSNAME,		_T("StatusBar"),
	};

	DWORD dwStyles[] =
	{
		//ToolBar:
		TBSTYLE_EX_DOUBLEBUFFER,	//双缓冲可在此设置， 其他扩展样式应该在创建工具栏后，发送消息去设置。MixedButtons 必须和 List 样式一起设置。
		WS_BORDER | CCS_ADJUSTABLE | TBSTYLE_TOOLTIPS | TBSTYLE_LIST, // (如果设置该属性，则文本显示在按钮右方) 

		//View1
		0,
		WS_VSCROLL | WS_HSCROLL | WS_VISIBLE,

		//slider
		0,
		WS_VISIBLE,

		//View2
		0,
		WS_VSCROLL | WS_HSCROLL | WS_VISIBLE,

		//panel: 特殊处理
		0,
		0,
		
		//StatusBar
		0,
		SBARS_SIZEGRIP,		//SBARS_TOOLTIPS
	};

	//创建 panel 面板
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

		case IDM_OPEN: //打开一个图片文件
			{
				TCHAR fname[MAX_PATH];
				if(GetFileName_Open(hWnd, _T("打开图片文件"), 
					fname, 
					5, //nFilterIndex
					_T("JPEG (*.JPG;*.JPEG;*.JPE)\0*.JPG;*.JPEG;*.JPE\0")
					_T("BMP (*.BMP;*.RLE;*.DIB)\0*.BMP;*.RLE;*.DIB\0")
					_T("PNG (*.PNG)\0*.PNG\0")
					_T("GIF (*.GIF)\0*.GIF\0")
					_T("图像文件\0*.JPG;*.JPEG;*.JPE;*.BMP;*.RLE;*.DIB;*.PNG;*.GIF\0")
					_T("所有文件 (*.*)\0*.*\0\0"),
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
					MessageBox(hWnd, _T("还没有执行高斯模糊，没有结果可保存！"), 
						MSGBOX_TITLE, MB_ICONWARNING);
					return TRUE;
				}

				if(GetFileName_Open(hWnd, _T("保存处理结果"), 
					fname, 
					5, //nFilterIndex
					_T("JPEG (*.JPG;*.JPEG;*.JPE)\0*.JPG;*.JPEG;*.JPE\0")
					_T("BMP (*.BMP;*.RLE;*.DIB)\0*.BMP;*.RLE;*.DIB\0")
					_T("PNG (*.PNG)\0*.PNG\0")
					_T("GIF (*.GIF)\0*.GIF\0")
					_T("图像文件\0*.JPG;*.JPEG;*.JPE;*.BMP;*.RLE;*.DIB;*.PNG;*.GIF\0")
					_T("所有文件 (*.*)\0*.*\0\0"),
					_T("JPG"), FALSE))
				{					
					g_Img.Attach(hBitmap2);
					HRESULT hr = g_Img.Save(fname);
					g_Img.Detach();

					if(SUCCEEDED(hr))
						UpdateStatusBar(g_hwnds[IDX_STATUSBAR], SBP_STATUS, _T("保存成功！"));
					else
						MessageBox(hWnd, _T("保存失败！"), MSGBOX_TITLE, MB_ICONWARNING);
				}
			}
			break;

		case IDM_CLOSE: //关闭图像
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
				UpdateStatusBar(g_hwnds[IDX_STATUSBAR], SBP_TIMESPAN, _T("耗时:"));
			}
			break;

		case IDM_GAUSSBLUR: //高斯模糊
			{
				TCHAR errmsg[256];
				if(!DoFilter(hWnd, errmsg, _ARRAYSIZE(errmsg)))
					MessageBox(hWnd, errmsg, MSGBOX_TITLE, MB_ICONWARNING);
			}
			break;

		case IDM_VISUALIZE: //可视化二维模板
			{
				TCHAR szText[32];
				GetDlgItemText(g_hwnds[IDX_PANEL], IDC_SIGMA, szText, _ARRAYSIZE(szText));
				double sigma = _tcstod(szText, NULL);
				int r = (int)(sigma * 3.0 + 0.5);

				if(r < 1 || r > 18)
				{
					MessageBox(hWnd, _T("高斯半径超出范围，请设置在 [0.200 - 5.999] 之间！"), 
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
			case IDC_SLIDER: //拖动垂直条
				{
					LPNMSLHDR pHdr = (LPNMSLHDR)lParam;
					//g_data.nWidth_TreeView += pHdr->diff;
					g_layout.nView1_Width += pHdr->diff;
					//布局所有子控件（但是不会实际移动他们，必须调用SetWindowPos反应位置变化！！！
					LayoutChildren(hWnd);
					OnSize(hWnd, TRUE); //onsize 内含更新 sliders 移动范围的调用。
				}
				break;			
			}
		};
		break;

	case WM_GETMINMAXINFO:
		{
			//设定窗口的最小尺寸为 800 * 600
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

// “关于”框的消息处理程序。
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


//打开一个图片文件时，执行的动作
BOOL OpenPicFile(HWND hWnd, LPCTSTR fname)
{
	HRESULT hr = g_Img.Load(fname);
	if(!SUCCEEDED(hr) || g_Img.IsNull())
	{
		MessageBox(hWnd, _T("打开图片失败！"), MSGBOX_TITLE, MB_ICONWARNING);
		return FALSE;
	}

	if(g_ImgInfo[0].hBitmap != NULL)
		DeleteObject(g_ImgInfo[0].hBitmap);

	if(g_ImgInfo[1].hBitmap != NULL)
		DeleteObject(g_ImgInfo[1].hBitmap);

	g_ImgInfo[0].bmWidth = g_Img.GetWidth();
	g_ImgInfo[0].bmHeight = g_Img.GetHeight();
	g_ImgInfo[0].bpp = g_Img.GetBPP();

	//bottom-up: 所以GetBits（）返回的并不是数据块的头部，而是靠近尾部
	if(g_Img.GetPitch() < 0)
		g_ImgInfo[0].lpBits = g_Img.GetPixelAddress(0, g_Img.GetHeight() - 1);
	else
		g_ImgInfo[0].lpBits = g_Img.GetBits();
	g_ImgInfo[0].hBitmap = g_Img.Detach();

	//
	// 更新视图
	//
	memset(&g_ImgInfo[1], 0, sizeof(IMG_INFO));
	SendMessage(g_hwnds[IDX_VIEW1], WM_SETIMGINFO, 0, (LPARAM)(&g_ImgInfo[0]));
	SendMessage(g_hwnds[IDX_VIEW2], WM_SETIMGINFO, 0, (LPARAM)(&g_ImgInfo[1]));

	//克隆一个相同大小的位图，用于保存高斯模糊的结果
	g_Img.Create(g_ImgInfo[0].bmWidth, g_ImgInfo[0].bmHeight, g_ImgInfo[0].bpp);


	//如果是灰度图像（索引图像），则必须设置调色板
	if(g_ImgInfo[0].bpp == 8)
	{
		//设置颜色板
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

	//更新状态栏
	TCHAR szText[48];
	_stprintf_s(szText, _ARRAYSIZE(szText), _T("图片尺寸: %ld x %ld"), 
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
		_tcscpy_s(pErrMsg, nBufSize, _T("请先打开一个图片！"));
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

		_tcscpy_s(pErrMsg, nBufSize, _T("线程数有效范围：[2, 16];\r\n已插入最接近的数值。"));
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

		_tcscpy_s(pErrMsg, nBufSize, _T("高斯半径有效范围：[0.1, 250.0];\r\n已插入最接近的数值。"));
		MessageBox(hWnd, pErrMsg, MSGBOX_TITLE, MB_ICONWARNING);

		TextBox_SelectAll(g_hwnds[IDX_PANEL], IDC_SIGMA);
		FocusDlgItem(g_hwnds[IDX_PANEL], IDC_SIGMA);

		return TRUE;
	}

	g_pFilters[nFilter]->SetMultiThreads(bMultiThread, nThreadCount);

	DWORD dwTickBegin = GetTickCount();

	//设置高斯半径
	g_pFilters[nFilter]->Init(pInfo[nFilter]);

	g_pFilters[nFilter]->Filter(
		g_ImgInfo[0].lpBits, 
		g_ImgInfo[1].lpBits,
		g_ImgInfo[0].bmWidth, g_ImgInfo[0].bmHeight, g_ImgInfo[0].bpp);

	DWORD dwTickEnd = GetTickCount();

	//更新视图2
	HANDLE hBitmap2 = (HANDLE)SendMessage(g_hwnds[IDX_VIEW2], WM_GETIMGHANDLE, 0, 0);
	if(hBitmap2 == NULL)
		SendMessage(g_hwnds[IDX_VIEW2], WM_SETIMGINFO, 0, (LPARAM)(&g_ImgInfo[1]));
	else
		InvalidateRect(g_hwnds[IDX_VIEW2], NULL, FALSE);

	//更新状态栏的耗时时间
	int msec = dwTickEnd - dwTickBegin;
	_stprintf_s(szText, _ARRAYSIZE(szText), 
		_T("耗时: %ld.%03ld sec"),
		msec / 1000,
		msec - msec / 1000 * 1000);
	UpdateStatusBar(g_hwnds[IDX_STATUSBAR], SBP_TIMESPAN, szText);

	return TRUE;
}

//设置状态栏各个 parts 的位置
void ArrangeStatusBarParts(HWND hStatusBar, int totalWidth)
{
	int i;

	//width[0] 取剩余尺寸；其他 parts 靠右对齐
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
	widths[i] = -1; //最后一项
	SendMessage(hStatusBar, SB_SETPARTS, _ARRAYSIZE(widths), (LPARAM)widths);
}

void UpdateStatusBar(HWND hStatusBar, int iPart, LPCTSTR szText)
{
	SendMessage(hStatusBar, SB_SETTEXT, (WPARAM)(iPart), (LPARAM)(szText));
}

void InitStatusBar(HWND hStatusBar)
{
	//状态栏分组的右边缘坐标。（-1为抵达最边缘）
	RECT rc;
	HWND hwnd = GetParent(hStatusBar);
	GetWindowRect(hwnd, &rc);
	ArrangeStatusBarParts(hStatusBar, rc.right - rc.left);

	//初始化状态栏的固定显示
	TCHAR szText[128];
	_tcscpy_s(szText, _ARRAYSIZE(szText), _T("就绪"));
	UpdateStatusBar(hStatusBar, SBP_STATUS, szText);

	
	_stprintf_s(szText, _ARRAYSIZE(szText), _T("处理器数: %d"),	g_nProcessors);
	UpdateStatusBar(hStatusBar, SBP_PROCESSOR_COUNT, szText);
	UpdateStatusBar(hStatusBar, SBP_TIMESPAN, _T("耗时:"));

	SendMessage(hStatusBar, WM_SIZE, 0, 0);
	ShowWindow(hStatusBar, SW_SHOW);
}

void InitToolBar(HWND hToolBar)
{
	//注意：TBSTYLE_EX_MIXEDBUTTONS 必须创建 ToolBar 之后设置
	//TBSTYLE_EX_DOUBLEBUFFER : 双缓冲
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
		_T("打开图像"), 
		_T("保存处理后的结果图像"), 
		_T("执行高斯模糊"), 
		_T("关于"),
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

//布局子节点
BOOL LayoutChildren(HWND hWnd)
{
	RECT rc;
	GetClientRect(hWnd, &rc);

	//注意程序最小化以后得到的 ClientRect 是 { 0, 0, 0, 0 }, 这时不要理会！！！
	if(IsRectEmpty(&rc))
		return FALSE;

	//toolbar 和 statusbar 不需要布局，只需要指定高度即可！
	int gap = 4; //间隔
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
		//等比缩放
		g_layout.nView1_Width = rc.right * g_layout.nView1_Width / g_layout.nClientWidth;
		g_layout.nClientWidth = rc.right;
		g_rects[index].right = g_rects[index].left + g_layout.nView1_Width;
	}
	g_rects[index].bottom = rc.bottom - g_layout.nPanelHeight - STATUSBAR_HEIGHT;

	//调整View1的位置，如果宽度小于32，则设置其隐藏
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

	//调整 View2 的位置，如果宽度小于32，则将其隐藏
	if(g_rects[index].right - g_rects[index].left <= 32)
	{
		g_rects[index].left = g_rects[index].right;

		//View1 和 Slider 同时被靠右
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

//设置 Sliders 的移动范围
void SetSlidersSpace()
{
	//treeview1 的 最小宽度 是 40 像素
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
// 以下是高斯二维模板可视化相关
//

//动态分配模板，并计算模板的值
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

//以 2KB 为单位写入内存
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

//将二维高斯模板，生成一个可视化的位图，显示在右侧子窗口，或者保存成一个 BMP 位图
//cellSize: 单元格大小
void TemplVisualize(HWND hWnd, double sigma, int cellSize, BOOL bGridLines)
{
	TCHAR szText[512];

	int r = (int)(sigma * 3 + 0.5);
	double *p = GetTempl(sigma, r);

	int row, col;

//输出右下角模板
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
	int bpp = 8; //索引图像
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
	//生成一个位图~。~
	BITMAPFILEHEADER h1 = { 0 };
	BITMAPINFO h2 = { 0 };

	h1.bfType = 0x4D42;
	h1.bfReserved1 = 0;
	h1.bfReserved2 = 0;
	h1.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	//如果bpp=8，则图片具有 256 色调色板
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

	//发送关闭命令（关闭当前打开的图像文件）
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

	//设置lpBits
	LPBYTE lpPixel;
	BYTE gray, clrBorder = 0x9F; //网格边框色
	int subRow, subCol;


	//计算一个放大因子（使得像素变得更亮一些）
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
						lpPixel[subCol] = clrBorder; //网格边界线
					else
						lpPixel[subCol] = gray;
				}				
			}
		}
	}

	//设置最后一行颜色
	row = r * 2 + 1;
	lpPixel = lpBits + row * cellSize * stride;
	for(col = 0; col < width * pixelSize; ++col)
		lpPixel[col] = clrBorder;

	//设置最后一列颜色
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

	//释放模板
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
	
	//释放申请的内存
	free(lpBits);

	_stprintf_s(szText, _ARRAYSIZE(szText), 
		_T("可视化文件已被保存到:\r\n%s"), FNAME_VISUALIZATION);
	MessageBox(hWnd, szText, MSGBOX_TITLE, MB_ICONINFORMATION);

#else
	SendMessage(g_hwnds[IDX_VIEW2], WM_SETIMGINFO, 0, (LPARAM)(&g_ImgInfo[1]));
	_stprintf_s(szText, _ARRAYSIZE(szText), _T("图片尺寸: %ld x %ld"), width, width);
	UpdateStatusBar(g_hwnds[IDX_STATUSBAR], SBP_IMAGESIZE, szText);
	_stprintf_s(szText, _ARRAYSIZE(szText), _T("BPP: %d"), bpp);
	UpdateStatusBar(g_hwnds[IDX_STATUSBAR], SBP_BPP, szText);
#endif

}