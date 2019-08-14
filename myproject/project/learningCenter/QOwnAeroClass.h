#ifndef QOWNAEROCLASS_H
#define QOWNAEROCLASS_H
#include<windows.h>
#include<QLibrary>
#include<QRect>
#ifndef DWM_BB_ENABLE
//*****************用于XP下的结构定义************
#define DWM_BB_ENABLE 0x00000001 // fEnable has been specified
#define DWM_BB_BLURREGION 0x00000002 // hRgnBlur has been specified
#define DWM_BB_TRANSITIONONMAXIMIZED 0x00000004 // fTransitionOnMaximized has been specified
typedef struct _DWM_BLURBEHIND {
    DWORD dwFlags;
    BOOL fEnable;
    HRGN hRgnBlur;
    BOOL fTransitionOnMaximized;
} DWM_BLURBEHIND, *PDWM_BLURBEHIND;
#endif

typedef struct _MARGINS {

    int cxLeftWidth; // width of left border that retains its size
    int cxRightWidth; // width of right border that retains its size

    int cyTopHeight; // height of top border that retains its size
    int cyBottomHeight; // height of bottom border that retains its size
} MARGINS, *PMARGINS;
typedef HRESULT (WINAPI* MyDwmIsCompositionEnabled)(BOOL *pBEnable);
typedef HRESULT (WINAPI* MyDwmExtendFrameIntoClientArea)(HWND hWnd,const MARGINS *pMargins);
typedef HRESULT (WINAPI* MyDwmEnableBlurBehindWindow)(HWND hWnd,const DWM_BLURBEHIND *pDWM_bulr);

class QOwnAeroClass
{
private:
    QOwnAeroClass(void);
    ~QOwnAeroClass(void);
    enum SysType { UNKNOW=0, WINME, WIN98, WIN2K, WINXP, VISTA, WIN7, };
public:
    //返回是否具有透明效果
    static bool IsCompositionEnabled();
    //取消透明效果
    static bool cancelAeroStyle(HWND hWnd);
    //设置全局透明效果
    static bool setAeroStyle(HWND hWnd,bool bFrame=true,int nPadding = 6, QRect* pNewRect = NULL);
    //获取系统版本信息
    static SysType getSysVersion();
    //DWM接口
    static MyDwmIsCompositionEnabled m_MyDwmIsCompositionEnabledFun;
    static MyDwmExtendFrameIntoClientArea m_MyDwmExtendFrameIntoClientAreaFun;
    static MyDwmEnableBlurBehindWindow m_MyDwmEnableBlurBehindWindowFun;
    //初始化DWM接口
    static bool InitDwmPort();
    //接口dll
    static QLibrary m_DwnLib;
private:

};

#endif // QOWNAEROCLASS_H
