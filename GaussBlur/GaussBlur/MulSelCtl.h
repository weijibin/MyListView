#pragma once

#include <windows.h>
#include <commctrl.h> //for HIMAGELIST

// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 MULSELCTL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// MULSELCTL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef MULSELCTL_EXPORTS
#define MULSELCTL_API
#else
#define MULSELCTL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

//指定结构体以 4 Bytes 对齐成员（默认值 = 8 bytes）
//#pragma pack(show)
#pragma pack(push, 4)

//窗口类类名
#define WC_MULSEL						_T("MulSelCtlByHoodlum1980")
#define WC_CLOCK						_T("ClockCtlByHoodlum1980")
#define WC_SLIDER						_T("VBSliderByHoodlum1980")

//默认理想尺寸（如果不对控件内部变量进行修改，则这些就是默认尺寸）
#define DEFAULT_GROUP_GAPH				4
#define DEFAULT_GROUP_GAPV				4
#define DEFAULT_ITEM_GAPH				4
#define DEFAULT_ITEM_GAPV				4
#define DEFAULT_ITEM_WIDTH				48
#define DEFAULT_ITEM_HEIGHT				22
#define DEFAULT_GROUP_LINESIZE			10
//这里指的是 group header's height
#define DEFAULT_GROUP_HEIGHT			24
#define DEFAULT_GROUP_WIDTH				(DEFAULT_ITEM_GAPH \
										+ (DEFAULT_ITEM_WIDTH + DEFAULT_ITEM_GAPH) \
										* DEFAULT_GROUP_LINESIZE)


//
//  控件的理想宽度（保证不出现水平滚动条）：555像素
//
// （1）预留垂直滚动条的宽度，即 GetSystemMetrics(SM_CXVSCROLL);
//
// （2）预留设置了 MSS_BORDER 样式时，窗口在客户区上绘制的深灰色边框，相当于实际视图的
//		尺寸向内缩减一个边框，因此再加 2 个像素。
//

#define DEFAULT_MULSELCTL_WIDTH	\
										(DEFAULT_GROUP_GAP * 2 \
										+ DEFAULT_GROUP_WIDTH \
										+ GetSystemMetrics(SM_CXVSCROLL) \
										+ 2)

//
// 控件的默认配色（可以通过接口改变它们）
//
#define NULL_COLOR							0xFFFFFFFF
#define COLOR_WHITE							RGB(255, 255, 255)
#define COLOR_BLACK							RGB(  0,   0,   0)
#define COLOR_ITEM_CHECKED_BKGND			RGB(255, 200, 128)
#define COLOR_ITEM_UNCHECKED_BKGND			RGB(240, 240, 240)
#define COLOR_ITEM_CHECKED_TEXT				COLOR_BLACK
#define COLOR_ITEM_UNCHECKED_TEXT			RGB(128, 128, 128)
#define COLOR_ITEM_CHECKED_BORDER			COLOR_BLACK
#define COLOR_ITEM_UNCHECKED_BORDER			RGB(128, 128, 128)

#define COLOR_GROUP_HEADER_BKGND			RGB(  0,  64, 128)
#define COLOR_GROUP_TITLE_TEXT				RGB(192, 192, 192)
#define COLOR_GROUP_CLIENT_BKGND			RGB(220, 220, 220)
#define COLOR_GROUP_BORDER					COLOR_BLACK

//
// 以下是 MulSel 的 HitResult
//

#define HIT_NULL				0
#define HIT_BUTTON				1		// Group Header 中的扩展/收缩按钮
#define HIT_CHECKBOX			2		// Group Header 中的 CheckBox
#define HIT_HEADER				3		// Group Header 主体
#define HIT_ITEM				4		// 某个具体的 Item
#define HIT_TITLE				5		// Group Header 中的文本
#define HIT_ICON				6		// Group Header 中的图标

//定义Style
#define MSS_NONE				0x00	//没有任何Style，注意不可以定义为-1（相当于全ON）
#define MSS_FLAT				0x01	//Header上的 checkbox 是否扁平
#define MSS_SHAREIMAGELIST		0x02	//是否不夺取 ImageList 的内存负责职权
#define MSS_SHAREFONT			0x04	//是否不夺取 Font 的内存负责职权
#define MSS_BORDER				0x08	//是否自绘一个深灰色边框线（不依赖控件窗口样式提供边框）
#define MSS_READONLY			0x10	//是否只读（外观和普通一样，但是不接受鼠标操作）


//句柄
typedef LPVOID					HMSGROUP;
typedef LPVOID					HMSITEM;

//
//	mask flags
//

