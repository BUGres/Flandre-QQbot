#include <iostream>
#include <windows.h>
#include <Stringapiset.h>

#include <curl/curl.h>//必须是Realease x64

#include "StrClip.h"
#include "Chat.h"
#include "ClipBoard.h"

#define Enter 13
#define Ctrl 17
 
#define KeyAt 9
#define HistoryDialogSize 2000//聊天记录最大复制长度
#define AnswerSize 500//ai回答最大长度

using namespace std;

//保存生成post的字符串的一些预设
class PostManager {
public:
    string start;
    string end;
    string dialogStart;
    string dialogEnd;
    string dialogEnd_Add;
    PostManager() {
        start = "{\"model\": \"gpt-3.5-turbo\",\"messages\": [";
        end = "]}";
        dialogStart = "{\"content\":\"";
        dialogEnd = "\",\"role\" : \"user\"}";
        dialogEnd_Add = ",";
    }
};

// 定义回调函数
size_t write_callback(char* ptr, size_t size, size_t nmemb, std::string* userdata) {
    userdata->append(ptr, size * nmemb);
    return size * nmemb;
}

// 定义函数来调用chatgpt3.5模型
std::string call_chatgpt3_5(const std::string& input_text) {
    // 设置API密钥和请求URL
    const std::string api_key = "你的apikey";
    const std::string url = "https://api.openai.com/v1/chat/completions";

    // 设置POST请求的数据
    PostManager pm;
    string str(FrandreMagic);
    str = String_To_UTF8(str);
    const std::string post_data = pm.start + str + pm.dialogStart + input_text + pm.dialogEnd + pm.end;

    // 初始化curl
    CURL* curl = curl_easy_init();

    // 设置curl选项
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, post_data.length());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    // 设置HTTP头
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, ("Authorization: Bearer " + api_key).c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // 发送请求并接收响应
    std::string response_data;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
    CURLcode res = curl_easy_perform(curl);

    // 检查请求是否成功
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }

    // 清理curl和HTTP头
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    // 返回响应数据
    int tar = response_data.find("\"content\":\"") + 11;
    int end = response_data.find("\"},\"", tar);//"},"
    return response_data.substr(tar, end - tar);
}

//报错函数
void breakOut(int typeError) {//错误处理函数
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

//上线消息发送
void awake()
{
    char welcome[] = "flandre上线！";

    if (!ToClipBoard(welcome))
        breakOut(1);

    SetCursorPos(400, 700);
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(1000);
    keybd_event(17, 0, 0, 0);
    keybd_event('V', 0, 0, 0);
    keybd_event(17, 0, KEYEVENTF_KEYUP, 0);
    keybd_event('V', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(13, 0, 0, 0);
    keybd_event(13, 0, KEYEVENTF_KEYUP, 0);
}

//对话输出中心
void dialog(string input)
{
    string str(input);
    cout << "[Post]" + str + "\n";
    str = call_chatgpt3_5(String_To_UTF8(str));
    str = UTF8_To_String(str);
    cout << "[Echo]" + str + "\n";

    char fdialog[AnswerSize] = "";
    for (int i = 0; i < str.size(); i++) {
        fdialog[i] = str.at(i);
    }

    if (!ToClipBoard(fdialog))
        breakOut(1);

    keybd_event(17, 0, 0, 0);
    keybd_event('V', 0, 0, 0);
    keybd_event(17, 0, KEYEVENTF_KEYUP, 0);
    keybd_event('V', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(13, 0, 0, 0);
    keybd_event(13, 0, KEYEVENTF_KEYUP, 0);
}

//阅读文本的中心
void Read() {
    int count = 0;
    int countrem = 0;
    bool judge = 0;
    int judge0 = 0;
    char* read = ReadClipBoard();
    char sentence[HistoryDialogSize];
    char head[KeyAt] = { "@flandre" };//机器人响应的被@字段
    char toAnswer[AnswerSize];
s:
    for (count = 0; (*read != '\n') && (*read != '\0');) {//剪切板内容的一行->sentence[]，之后在结尾补充\0
        sentence[count] = *read;
        count++;
        read++;
    }
    sentence[count] = '\0';
    read++;

    for (count = 0; head[count] == sentence[count]; count++);//检查字符串和head[]是否匹配，出现匹配时judge0变成1，judge为true
    if (count == KeyAt - 1) {
        for (count = KeyAt; count < AnswerSize + 1; count++) {
            if (sentence[count] == '\0') {
                toAnswer[count - KeyAt] = '\0';
                countrem = count - KeyAt;
                break;
            }
            toAnswer[count - KeyAt] = sentence[count];
        }
        judge = true;
        judge0 = 0;
    }

    if (judge)//由于对话后面还有一个空行，所以要再过一行看看再下一行是不是\0，不是就continue
        judge0++;
    if (*read != '\0')goto s;

    if (strlen(toAnswer) != 0) {
        if (judge0 == 2) {//确认为最后一行了，judge0=2代表两行前是@机器人，这是唯一的，确认了确实被@了
            string str(toAnswer);
            dialog(str.substr(0, countrem - 1));//在这里植入对话的代码
        }
    }
}

void main() {
    start:
    printf("欢迎来到flandre的终端>.<\n1.发送上线消息并启动\n2.直接启动\n");
    int mode;
    scanf("%d", &mode);
    switch (mode) {
    case 1:
        awake();
        break;
    case 2:
        break;
    default:
        system("CLS");
        goto start;
    }
    printf("[INFO]已启动\n");
    for (;;) {//主循环
        SetCursorPos(400, 400);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);


        Sleep(1000);
        keybd_event(17, 0, 0, 0);
        keybd_event('A', 0, 0, 0);
        keybd_event(17, 0, KEYEVENTF_KEYUP, 0);
        keybd_event('A', 0, KEYEVENTF_KEYUP, 0);
        keybd_event(17, 0, 0, 0);
        keybd_event('C', 0, 0, 0);
        keybd_event(17, 0, KEYEVENTF_KEYUP, 0);
        keybd_event('C', 0, KEYEVENTF_KEYUP, 0);
        Sleep(1000);

        SetCursorPos(400, 700);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(1000);
        SetCursorPos(400, 400);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(1000);


        Read();//frando-ru对话发送

        Sleep(5000);//时间较短可能会会导致鼠标不能控制，少于3秒难以关掉程序
    }
}