#include "QOwnAeroClass.h"
#include <QDebug>

MyDwmIsCompositionEnabled QOwnAeroClass::m_MyDwmIsCompositionEnabledFun=NULL;
MyDwmExtendFrameIntoClientArea QOwnAeroClass::m_MyDwmExtendFrameIntoClientAreaFun=NULL;
MyDwmEnableBlurBehindWindow QOwnAeroClass::m_MyDwmEnableBlurBehindWindowFun=NULL;

QLibrary QOwnAeroClass::m_DwnLib;

QOwnAeroClass::QOwnAeroClass(void)
{
}


QOwnAeroClass::~QOwnAeroClass(void)
{
}
//初始化DWM接口，Theme接口
bool QOwnAeroClass::InitDwmPort()
{
    m_MyDwmEnableBlurBehindWindowFun = NULL;
    m_MyDwmExtendFrameIntoClientAreaFun = NULL;
    m_MyDwmIsCompositionEnabledFun = NULL;

    if(m_DwnLib.isLoaded())
    {
        m_DwnLib.unload();
    }
    m_DwnLib.setFileName("Dwmapi.dll");
    if(!m_DwnLib.load())
        return false;

    m_MyDwmIsCompositionEnabledFun = (MyDwmIsCompositionEnabled)m_DwnLib.resolve("DwmIsCompositionEnabled");
    m_MyDwmExtendFrameIntoClientAreaFun = (MyDwmExtendFrameIntoClientArea)m_DwnLib.resolve("DwmExtendFrameIntoClientArea");
    m_MyDwmEnableBlurBehindWindowFun = (MyDwmEnableBlurBehindWindow)m_DwnLib.resolve("DwmEnableBlurBehindWindow");

    if(m_MyDwmEnableBlurBehindWindowFun == NULL ||
        m_MyDwmExtendFrameIntoClientAreaFun == NULL ||
        m_MyDwmIsCompositionEnabledFun == NULL)
    {
        return false;
    }

    return true;
}
//返回是否具有透明效果
bool QOwnAeroClass::IsCompositionEnabled()
{
    //return false;
    BOOL bCompEnabled = FALSE;
    SysType sysType;
    sysType = getSysVersion();
    if(sysType <VISTA)
        return false;
    if(m_MyDwmIsCompositionEnabledFun == NULL)
    {
        if(!InitDwmPort())
        {
            qDebug() << "QOwnAeroClass::IsCompositionEnabled InitDWM fail!!!!";
            return false;
        }
    }
    m_MyDwmIsCompositionEnabledFun(&bCompEnabled);
    if(bCompEnabled)
    {
        return true;
    }
    else
        return false;
}
//取消透明效果
bool QOwnAeroClass::cancelAeroStyle(HWND hWnd)
{
    if(::IsWindow(hWnd))
    {
        SysType sysType;
        sysType = getSysVersion();
        if(sysType < VISTA)
            return false;

        if(m_MyDwmExtendFrameIntoClientAreaFun == NULL
            || m_MyDwmEnableBlurBehindWindowFun == NULL)
        {
            if(!InitDwmPort())
            {
                qDebug() << "QOwnAeroClass::cancelAeroStyle InitDWM fail!!!!";
                return false;
            }
        }
        MARGINS margins = {0};	//将取消
        m_MyDwmExtendFrameIntoClientAreaFun(hWnd, &margins);

        //
        DWM_BLURBEHIND bb = {0};
        bb.dwFlags = DWM_BB_ENABLE /*| DWM_BB_BLURREGION*/;
        bb.fEnable = false;
        bb.hRgnBlur = NULL;
        m_MyDwmEnableBlurBehindWindowFun(hWnd, &bb);
        return true;
    }
    return false;
}
//设置全局透明效果
bool QOwnAeroClass::setAeroStyle(HWND hWnd,bool bFrame,int nPadding, QRect* pNewRect)
{
    if(!::IsWindow(hWnd))
        return false;

    SysType sysType;
    sysType = getSysVersion();
    if(sysType <VISTA)
        return false;
    //先取消在设置
    cancelAeroStyle(hWnd);
    //全屏效果
    if(bFrame)
    {
        if(m_MyDwmExtendFrameIntoClientAreaFun == NULL)
        {
            if(!InitDwmPort())
            {
                qDebug() << "QOwnAeroClass::setAeroStyle InitDWM fail!!!!";
                return false;
            }
        }
        MARGINS margins = {-1};	//将效果
        m_MyDwmExtendFrameIntoClientAreaFun(hWnd, &margins);
    }
    //局部效果
    else
    {
        DWM_BLURBEHIND blurBehind = { 0 };

        blurBehind.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
        blurBehind.fEnable = true;
        //blurBehind.fTransitionOnMaximized = TRUE;
        RECT winRect,NewRect;

        ::GetWindowRect(hWnd,&winRect);
        if(pNewRect != NULL)
        {
            NewRect.top = nPadding;
            NewRect.left = nPadding;
            NewRect.bottom = pNewRect->height()-nPadding;
            NewRect.right = pNewRect->width()-nPadding;
        }
        else{
            NewRect.top = nPadding;
            NewRect.left = nPadding;
            NewRect.bottom = (winRect.bottom - winRect.top)-nPadding;
            NewRect.right = (winRect.right - winRect.left)-nPadding;
        }
        /*winRect.left += 6;
        winRect.top += 6;
        winRect.bottom -= 6;
        winRect.right -= 6;*/
        HRGN hRgn = ::CreateRectRgn(NewRect.left,NewRect.top,NewRect.right,NewRect.bottom);

        blurBehind.hRgnBlur = hRgn;

        m_MyDwmEnableBlurBehindWindowFun(hWnd,
            &blurBehind);
    }
    return true;
}

//获取系统版本信息
QOwnAeroClass::SysType QOwnAeroClass::getSysVersion()
{
    OSVERSIONINFO Version;
    ZeroMemory(&Version,sizeof(OSVERSIONINFO));
    Version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&Version);
    if (Version.dwPlatformId==VER_PLATFORM_WIN32_NT)
    {
        if((Version.dwMajorVersion==5)&&(Version.dwMinorVersion==0))
        {
            return WIN2K;
        }else if((Version.dwMajorVersion==5)&&(Version.dwMinorVersion>0))
        {
            return WINXP;
        }else if((Version.dwMajorVersion==6)&&(Version.dwMinorVersion==0))
            return VISTA;
        else if((Version.dwMajorVersion>=6))
            return WIN7;
    }
    else if(Version.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)
    {
        if ((Version.dwMajorVersion == 4) && (Version.dwMinorVersion < 90) )
        {
            return WIN98;
        }
        if ((Version.dwMajorVersion == 4) && (Version.dwMinorVersion >= 90) )
        {
            return WINME;
        }
    }
    return UNKNOW;
}
