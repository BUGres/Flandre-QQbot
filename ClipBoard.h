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