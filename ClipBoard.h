#pragma comment(lib,"gdiplus.lib")
#include <GdiPlus.h>

using namespace Gdiplus;

void breakOut_H(int typeError) {//��������
    switch (typeError) {
    case 1:
        MessageBox(NULL, TEXT("����1:�������ܿ������ı�ָ�����������ɵ�"), TEXT("frando-ru����"), MB_OK);
        exit(1);
    case 2:
        MessageBox(NULL, TEXT("����2:�򿪼��а�ʧ�ܣ��������ڴ汻������ɵ�"), TEXT("frando-ru����"), MB_OK);
        exit(1);
    case 3:
        MessageBox(NULL, TEXT("����3:���а����ݲ���CF_TXT��ԭ�������frando-ru������ͼƬ�ļ�"), TEXT("frando-ru����"), MB_OK);
        exit(1);
    case 4:
        MessageBox(NULL, TEXT("����4��û���ҵ�����Ŀ��Ⱥ���Ƶ��ļ�"), TEXT("frando-ru����"), MB_OK);
    }
}

BOOL ToClipBoard(char* str)//���а�д������
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

char* ReadClipBoard() {//���а��ȡ����
    HANDLE hclip;
    char* pbuf = NULL;
    if (OpenClipboard(NULL) == 0)
    {
        breakOut_H(2);
    }
    if (!IsClipboardFormatAvailable(CF_TEXT))
    {
        printf("���а嵱�е��������Ͳ�ƥ��!\n");
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
/*    ��ͼƬд��������ԭ������ǣ��Ƚ�ͼƬת��Ϊbitmap��ʽ����Ϊ������ͼƬ��֧��bitmap��ʽ������ʽд����ȥ��
       ����ʹ�� Gdiplus�ṩ����ȥ����ת��.������԰ٶ��˽�����࣬�ҾͲ�������ܡ�
*/
static bool CopyFileToClipboard(const wchar_t* path)//����һ��ͼƬ�ľ���·��
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
            EmptyClipboard();//��ռ�����
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