#define MSF_COLOR				0x0001
#define MSF_TEXT_X				0x0002
#define MSF_IMAGE				0x0004
#define MSF_HEADERSIZE			0x0008
#define MSF_LPARAM				0x0010
#define MSF_GAP					0x0020
#define MSF_CHECKSTATE			0x0040
#define MSF_ISCOLLAPSED			0x0080
#define MSF_ITEMCOLORS			0x0100
#define MSF_ITEMSIZE			0x0200
#define MSF_GROUPCOLORS			MSF_COLOR

//指示对外接口使用的文本编码，是否是 Unicode 格式
#define MSF_UNICODE				0x8000

#define MSF_TEXTA				(MSF_TEXT_X)
#define MSF_TEXTW				(MSF_TEXT_X | MSF_UNICODE)

#ifdef _UNICODE
#define MSF_TEXT				MSF_TEXTW
#else
#define MSF_TEXT				MSF_TEXTA
#endif

#define MS_TEXT_BUFSIZE			48

// byWhich 的取值

#define GET_BY_INDEX			0x01
#define GET_BY_TEXT				0x02
#define GET_BY_HANDLE			0x03

typedef struct tagGET_BY
{
	//必须初始化为 MSF_TEXT
	UINT fMask;
	int byWhich;
	BOOL bIgnoreCase; //是否忽略大小写（在使用文本获取时有意义）
	union
	{
		int index;
		HANDLE handle;
		LPCSTR  pTextA;
		LPCWSTR pTextW;
		LPCTSTR pText;
	};
} GETBY, *PGETBY, *LPGETBY;

typedef struct tagGET_ITEM
{
	GETBY group;
	GETBY item;
} GETITEM, *PGETITEM, *LPGETITEM;

typedef struct tagGROUPCOLORS
{
	COLORREF clrTitleText;
	COLORREF clrHeaderBkGnd;
	COLORREF clrClientBkGnd;
	COLORREF clrBorder;
} GROUPCOLORS, *PGROUPCOLORS, *LPGROUPCOLORS;

// item 的配色
typedef struct tagITEMCOLORS
{
	COLORREF clrCheckedText;
	COLORREF clrCheckedBkGnd;
	COLORREF clrUncheckedText;
	COLORREF clrUncheckedBkGnd;
	COLORREF clrCheckedBorder;	//边框颜色
	COLORREF clrUncheckedBorder;
} ITEMCOLORS, *PITEMCOLORS, *LPITEMCOLORS;

//控件内部一律使用 Unicode 编码的文本。对外兼容 Ascii 编码。
typedef struct tagMS_GROUP
{
	UINT fMask;
	HMSGROUP hGroup;
	
	union
	{
		CHAR  TextA[MS_TEXT_BUFSIZE];
		WCHAR TextW[MS_TEXT_BUFSIZE];
		TCHAR Text[MS_TEXT_BUFSIZE];
	};

	//图片索引
	int iImgExpanded;
	int iImgCollapsed;

	int nHeaderHeight;	//Header的高度
	int nGapH;			//子结点布局间距
	int nGapV;
	BOOL bCollapsed;	//是否折叠状态
	int checkState;		//设置时，此值只能是 BST_CHECKED or BST_UNCHECKED;

	//items' size
	int nItemWidth;
	int nItemHeight;

	//group colors
	GROUPCOLORS colors;

	//items' color
	ITEMCOLORS ItemColors;

	//lparam
	LPARAM lParam;
} MSGROUP, *PMSGROUP, *LPMSGROUP;

typedef struct tagMS_ITEM
{
	UINT fMask;
	HMSITEM hItem;
	HMSGROUP hGroup; //此属性，仅用于获取，不能设置
	union
	{
		CHAR  TextA[MS_TEXT_BUFSIZE];
		WCHAR TextW[MS_TEXT_BUFSIZE];
		TCHAR Text[MS_TEXT_BUFSIZE];
	};
	UINT checkState; //只能是 BST_CHECKED or BST_UNCHECKED;
	int iImgChecked;
	int iImgUnchecked;
	LPARAM lParam;
} MSITEM, *PMSITEM, *LPMSITEM;


#define MSI_FIRST			((HANDLE)(ULONG_PTR)-0x0FFFF)
#define MSI_LAST			((HANDLE)(ULONG_PTR)-0x0FFFE)

typedef struct tagMS_INSERTGROUP
{
	HMSGROUP hInsertAfter;
	MSGROUP group;
} MS_INSERTGROUP, *PMS_INSERTGROUP, *LPMS_INSERTGROUP;

//用于 insert item 的数据结构
typedef struct tagMS_INSERTITEM
{
	HMSGROUP hGroup;
	HMSITEM hInsertAfter;
	MSITEM item;
} MS_INSERTITEM, *PMS_INSERTITEM, *LPMS_INSERTITEM;

