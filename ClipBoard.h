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