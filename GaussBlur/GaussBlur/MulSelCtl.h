#pragma once

#include <windows.h>
#include <commctrl.h> //for HIMAGELIST

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MULSELCTL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MULSELCTL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef MULSELCTL_EXPORTS
#define MULSELCTL_API
#else
#define MULSELCTL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

//ָ���ṹ���� 4 Bytes �����Ա��Ĭ��ֵ = 8 bytes��
//#pragma pack(show)
#pragma pack(push, 4)

//����������
#define WC_MULSEL						_T("MulSelCtlByHoodlum1980")
#define WC_CLOCK						_T("ClockCtlByHoodlum1980")
#define WC_SLIDER						_T("VBSliderByHoodlum1980")

//Ĭ������ߴ磨������Կؼ��ڲ����������޸ģ�����Щ����Ĭ�ϳߴ磩
#define DEFAULT_GROUP_GAPH				4
#define DEFAULT_GROUP_GAPV				4
#define DEFAULT_ITEM_GAPH				4
#define DEFAULT_ITEM_GAPV				4
#define DEFAULT_ITEM_WIDTH				48
#define DEFAULT_ITEM_HEIGHT				22
#define DEFAULT_GROUP_LINESIZE			10
//����ָ���� group header's height
#define DEFAULT_GROUP_HEIGHT			24
#define DEFAULT_GROUP_WIDTH				(DEFAULT_ITEM_GAPH \
										+ (DEFAULT_ITEM_WIDTH + DEFAULT_ITEM_GAPH) \
										* DEFAULT_GROUP_LINESIZE)


//
//  �ؼ��������ȣ���֤������ˮƽ����������555����
//
// ��1��Ԥ����ֱ�������Ŀ�ȣ��� GetSystemMetrics(SM_CXVSCROLL);
//
// ��2��Ԥ�������� MSS_BORDER ��ʽʱ�������ڿͻ����ϻ��Ƶ����ɫ�߿��൱��ʵ����ͼ��
//		�ߴ���������һ���߿�����ټ� 2 �����ء�
//

#define DEFAULT_MULSELCTL_WIDTH	\
										(DEFAULT_GROUP_GAP * 2 \
										+ DEFAULT_GROUP_WIDTH \
										+ GetSystemMetrics(SM_CXVSCROLL) \
										+ 2)

//
// �ؼ���Ĭ����ɫ������ͨ���ӿڸı����ǣ�
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
// ������ MulSel �� HitResult
//

#define HIT_NULL				0
#define HIT_BUTTON				1		// Group Header �е���չ/������ť
#define HIT_CHECKBOX			2		// Group Header �е� CheckBox
#define HIT_HEADER				3		// Group Header ����
#define HIT_ITEM				4		// ĳ������� Item
#define HIT_TITLE				5		// Group Header �е��ı�
#define HIT_ICON				6		// Group Header �е�ͼ��

//����Style
#define MSS_NONE				0x00	//û���κ�Style��ע�ⲻ���Զ���Ϊ-1���൱��ȫON��
#define MSS_FLAT				0x01	//Header�ϵ� checkbox �Ƿ��ƽ
#define MSS_SHAREIMAGELIST		0x02	//�Ƿ񲻶�ȡ ImageList ���ڴ渺��ְȨ
#define MSS_SHAREFONT			0x04	//�Ƿ񲻶�ȡ Font ���ڴ渺��ְȨ
#define MSS_BORDER				0x08	//�Ƿ��Ի�һ�����ɫ�߿��ߣ��������ؼ�������ʽ�ṩ�߿�
#define MSS_READONLY			0x10	//�Ƿ�ֻ������ۺ���ͨһ�������ǲ�������������


//���
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

//ָʾ����ӿ�ʹ�õ��ı����룬�Ƿ��� Unicode ��ʽ
#define MSF_UNICODE				0x8000

#define MSF_TEXTA				(MSF_TEXT_X)
#define MSF_TEXTW				(MSF_TEXT_X | MSF_UNICODE)

#ifdef _UNICODE
#define MSF_TEXT				MSF_TEXTW
#else
#define MSF_TEXT				MSF_TEXTA
#endif

#define MS_TEXT_BUFSIZE			48