//提供获取选中的 items 的文本缓冲区
typedef struct tagGET_CHECKED_ITEMS
{
	//必须把 fMask 赋值为 MSF_TEXT
	UINT fMask;
	union
	{
		LPSTR  pBufOrFilenameA;
		LPWSTR pBufOrFilenameW;
		LPTSTR pBufOrFilename;
	};

	// buffer size in chars (NOT BYTES) including null-terminator;
	int cchMax;
	UINT state;
	int itemCount;

	//分隔符字符
	int cSeperator;
} GETCHECKEDITEMS, *PGETCHECKEDITEMS, *LPGETCHECKEDITEMS;

//LayoutInfo (主要是水平方向的设定，可以在添加 groups / items 之前进行统一设定)
typedef struct tagMS_LAYOUTINFO
{
	int nLineSize; //每一行容纳的 Items 个数
	
	int nItemWidth;
	int nItemHeight;
	
	int nItemGapH;
	int nItemGapV;

	int nGroupGapH;
	int nGroupGapV;

	int nGroupHeaderHeight;
} MSLAYOUTINFO, *PMSLAYOUTINFO, *LPMSLAYOUTINFO;

//动画信息 (此动画信息主要是关于展开和折叠 group 的)
typedef struct tagANIMATION_INFO
{
	BOOL bEnabled;	//是否允许动画
	int nFrameTime; //每帧动画持续时间
	int dy;			//每帧动画的 group 高度变化值
} ANIMATION_INFO, *PANIMATION_INFO, *LPANIMATION_INFO;

// HitTest 返回信息
typedef struct tagHITINFO
{
	int x;
	int y;
	int nHit;			//击中了什么元素
	HMSGROUP hGroup;	//击中元素所在的 Group
	HMSITEM hItem;
} HITINFO, *PHITINFO, *LPHITINFO;

typedef struct tagFRAMEINFO
{
	int count;			//总帧数( <=16 )
	char seq[16];		//每一帧的 ImageIndex 的字符形式（ImageIndex + '0') 
	int time[16];		//帧持续时间（毫秒为单位），最后一帧的时间没有意义
} FRAMEINFO, *PFRAMEINFO, *LPFRAMEINFO;

//
// 定义旋转按钮的动画信息
//
typedef struct tagBUTTONINFO
{
	HBITMAP hBitmap;					//旋转按钮动画的帧
	int nBpp;							//当 Bpp = 24 时，采用 TransparentBlt，= 32 时，采用 AlphaBlend
	BOOL bPreMultiplied;				//当 Bpp = 32 时，RGB 通道是否已经预先乘过 Alpha 通道
	COLORREF clrTransparent;			//当 Bpp = 24 时，透明色
	BOOL bShared;						//是否共享（若为 TRUE，控件销毁时，不会销毁 hBitmap）
	BOOL bLTR;							//图片帧是否是从左向右排列（如果为 FALSE，则图片帧从上到下排列）
	int nFrameWidth;
	int nFrameHeight;
	FRAMEINFO expanding;
	FRAMEINFO collapsing;
} BUTTONINFO, *PBUTTONINFO, *LPBUTTONINFO;

