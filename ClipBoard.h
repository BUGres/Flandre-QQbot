#pragma comment(lib,"gdiplus.lib")
#include <GdiPlus.h>

using namespace Gdiplus;

void breakOut_H(int typeError) {//错误处理函数
    switch (typeError) {
    case 1:
        MessageBox(NULL, TEXT("错误1:这个错误很可能是文本指针操作不当造成的"), TEXT("frando-ru崩溃"), MB_OK);
        exit(1);
    case 2:
        MessageBox(NULL, TEXT("错误2:打开剪切板失败，可能是内存被锁定造成的"), TEXT("frando-ru崩溃"), MB_OK);
        exit(1);
    case 3:
        MessageBox(NULL, TEXT("错误3:剪切板内容不是CF_TXT，原因可能是frando-ru复制了图片文件"), TEXT("frando-ru崩溃"), MB_OK);
        exit(1);
    case 4:
        MessageBox(NULL, TEXT("错误4：没有找到包含目标群名称的文件"), TEXT("frando-ru错误"), MB_OK);
    }
}

BOOL ToClipBoard(char* str)//剪切板写入数据
{
    OpenClipboard(0);
    EmptyClipboard();
    HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, strlen(str) + 1);
    if (!hg)
    {
        CloseClipboard();
        return false;
    }
    memcpy(GlobalLock(hg), str, strlen(str) + 1);
    GlobalUnlock(hg);
    SetClipboardData(CF_TEXT, hg);
    CloseClipboard();
    GlobalFree(hg);
    return true;
}

char* ReadClipBoard() {//剪切板读取数据
    HANDLE hclip;
    char* pbuf = NULL;
    if (OpenClipboard(NULL) == 0)
    {
        breakOut_H(2);
    }
    if (!IsClipboardFormatAvailable(CF_TEXT))
    {
        printf("剪切板当中的数据类型不匹配!\n");
        CloseClipboard();
        breakOut_H(3);
    }
    hclip = GetClipboardData(CF_TEXT);
    pbuf = (char*)GlobalLock(hclip);
    GlobalUnlock(hclip);
    //printf("%s\n", pbuf);
    CloseClipboard();
    return pbuf;
}
/*    将图片写入剪贴板的原理大致是：先将图片转化为bitmap格式（因为剪贴板图片仅支持bitmap格式其他格式写不进去）
       这里使用 Gdiplus提供的类去进行转化.具体可以百度了解这个类，我就不过多介绍。
*/
static bool CopyFileToClipboard(const wchar_t* path)//参数一：图片的绝对路径
{
    bool result = false;

    GdiplusStartupInput    m_Gdistart;
    ULONG_PTR    m_GdiplusToken;
    GdiplusStartup(&m_GdiplusToken, &m_Gdistart, NULL);

    Gdiplus::Bitmap* gdibmp = Gdiplus::Bitmap::FromFile(path);
    if (gdibmp)
    {
        HBITMAP hbitmap;
        gdibmp->GetHBITMAP(0, &hbitmap);
        if (OpenClipboard(NULL))
        {
            EmptyClipboard();//清空剪贴板
            DIBSECTION ds;
            if (GetObject(hbitmap, sizeof(DIBSECTION), &ds))
            {
                HDC hdc = GetDC(HWND_DESKTOP);
                //create compatible bitmap (get DDB from DIB)
                HBITMAP hbitmap_ddb = CreateDIBitmap(hdc, &ds.dsBmih, CBM_INIT,
                    ds.dsBm.bmBits, (BITMAPINFO*)&ds.dsBmih, DIB_RGB_COLORS);
                ReleaseDC(HWND_DESKTOP, hdc);
                SetClipboardData(CF_BITMAP, hbitmap_ddb);
                DeleteObject(hbitmap_ddb);
                result = true;
            }
            CloseClipboard();
        }

        //cleanup:
        DeleteObject(hbitmap);
        delete gdibmp;
    }
    return result;
}