// byWhich ��ȡֵ

#define GET_BY_INDEX			0x01
#define GET_BY_TEXT				0x02
#define GET_BY_HANDLE			0x03

typedef struct tagGET_BY
{
	//�����ʼ��Ϊ MSF_TEXT
	UINT fMask;
	int byWhich;
	BOOL bIgnoreCase; //�Ƿ���Դ�Сд����ʹ���ı���ȡʱ�����壩
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

// item ����ɫ
typedef struct tagITEMCOLORS
{
	COLORREF clrCheckedText;
	COLORREF clrCheckedBkGnd;
	COLORREF clrUncheckedText;
	COLORREF clrUncheckedBkGnd;
	COLORREF clrCheckedBorder;	//�߿���ɫ
	COLORREF clrUncheckedBorder;
} ITEMCOLORS, *PITEMCOLORS, *LPITEMCOLORS;

//�ؼ��ڲ�һ��ʹ�� Unicode ������ı���������� Ascii ���롣
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

	//ͼƬ����
	int iImgExpanded;
	int iImgCollapsed;

	int nHeaderHeight;	//Header�ĸ߶�
	int nGapH;			//�ӽ�㲼�ּ��
	int nGapV;
	BOOL bCollapsed;	//�Ƿ��۵�״̬
	int checkState;		//����ʱ����ֵֻ���� BST_CHECKED or BST_UNCHECKED;

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
	HMSGROUP hGroup; //�����ԣ������ڻ�ȡ����������
	union
	{
		CHAR  TextA[MS_TEXT_BUFSIZE];
		WCHAR TextW[MS_TEXT_BUFSIZE];
		TCHAR Text[MS_TEXT_BUFSIZE];
	};
	UINT checkState; //ֻ���� BST_CHECKED or BST_UNCHECKED;
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

//���� insert item �����ݽṹ
typedef struct tagMS_INSERTITEM
{
	HMSGROUP hGroup;
	HMSITEM hInsertAfter;
	MSITEM item;
} MS_INSERTITEM, *PMS_INSERTITEM, *LPMS_INSERTITEM;

//�ṩ��ȡѡ�е� items ���ı�������
typedef struct tagGET_CHECKED_ITEMS
{
	//����� fMask ��ֵΪ MSF_TEXT
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

	//�ָ����ַ�
	int cSeperator;
} GETCHECKEDITEMS, *PGETCHECKEDITEMS, *LPGETCHECKEDITEMS;

//LayoutInfo (��Ҫ��ˮƽ������趨����������� groups / items ֮ǰ����ͳһ�趨)
typedef struct tagMS_LAYOUTINFO
{
	int nLineSize; //ÿһ�����ɵ� Items ����
	
	int nItemWidth;
	int nItemHeight;
	
	int nItemGapH;
	int nItemGapV;

	int nGroupGapH;
	int nGroupGapV;

	int nGroupHeaderHeight;
} MSLAYOUTINFO, *PMSLAYOUTINFO, *LPMSLAYOUTINFO;

//������Ϣ (�˶�����Ϣ��Ҫ�ǹ���չ�����۵� group ��)
typedef struct tagANIMATION_INFO
{
	BOOL bEnabled;	//�Ƿ�������
	int nFrameTime; //ÿ֡��������ʱ��
	int dy;			//ÿ֡������ group �߶ȱ仯ֵ
} ANIMATION_INFO, *PANIMATION_INFO, *LPANIMATION_INFO;

// HitTest ������Ϣ
typedef struct tagHITINFO
{
	int x;
	int y;
	int nHit;			//������ʲôԪ��
	HMSGROUP hGroup;	//����Ԫ�����ڵ� Group
	HMSITEM hItem;
} HITINFO, *PHITINFO, *LPHITINFO;

typedef struct tagFRAMEINFO
{
	int count;			//��֡��( <=16 )
	char seq[16];		//ÿһ֡�� ImageIndex ���ַ���ʽ��ImageIndex + '0') 
	int time[16];		//֡����ʱ�䣨����Ϊ��λ�������һ֡��ʱ��û������
} FRAMEINFO, *PFRAMEINFO, *LPFRAMEINFO;

//
// ������ת��ť�Ķ�����Ϣ
//
typedef struct tagBUTTONINFO
{
	HBITMAP hBitmap;					//��ת��ť������֡
	int nBpp;							//�� Bpp = 24 ʱ������ TransparentBlt��= 32 ʱ������ AlphaBlend
	BOOL bPreMultiplied;				//�� Bpp = 32 ʱ��RGB ͨ���Ƿ��Ѿ�Ԥ�ȳ˹� Alpha ͨ��
	COLORREF clrTransparent;			//�� Bpp = 24 ʱ��͸��ɫ
	BOOL bShared;						//�Ƿ�����Ϊ TRUE���ؼ�����ʱ���������� hBitmap��
	BOOL bLTR;							//ͼƬ֡�Ƿ��Ǵ����������У����Ϊ FALSE����ͼƬ֡���ϵ������У�
	int nFrameWidth;
	int nFrameHeight;
	FRAMEINFO expanding;
	FRAMEINFO collapsing;
} BUTTONINFO, *PBUTTONINFO, *LPBUTTONINFO;

//������Ϣ�ӿ�
#define MSM_CLEARDATA					(WM_USER + 100)
#define MSM_INSERTGROUP					(WM_USER + 101)
#define MSM_INSERTITEM					(WM_USER + 102)
#define MSM_GETCHECKEDITEMS				(WM_USER + 103) //���Ѿ���ѡ��items��д��������
#define MSM_SETGROUP					(WM_USER + 104)
#define MSM_SETITEM						(WM_USER + 105)
#define MSM_SERIALIZE					(WM_USER + 106)
#define MSM_DESERIALIZE					(WM_USER + 107)
#define MSM_SUSPENDLAYOUT				(WM_USER + 108) //��ʱ���᲼�֣��ڴ��ڼ���ӽڵ㣬�ؼ����᳢���ػ�
//#define MSM_RESUMELAYOUT				(WM_USER + 109) //�������᲼�֣���ʱ�ؼ���ʼ���� (obsolete)
#define MSM_SETCHECKSTATE				(WM_USER + 110) //ȫ��ѡ��/��ѡ
#define MSM_REVERSEALL					(WM_USER + 111) //ȫ����ѡ
// -----------------
// [message id gap]
// -----------------
#define MSM_GETGROUPWIDTH				(WM_USER + 115) //��ȡ Group width
#define MSM_GETGROUPCHECKEDITEMSCOUNT	(WM_USER + 116) //��ȡĳ�� group �� checked items count
#define MSM_GETCHECKEDITEMSCOUNT		(WM_USER + 117) //��ȡ���е� checked items count
#define MSM_SERIALIZE_MEM				(WM_USER + 118) //���������л���ָ�����ڴ���
#define MSM_DESERIALIZE_MEM				(WM_USER + 119) //��һ���ڴ��з����л���������
#define MSM_GETGROUPHANDLE				(WM_USER + 120) //��ȡĳ�� Group �ľ��
#define MSM_GETITEMHANDLE				(WM_USER + 121)	//��ȡĳ�� Item  �ľ��
#define MSM_GETGROUPSCOUNT				(WM_USER + 122) //��ȡ Groups Count
#define MSM_GETGROUPITEMSCOUNT			(WM_USER + 123) //��ȡĳ�� Group �� ItemsCount
#define MSM_GETTOTALITEMSCOUNT			(WM_USER + 124) //��ȡ�ܵ� ItemsCount
#define MSM_GETGROUP					(WM_USER + 125) //��ȡ Group ��Ϣ
#define MSM_GETITEM						(WM_USER + 126) //��ȡ Item  ��Ϣ
#define MSM_GETSTYLE					(WM_USER + 127) //��ȡ���� Style ��Ϣ�����Ǵ�����ʽ����
#define MSM_SETSTYLE					(WM_USER + 128) //�������� Style
#define MSM_SETONESTYLE					(WM_USER + 129) //���õ��� Style ��״̬
#define MSM_GETBKGNDCOLOR				(WM_USER + 130) //��ȡ�ؼ�����ɫ
#define MSM_SETBKGNDCOLOR				(WM_USER + 131) //���ÿؼ�����ɫ
#define MSM_GETIMAGELIST				(WM_USER + 132) //��ȡ�ؼ��� ImageList
#define MSM_SETIMAGELIST				(WM_USER + 133)	//���ÿؼ��� ImageList
#define MSM_GETFONT						(WM_USER + 134) //������WM_GETFONT���� WM_SETFONT ���棬ԭ����
#define MSM_SETFONT						(WM_USER + 135) //����ᵼ�¶Ի����������ؼ����嶼��ΪSystem����
#define MSM_SETGROUPSIMAGE				(WM_USER + 136) //�������� Groups ��Image
#define MSM_GETCHECKSTATE				(WM_USER + 137) //��ȡ��ǰ�ؼ���ѡ��״̬
#define MSM_SETGROUPWIDTH				(WM_USER + 138) //����Group��ȣ����ܵ����������²��֣�
#define MSM_SETITEMSSIZE				(WM_USER + 139) //����Item�ߴ磨���ܵ����������²��֣�
#define MSM_GROUPCLEAR					(WM_USER + 140) //��ĳ�� Group �� Items ���
#define MSM_DELETEGROUP					(WM_USER + 141) //ɾ��ĳ�� Group
#define MSM_DELETEITEM					(WM_USER + 142) //ɾ��ĳ�� Item
#define MSM_GETLAYOUTINFO				(WM_USER + 143) //��ȡĬ�ϲ�����Ϣ
#define MSM_SETLAYOUTINFO				(WM_USER + 144) //����Ĭ�ϲ�����Ϣ
#define MSM_LAYOUTBYLINESIZE			(WM_USER + 145) //���ݴ��ڿ�Ⱥ� LineSize �������ò���
#define MSM_CLICKCHECKBOX				(WM_USER + 146) //�û�������ܵ� checkbox��
#define MSM_GETANIMATIONINFO			(WM_USER + 147) //��ȡ������Ϣ
#define MSM_SETANIMATIONINFO			(WM_USER + 148) //���ö�����Ϣ
#define MSM_REFRESHCHECKSTATE			(WM_USER + 149) //���¿ؼ��ڲ�ά���� CheckState ״̬�����������ͼ��
#define MSM_HITTEST						(WM_USER + 150) //�������
#define MSM_SETBUTTONINFO				(WM_USER + 151) //���� ButtonInfo
#define MSM_GETGROUPCOLORS				(WM_USER + 152) //��ȡĬ�ϵ� GroupColors�������Ǿ����ĳ�� Group��
#define MSM_SETGROUPCOLORS				(WM_USER + 153) //����Ĭ�ϵ� GroupColors�������赱ǰ������ Group color��
#define MSM_GETITEMCOLORS				(WM_USER + 154) //��ȡĬ�ϵ� ItemColors �������Ǿ����ĳ�� Item��
#define MSM_SETITEMCOLORS				(WM_USER + 155) //����Ĭ�ϵ� ItemColors �������赱ǰ���е� Item color��

typedef struct tagNM_MULSEL_HDR
{
	HWND hwndFrom;
	UINT idFrom;
	UINT code;
	HMSGROUP hGroup;			//�¼��� Group
	HMSITEM	hItem;				//�¼��� Item
	UINT oldState;				//checkState
	UINT newState;
} NMMSHDR, *LPNMMSHDR;

//
// Notify Codes
//
#define MSN_CHECKSTATECHANGE	1 //�ܵ� CheckBox �Ĺ�ѡ״̬�ѷ����仯
#define MSN_GROUPEXPAND			2 //��δ����
#define MSN_GROUPEXPANDING		3 //��δ����
#define MSN_GROUPCOLLAPSE		4 //��δ����
#define MSN_GROUPCOLLAPSING		5 //��δ����
#define MSN_CHECKEDITEMSCHANGE	6 //����ѡ�е� Items ���ݷ����仯


//��Ϣ��
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
// ��ȡ����
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
// ����ֻ�����ԣ���ר����Ϣ��
//
#define MulSel_SetReadOnly(hCtl, bReadOnly) \
	MulSel_SetOneStyle(hCtl, MSS_READONLY, bReadOnly, FALSE)

//
// pLayoutInfo ��һ��Ĭ����Ϣ���û���Ȼ���Զ� Group ָ���Զ���Ĳ�����Ϣ��
//

#define MulSel_GetLayoutInfo(hCtl, pLayout) \
	SendMessage((hCtl), MSM_GETLAYOUTINFO, 0, (LPARAM)(pLayout))

#define MulSel_SetLayoutInfo(hCtl, pLayout, bRedraw) \
	SendMessage((hCtl), MSM_SETLAYOUTINFO, MAKEWPARAM((bRedraw), 0), (LPARAM)(pLayout))

//
// �����ڵ����ռ���ʱ�����ʹ���Ϣ���� nLineSize <= 0 ʱ��
// ��ʹ�õ�ǰ�� nLineSize ��չ item ���
//
#define MulSel_LayoutByLineSize(hCtl, nLineSize, bResizeItems, bRedraw) \
	SendMessage((hCtl), MSM_LAYOUTBYLINESIZE, MAKEWPARAM((bRedraw), 0), (LPARAM)MAKELONG(nLineSize, bResizeItems))


#define MulSel_GroupClear(hCtl, hGroup, bNotify, bRedraw) \
	SendMessage((hCtl), MSM_GROUPCLEAR, MAKEWPARAM((bRedraw), (bNotify)), (LPARAM)(hGroup))

//
// ɾ�� group / item
//

#define MulSel_DeleteGroup(hCtl, hGroup, bNotify, bRedraw) \
	SendMessage((hCtl), MSM_DELETEGROUP, MAKEWPARAM((bRedraw), (bNotify)), (LPARAM)(hGroup))

#define MulSel_DeleteItem(hCtl, hItem, bNotify, bRedraw) \
	SendMessage((hCtl), MSM_DELETEITEM, MAKEWPARAM((bRedraw), (bNotify)), (LPARAM)(hItem))


// �û�������ܵġ�CheckBox
// bNotify: �Ƿ��򸸴��ڷ��� WM_NOTIFY ֪ͨ
// bRedraw: �Ƿ���¿ؼ�����ͼ

#define MulSel_ClickCheckBox(hCtl, bNotify, bRedraw) \
	SendMessage((hCtl), MSM_CLICKCHECKBOX, MAKEWPARAM((bRedraw), (bNotify)), 0)

//
// ��ȡ/���ö�����Ϣ
//

#define MulSel_GetAnimationInfo(hCtl, pInfo) \
	SendMessage((hCtl), MSM_GETANIMATIONINFO, 0, (LPARAM)(pInfo))

#define MulSel_SetAnimationInfo(hCtl, pInfo) \
	SendMessage((hCtl), MSM_SETANIMATIONINFO, 0, (LPARAM)(pInfo))


//
// ˢ�¿ؼ��ڲ�ά����״̬�����������ͼ�����������Ӻ��޸��ӽڵ�����У�
// bNotify ��Ϊ FALSE����ؼ��ڲ�״̬�����޷�׼ȷ�����û��Կؼ����޸ģ�
// ���ô���Ϣ�󣬽��Ὣ�ؼ��ڲ��� CheckState ״̬�����趨Ϊ��ȷ״̬��
//

#define MulSel_RefreshCheckState(hCtl) \
	SendMessage((hCtl), MSM_REFRESHCHECKSTATE, 0, 0)


//
// �������
//

#define MulSel_HitTest(hCtl, pHitInfo) \
	SendMessage((hCtl), MSM_HITTEST, 0, (LPARAM)(pHitInfo))


//
// ������ת��ť��Ϣ(����)
//

#define MulSel_SetButtonInfo(hCtl, pBtnInfo, bRedraw) \
	SendMessage((hCtl), MSM_SETBUTTONINFO, MAKEWPARAM((bRedraw), 0), (LPARAM)(pBtnInfo))


//
// ��ȡ������Ĭ����ɫ
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
// ������ ClockCtrl
//

//HIT_NULL �Ѿ���ǰ�涨��

#define HIT_HOURPTR			1 //����ʱ��
#define HIT_MINUTEPTR		2 //���з���
#define HIT_CLOCKCENTER		3 //����ʱ�ӵ����ģ���ʱ������Ӧ��

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
	int hour;		//ʱ��ı���Сʱ
	int minute;		//ʱ��ı��ķ���
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

//��ȡ�������϶�ָ��ʱ����С��λ��Ĭ��Ϊ5���ӣ�
#define Clock_GetMinuteUnit(hCtl) \
	((int)SendMessage((hCtl), CLM_GETMINUTEUNIT, 0, 0))

#define Clock_SetMinuteUnit(hCtl, nUnit) \
	((int)SendMessage((hCtl), CLM_SETMINUTEUNIT, (WPARAM)(nUnit), 0))

#define Clock_SetStyle(hCtl, style, bRedraw) \
	SendMessage((hCtl), CLM_SETSTYLE, MAKEWPARAM((bRedraw), 0), (LPARAM)(style)))