//对外消息接口
#define MSM_CLEARDATA					(WM_USER + 100)
#define MSM_INSERTGROUP					(WM_USER + 101)
#define MSM_INSERTITEM					(WM_USER + 102)
#define MSM_GETCHECKEDITEMS				(WM_USER + 103) //把已经勾选的items填写到缓冲区
#define MSM_SETGROUP					(WM_USER + 104)
#define MSM_SETITEM						(WM_USER + 105)
#define MSM_SERIALIZE					(WM_USER + 106)
#define MSM_DESERIALIZE					(WM_USER + 107)
#define MSM_SUSPENDLAYOUT				(WM_USER + 108) //暂时冻结布局，在此期间添加节点，控件不会尝试重绘
//#define MSM_RESUMELAYOUT				(WM_USER + 109) //结束冻结布局，此时控件开始更新 (obsolete)
#define MSM_SETCHECKSTATE				(WM_USER + 110) //全部选择/不选
#define MSM_REVERSEALL					(WM_USER + 111) //全部反选
// -----------------
// [message id gap]
// -----------------
#define MSM_GETGROUPWIDTH				(WM_USER + 115) //获取 Group width
#define MSM_GETGROUPCHECKEDITEMSCOUNT	(WM_USER + 116) //获取某个 group 的 checked items count
#define MSM_GETCHECKEDITEMSCOUNT		(WM_USER + 117) //获取所有的 checked items count
#define MSM_SERIALIZE_MEM				(WM_USER + 118) //把自身反序列化到指定的内存中
#define MSM_DESERIALIZE_MEM				(WM_USER + 119) //从一段内存中反序列化自身数据
#define MSM_GETGROUPHANDLE				(WM_USER + 120) //获取某个 Group 的句柄
#define MSM_GETITEMHANDLE				(WM_USER + 121)	//获取某个 Item  的句柄
#define MSM_GETGROUPSCOUNT				(WM_USER + 122) //获取 Groups Count
#define MSM_GETGROUPITEMSCOUNT			(WM_USER + 123) //获取某个 Group 的 ItemsCount
#define MSM_GETTOTALITEMSCOUNT			(WM_USER + 124) //获取总的 ItemsCount
#define MSM_GETGROUP					(WM_USER + 125) //获取 Group 信息
#define MSM_GETITEM						(WM_USER + 126) //获取 Item  信息
#define MSM_GETSTYLE					(WM_USER + 127) //获取内置 Style 信息（不是窗口样式！）
#define MSM_SETSTYLE					(WM_USER + 128) //设置总体 Style
#define MSM_SETONESTYLE					(WM_USER + 129) //设置单个 Style 的状态
#define MSM_GETBKGNDCOLOR				(WM_USER + 130) //获取控件背景色
#define MSM_SETBKGNDCOLOR				(WM_USER + 131) //设置控件背景色
#define MSM_GETIMAGELIST				(WM_USER + 132) //获取控件的 ImageList
#define MSM_SETIMAGELIST				(WM_USER + 133)	//设置控件的 ImageList
#define MSM_GETFONT						(WM_USER + 134) //不能用WM_GETFONT，和 WM_SETFONT 代替，原因不详
#define MSM_SETFONT						(WM_USER + 135) //否则会导致对话框上其他控件字体都变为System字体
#define MSM_SETGROUPSIMAGE				(WM_USER + 136) //设置所有 Groups 的Image
#define MSM_GETCHECKSTATE				(WM_USER + 137) //获取当前控件的选中状态
#define MSM_SETGROUPWIDTH				(WM_USER + 138) //重设Group宽度（可能导致整体重新布局）
#define MSM_SETITEMSSIZE				(WM_USER + 139) //重设Item尺寸（可能导致整体重新布局）
#define MSM_GROUPCLEAR					(WM_USER + 140) //把某个 Group 的 Items 清空
#define MSM_DELETEGROUP					(WM_USER + 141) //删除某个 Group
#define MSM_DELETEITEM					(WM_USER + 142) //删除某个 Item
#define MSM_GETLAYOUTINFO				(WM_USER + 143) //获取默认布局信息
#define MSM_SETLAYOUTINFO				(WM_USER + 144) //设置默认布局信息
#define MSM_LAYOUTBYLINESIZE			(WM_USER + 145) //根据窗口宽度和 LineSize 重新设置布局
#define MSM_CLICKCHECKBOX				(WM_USER + 146) //用户点击“总的 checkbox”
#define MSM_GETANIMATIONINFO			(WM_USER + 147) //获取动画信息
#define MSM_SETANIMATIONINFO			(WM_USER + 148) //设置动画信息
#define MSM_REFRESHCHECKSTATE			(WM_USER + 149) //更新控件内部维护的 CheckState 状态（不会更新视图）
#define MSM_HITTEST						(WM_USER + 150) //点击测试
#define MSM_SETBUTTONINFO				(WM_USER + 151) //设置 ButtonInfo
#define MSM_GETGROUPCOLORS				(WM_USER + 152) //获取默认的 GroupColors（而不是具体的某个 Group）
#define MSM_SETGROUPCOLORS				(WM_USER + 153) //设置默认的 GroupColors（并重设当前的所有 Group color）
#define MSM_GETITEMCOLORS				(WM_USER + 154) //获取默认的 ItemColors （而不是具体的某个 Item）
#define MSM_SETITEMCOLORS				(WM_USER + 155) //设置默认的 ItemColors （并重设当前所有的 Item color）

typedef struct tagNM_MULSEL_HDR
{
	HWND hwndFrom;
	UINT idFrom;
	UINT code;
	HMSGROUP hGroup;			//事件的 Group
	HMSITEM	hItem;				//事件的 Item
	UINT oldState;				//checkState
	UINT newState;
} NMMSHDR, *LPNMMSHDR;

//
// Notify Codes
//
#define MSN_CHECKSTATECHANGE	1 //总的 CheckBox 的勾选状态已发生变化
#define MSN_GROUPEXPAND			2 //暂未启用
#define MSN_GROUPEXPANDING		3 //暂未启用
#define MSN_GROUPCOLLAPSE		4 //暂未启用
#define MSN_GROUPCOLLAPSING		5 //暂未启用
#define MSN_CHECKEDITEMSCHANGE	6 //所有选中的 Items 内容发生变化


//消息宏
#define MulSel_Clear(hCtl, bNotify, bRedraw) \
	SendMessage((hCtl), MSM_CLEARDATA, MAKEWPARAM((bRedraw), (bNotify)), 0)

#define MulSel_InsertGroup(hCtl, lpmsi, bNotify, bRedraw) \
	(HMSGROUP)(SendMessage((hCtl), MSM_INSERTGROUP, MAKEWPARAM((bRedraw), (bNotify)), (LPARAM)(lpmsi)))

#define MulSel_GetGroupHandle(hCtl, pGetItem) \
	(HMSGROUP)(SendMessage((hCtl), MSM_GETGROUPHANDLE, 0, (LPARAM)(pGetItem)))

#define MulSel_InsertItem(hCtl, lpmsi, bNotify, bRedraw) \
	SendMessage((hCtl), MSM_INSERTITEM, MAKEWPARAM((bRedraw), (bNotify)), (LPARAM)(lpmsi))

#define MulSel_GetItemHandle(hCtl, pGetItem) \
	(HMSITEM)(SendMessage((hCtl), MSM_GETITEMHANDLE, 0, (LPARAM)(pGetItem)))

#define MulSel_GetCheckedItems(hCtl, pGetCheckedItems) \
	SendMessage((hCtl), MSM_GETCHECKEDITEMS, 0, (LPARAM)(pGetCheckedItems))

#define MulSel_SuspendLayout(hCtl, bSuspend) \
	SendMessage((hCtl), MSM_SUSPENDLAYOUT, (WPARAM)(bSuspend), 0)

#define MulSel_SetCheckState(hCtl, state, bNotify, bRedraw) \
	SendMessage((hCtl), MSM_SETCHECKSTATE, MAKEWPARAM((bRedraw), (bNotify)), (LPARAM)(state))

#define MulSel_ReverseAll(hCtl, bRedraw) \
	SendMessage((hCtl), MSM_REVERSEALL, MAKEWPARAM((bRedraw), 0), 0)

#define MulSel_GetGroup(hCtl, pGroupInfo) \
	SendMessage((hCtl), MSM_GETGROUP, 0, (LPARAM)(pGroupInfo))

#define MulSel_SetGroup(hCtl, pGroupInfo, bNotify, bRedraw) \
	SendMessage((hCtl), MSM_SETGROUP, MAKEWPARAM((bRedraw), (bNotify)), (LPARAM)(pGroupInfo))

#define MulSel_GetItem(hCtl, hItemInfo) \
	SendMessage((hCtl), MSM_GETITEM, 0, (LPARAM)(pItemInfo))

#define MulSel_SetItem(hCtl, pItemInfo, bNotify, bRedraw) \
	SendMessage((hCtl), MSM_SETITEM, MAKEWPARAM((bRedraw), (bNotify)), (LPARAM)(pItemInfo))

#define MulSel_Serialize(hCtl, pBufInfo) \
	SendMessage((hCtl), MSM_SERIALIZE, 0, (LPARAM)(pBufInfo))

#define MulSel_Deserialize(hCtl, pBufInfo, bNotify, bRedraw) \
	SendMessage((hCtl), MSM_DESERIALIZE, MAKEWPARAM((bRedraw), (bNotify)), (LPARAM)(pBufInfo))

#define MulSel_SerializeToMem(hCtl, pBufInfo) \
	SendMessage((hCtl), MSM_SERIALIZE_MEM, 0, (LPARAM)(pBufInfo))

#define MulSel_DeserializeFromMem(hCtl, pBufInfo, bNotify, bRedraw) \
	SendMessage((hCtl), MSM_DESERIALIZE_MEM, MAKEWPARAM((bRedraw), (bNotify)), (LPARAM)(pBufInfo))

#define MulSel_GetStyle(hCtl) \
	((int)SendMessage((hCtl), MSM_GETSTYLE, 0, 0))

#define MulSel_SetStyle(hCtl, style, bRedraw) \
	((int)SendMessage((hCtl), MSM_SETSTYLE, MAKEWPARAM((bRedraw), 0), (LPARAM)(style)))

#define MulSel_SetOneStyle(hCtl, style, bOn, bRedraw) \
	((int)SendMessage((hCtl), MSM_SETONESTYLE, MAKEWPARAM((bRedraw), (bOn)), (LPARAM)(style)))

#define MulSel_GetBkColor(hCtl) \
	((COLORREF)SendMessage((hCtl), MSM_GETBKGNDCOLOR, 0, 0))

#define MulSel_SetBkColor(hCtl, clrBkColor, bRedraw) \
	SendMessage((hCtl), MSM_SETBKGNDCOLOR, MAKEWPARAM((bRedraw), 0), (LPARAM)(clrBkColor))

#define MulSel_GetImageList(hCtl) \
	((HIMAGELIST)SendMessage((hCtl), MSM_GETIMAGELIST, 0, 0))

#define MulSel_SetImageList(hCtl, hImgList, bRedraw) \
	((HIMAGELIST)SendMessage((hCtl), MSM_SETIMAGELIST, MAKEWPARAM((bRedraw), 0), (LPARAM)(hImgList)))