#define Clock_GetStyle(hCtl) \
	((UNIT)SendMessage((hCtl), CLM_GETSTYLE, 0, 0))

//��ȡ�����õ������ʱ�����壨��λΪ��������Ĭ��Ϊ5���ӣ�
#define Clock_GetHitErrBuffer(hCtl) \
	((int)SendMessage((hCtl), CLM_GETHITERRBUFFER, 0, 0))

#define Clock_SetHitErrBuffer(hCtl, nBufMinutes) \
	((int)SendMessage((hCtl), CLM_SETHITERRBUFFER, (WPARAM)(nBufMinutes), 0))

#define Clock_SetOneStyle(hCtl, style, bOn, bRedraw) \
	((int)SendMessage((hCtl), CLM_SETONESTYLE, MAKEWPARAM((bRedraw), (bOn)), (LPARAM)(style)))

#define Clock_SetReadOnly(hCtl, bReadOnly)\
	Clock_SetOneStyle((hCtl), MSS_READONLY, (WPARAM)(bReadOnly), FALSE)

//
// slider �ķ���
//

#define DIRECTION_V			0 //��ֱ����
#define DIRECTION_H			1 //ˮƽ��


//
// Message
//

#define SLSPACE_TL			0x01	//Top or Left;
#define SLSPACE_BR			0x02	//Bottom or Right;
#define SLSPACE_BOTH		(SLSPACE_TL | SLSPACE_BR)