#define MulSel_GetFont(hCtl) \
	((HFONT)SendMessage((hCtl), MSM_GETFONT, 0, 0))

#define MulSel_SetFont(hCtl, hFont, bRedraw) \
	((HFONT)SendMessage((hCtl), MSM_SETFONT, MAKEWPARAM((bRedraw), 0), (LPARAM)(hFont)))

//
// 获取个数
//

#define MulSel_GetTotalItemsCount(hCtl) \
	((int)SendMessage((hCtl), MSM_GETTOTALITEMSCOUNT, 0, 0))

#define MulSel_GetCheckedItemsCount(hCtl) \
	((int)SendMessage((hCtl), MSM_GETCHECKEDITEMSCOUNT, 0, 0))

#define MulSel_GetGroupsCount(hCtl) \
	((int)SendMessage((hCtl), MSM_GETGROUPSCOUNT, 0, 0))

#define MulSel_GetGroupItemsCount(hCtl, hGroup) \
	((int)SendMessage((hCtl), MSM_GETGROUPITEMSCOUNT, 0, (LPARAM)(hGroup)))

#define MulSel_GetGroupCheckedItemsCount(hCtl) \
	((int)SendMessage((hCtl), MSM_GETGROUPCHECKEDITEMSCOUNT, 0, (LPARAM)(hGroup)))

//
//
//

#define MulSel_SetGroupImage(hCtl, index1, index2, bRedraw) \
	SendMessage((hCtl), MSM_SETGROUPIMAGE, MAKEWPARAM((bRedraw), 0), (LPARAM)MAKELONG((index1), (index2)))

#define MulSel_GetCheckState(hCtl) \
	(UINT)(SendMessage((hCtl), MSM_GETCHECKSTATE, 0, 0))

#define MulSel_SetGroupWidth(hCtl, newWidth, bRedraw) \
	SendMessage((hCtl), MSM_SETGROUPWIDTH, MAKEWPARAM((bRedraw), 0), (LPARAM)MAKELONG((newWidth), 0))

#define MulSel_GetGroupWidth(hCtl) \
	SendMessage((hCtl), MSM_GETGROUPWIDTH, 0, 0)

#define MulSel_SetItemSize(hCtl, newWidth, newHeight, bRedraw) \
	SendMessage((hCtl), MSM_SETITEMSIZE, MAKEWPARAM((bRedraw), 0), (LPARAM)MAKELONG((newWidth), (newHeight)))


//
// 设置只读属性（非专有消息）
//
#define MulSel_SetReadOnly(hCtl, bReadOnly) \
	MulSel_SetOneStyle(hCtl, MSS_READONLY, bReadOnly, FALSE)

//
// pLayoutInfo 是一种默认信息，用户依然可以对 Group 指定自定义的布局信息。
//

#define MulSel_GetLayoutInfo(hCtl, pLayout) \
	SendMessage((hCtl), MSM_GETLAYOUTINFO, 0, (LPARAM)(pLayout))

#define MulSel_SetLayoutInfo(hCtl, pLayout, bRedraw) \
	SendMessage((hCtl), MSM_SETLAYOUTINFO, MAKEWPARAM((bRedraw), 0), (LPARAM)(pLayout))

//
// 适用于调整空间宽度时，发送此消息。当 nLineSize <= 0 时，
// 则使用当前的 nLineSize 扩展 item 宽度
//
#define MulSel_LayoutByLineSize(hCtl, nLineSize, bResizeItems, bRedraw) \
	SendMessage((hCtl), MSM_LAYOUTBYLINESIZE, MAKEWPARAM((bRedraw), 0), (LPARAM)MAKELONG(nLineSize, bResizeItems))


#define MulSel_GroupClear(hCtl, hGroup, bNotify, bRedraw) \
	SendMessage((hCtl), MSM_GROUPCLEAR, MAKEWPARAM((bRedraw), (bNotify)), (LPARAM)(hGroup))

//
// 删除 group / item
//

#define MulSel_DeleteGroup(hCtl, hGroup, bNotify, bRedraw) \
	SendMessage((hCtl), MSM_DELETEGROUP, MAKEWPARAM((bRedraw), (bNotify)), (LPARAM)(hGroup))

#define MulSel_DeleteItem(hCtl, hItem, bNotify, bRedraw) \
	SendMessage((hCtl), MSM_DELETEITEM, MAKEWPARAM((bRedraw), (bNotify)), (LPARAM)(hItem))


// 用户点击“总的”CheckBox
// bNotify: 是否向父窗口发送 WM_NOTIFY 通知
// bRedraw: 是否更新控件的视图

#define MulSel_ClickCheckBox(hCtl, bNotify, bRedraw) \
	SendMessage((hCtl), MSM_CLICKCHECKBOX, MAKEWPARAM((bRedraw), (bNotify)), 0)