//
// SLM_SETSPACE : ��������߾� 
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
// SLM_SETDIRECTION : ���÷���
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
	int diff;		//�϶����루�����ɸ���
} NMSLHDR, *LPNMSLHDR;

//
// Notify Codes
//
#define SLN_DROPDOWN		1

//
// Macros:
//
//
// SLM_SETSPACE : ��������߾� 
// 
// wParam: flags; which space
// lParam: HIWORD top-left Space, LOWORD: bottom-right Space;
// Return: 
#define Slider_SetSpace(hCtl, flags, nSpaceTL, nSpaceBR) \
	SendMessage((hCtl), SLM_SETSPACE, (WPARAM)(flags), MAKELPARAM((nSpaceBR), (nSpaceTL)))

#define Slider_GetSpace(hCtl) \
	((int)SendMessage((hCtl), SLM_GETSPACE, 0, 0))

//
// SLM_SETDIRECTION : ���÷���
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
// ��������/
//

#define IMSC_MULSEL			0x00000001
#define IMSC_CLOCK			0x00000002
#define IMSC_SLIDER			0x00000004

BOOL MULSELCTL_API InitMulSelControls(UINT nIMSC);
ATOM MULSELCTL_API GetClassAtom(UINT nWhichClass);
//�������Ķ�ѡ�ؼ���ȣ��߶����⣩
int MULSELCTL_API GetIdealMulSelCtlWidth(LPMSLAYOUTINFO pLayout);

//��ȡ�� slider ��صĿؼ����ù����
HCURSOR MULSELCTL_API GetSliderCursor(UINT direction);

//
// �� Unicode �� ANSI��char*��֮�以ת
//
int MULSELCTL_API UnicodeToAnsi(LPCWSTR lpWideCharStr, LPSTR lpMultiByteStr, int cbMultiByte);
int MULSELCTL_API AnsiToUnicode(LPCSTR lpMultiByteStr, LPWSTR lpWideCharStr, int cchWideChar);

//�ָ������Ĭ��ֵ��8 bytes��
#pragma pack(pop)
//#pragma pack(show)

#ifdef __cplusplus
} //__END_OF_ extern "C" {}
#endif