//
// 获取/设置动画信息
//

#define MulSel_GetAnimationInfo(hCtl, pInfo) \
	SendMessage((hCtl), MSM_GETANIMATIONINFO, 0, (LPARAM)(pInfo))

#define MulSel_SetAnimationInfo(hCtl, pInfo) \
	SendMessage((hCtl), MSM_SETANIMATIONINFO, 0, (LPARAM)(pInfo))


//
// 刷新控件内部维护的状态（不会更新视图），如果在添加和修改子节点过程中，
// bNotify 传为 FALSE，则控件内部状态可能无法准确跟踪用户对控件的修改，
// 调用此消息后，将会将控件内部的 CheckState 状态重新设定为正确状态。
//

#define MulSel_RefreshCheckState(hCtl) \
	SendMessage((hCtl), MSM_REFRESHCHECKSTATE, 0, 0)


//
// 点击测试
//

#define MulSel_HitTest(hCtl, pHitInfo) \
	SendMessage((hCtl), MSM_HITTEST, 0, (LPARAM)(pHitInfo))


//
// 设置旋转按钮信息(动画)
//

#define MulSel_SetButtonInfo(hCtl, pBtnInfo, bRedraw) \
	SendMessage((hCtl), MSM_SETBUTTONINFO, MAKEWPARAM((bRedraw), 0), (LPARAM)(pBtnInfo))


//
// 获取和设置默认颜色
//

#define MulSel_GetGroupColors(hCtl, pGroupColors) \
	SendMessage((hCtl), MSM_GETGROUPCOLORS, 0, (LPARAM)(pGroupColors))

#define MulSel_SetGroupColors(hCtl, pGroupColors, bRedraw) \
	SendMessage((hCtl), MSM_SETGROUPCOLORS, MAKEWPARAM((bRedraw), 0), (LPARAM)(pGroupColors))

#define MulSel_GetItemColors(hCtl, pItemColors) \
	SendMessage((hCtl), MSM_GETITEMCOLORS, 0, (LPARAM)(pItemColors))

#define MulSel_SetItemColors(hCtl, pItemColors, bRedraw) \
	SendMessage((hCtl), MSM_SETITEMCOLORS, MAKEWPARAM((bRedraw), 0), (LPARAM)(pItemColors))

//
// ------------------------------------------------------------------------------------
//
//
// 以下是 ClockCtrl
//

//HIT_NULL 已经在前面定义

#define HIT_HOURPTR			1 //击中时针
#define HIT_MINUTEPTR		2 //击中分针
#define HIT_CLOCKCENTER		3 //击中时钟的中心，此时不做响应！

typedef struct _CLOCKTIME
{
	BYTE hour;
	BYTE minute;
} CLOCKTIME, *PCLOCKTIME;

//
// ClockCtl Message
//

#define CLM_SETTIME			(WM_USER + 300)
#define CLM_GETTIME			(WM_USER + 301)
#define CLM_GETMINUTEUNIT	(WM_USER + 302)
#define CLM_SETMINUTEUNIT	(WM_USER + 303)
#define CLM_GETSTYLE		(WM_USER + 304)
#define CLM_SETSTYLE		(WM_USER + 305)
#define CLM_GETHITERRBUFFER	(WM_USER + 306)
#define CLM_SETHITERRBUFFER	(WM_USER + 307)
#define CLM_SETONESTYLE		(WM_USER + 308)

typedef struct _NM_CLOCK_HDR
{
	HWND hwndFrom;
	UINT idFrom;
	UINT code;
	int hour;		//时间改变后的小时
	int minute;		//时间改变后的分钟
} NMCLHDR, *LPNMCLHDR;
//
// ClockCtl Notify Codes
//
#define CLN_TIMECHANGE		1

//
// Macros
//
#define Clock_SetTime(hCtl, pTime, bRedraw) \
	SendMessage((hCtl), CLM_SETTIME, MAKEWPARAM((bRedraw), 0), (LPARAM)(pTime))

#define Clock_GetTime(hCtl, pTime) \
	SendMessage((hCtl), CLM_GETTIME, 0, (LPARAM)(pTime))

//获取和设置拖动指针时的最小单位（默认为5分钟）
#define Clock_GetMinuteUnit(hCtl) \
	((int)SendMessage((hCtl), CLM_GETMINUTEUNIT, 0, 0))

#define Clock_SetMinuteUnit(hCtl, nUnit) \
	((int)SendMessage((hCtl), CLM_SETMINUTEUNIT, (WPARAM)(nUnit), 0))

#define Clock_SetStyle(hCtl, style, bRedraw) \
	SendMessage((hCtl), CLM_SETSTYLE, MAKEWPARAM((bRedraw), 0), (LPARAM)(style)))

#define Clock_GetStyle(hCtl) \
	((UNIT)SendMessage((hCtl), CLM_GETSTYLE, 0, 0))

//获取和设置点击测试时的误差缓冲（单位为分钟数，默认为5分钟）
#define Clock_GetHitErrBuffer(hCtl) \
	((int)SendMessage((hCtl), CLM_GETHITERRBUFFER, 0, 0))

#define Clock_SetHitErrBuffer(hCtl, nBufMinutes) \
	((int)SendMessage((hCtl), CLM_SETHITERRBUFFER, (WPARAM)(nBufMinutes), 0))

#define Clock_SetOneStyle(hCtl, style, bOn, bRedraw) \
	((int)SendMessage((hCtl), CLM_SETONESTYLE, MAKEWPARAM((bRedraw), (bOn)), (LPARAM)(style)))

#define Clock_SetReadOnly(hCtl, bReadOnly)\
	Clock_SetOneStyle((hCtl), MSS_READONLY, (WPARAM)(bReadOnly), FALSE)

//
// slider 的方向
//

#define DIRECTION_V			0 //垂直竖线
#define DIRECTION_H			1 //水平线


//
// Message
//

#define SLSPACE_TL			0x01	//Top or Left;
#define SLSPACE_BR			0x02	//Bottom or Right;
#define SLSPACE_BOTH		(SLSPACE_TL | SLSPACE_BR)

//
// SLM_SETSPACE : 设置两侧边距 
// 
// wParam: flags; which space
// lParam: HIWORD top-left Space, LOWORD: bottom-right Space;
// Return: 
			
#define SLM_SETSPACE			(WM_USER + 300)

//
// SLM_GETSPACE :
// 
// wParam:
// lParam:
// Return: HIWORD top-left Space, LOWORD: bottom-right Space;

#define SLM_GETSPACE			(WM_USER + 301)

//
// SLM_SETDIRECTION : 设置方向
// 
// wParam: direction
// lParam: 
// Return: 
			
#define SLM_SETDIRECTION		(WM_USER + 302)

//
// SLM_GETDIRECTION :
// 
// wParam: 
// lParam: 
// Return: direction
			
#define SLM_GETDIRECTION		(WM_USER + 303)



typedef struct _NM_SLIDER_HDR
{
	HWND hwndFrom;
	UINT idFrom;
	UINT code;
	int diff;		//拖动距离（可正可负）
} NMSLHDR, *LPNMSLHDR;

//
// Notify Codes
//
#define SLN_DROPDOWN		1

//
// Macros:
//
//
// SLM_SETSPACE : 设置两侧边距 
// 
// wParam: flags; which space
// lParam: HIWORD top-left Space, LOWORD: bottom-right Space;
// Return: 
#define Slider_SetSpace(hCtl, flags, nSpaceTL, nSpaceBR) \
	SendMessage((hCtl), SLM_SETSPACE, (WPARAM)(flags), MAKELPARAM((nSpaceBR), (nSpaceTL)))

#define Slider_GetSpace(hCtl) \
	((int)SendMessage((hCtl), SLM_GETSPACE, 0, 0))

//
// SLM_SETDIRECTION : 设置方向
// 
// wParam: direction
// lParam: 
// Return: 
			
#define Slider_SetDirection(hCtl, direction) \
	SendMessage((hCtl), SLM_SETDIRECTION, (WPARAM)(direction), 0)

//
// SLM_GETDIRECTION :
// 
// wParam: 
// lParam: 
// Return: direction
			
#define Slider_GetDirection(hCtl) \
	((int)SendMessage((hCtl), SLM_GETDIRECTION, 0, 0))


//
// 导出函数/
//

#define IMSC_MULSEL			0x00000001
#define IMSC_CLOCK			0x00000002
#define IMSC_SLIDER			0x00000004

BOOL MULSELCTL_API InitMulSelControls(UINT nIMSC);
ATOM MULSELCTL_API GetClassAtom(UINT nWhichClass);
//获得理想的多选控件宽度（高度随意）
int MULSELCTL_API GetIdealMulSelCtlWidth(LPMSLAYOUTINFO pLayout);

//获取和 slider 相关的控件内置光标句柄
HCURSOR MULSELCTL_API GetSliderCursor(UINT direction);

//
// 在 Unicode 和 ANSI（char*）之间互转
//
int MULSELCTL_API UnicodeToAnsi(LPCWSTR lpWideCharStr, LPSTR lpMultiByteStr, int cbMultiByte);
int MULSELCTL_API AnsiToUnicode(LPCSTR lpMultiByteStr, LPWSTR lpWideCharStr, int cchWideChar);

//恢复对齐的默认值（8 bytes）
#pragma pack(pop)
//#pragma pack(show)

#ifdef __cplusplus
} //__END_OF_ extern "C" {}
#endif