#ifndef FILENAME_H
#define FILENAME_H
#include<iostream>
#include <windows.h>

#include "Chat_Picture.h"
#include "ClipBoard.h"
#include "StrClip.h"
#include "6Pen.h"
#endif

#define AnswerSize 2000

using namespace std;

//flandre prompt
const char* FrandreMagic = "{\"role\":\"system\",\"content\":\"你将扮演东方project中的芙兰朵露参与对话\"},";

string rem6PenID = "";

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
    const std::string api_key = "sk-";// apikey
    const std::string url = "https://api.chatanywhere.com.cn/v1/chat/completions";// 这个是一个镜像地址，需要自己换

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

    ToClipBoard(fdialog);

    keybd_event(17, 0, 0, 0);
    keybd_event('V', 0, 0, 0);
    keybd_event(17, 0, KEYEVENTF_KEYUP, 0);
    keybd_event('V', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(13, 0, 0, 0);
    keybd_event(13, 0, KEYEVENTF_KEYUP, 0);
}

void dialog_add(string input)
{
    string str(input);
    cout << "\t[Send]" + str + "\n";

    char fdialog[AnswerSize] = "";
    for (int i = 0; i < str.size(); i++) {
        fdialog[i] = str.at(i);
    }

    ToClipBoard(fdialog);

    keybd_event(17, 0, 0, 0);
    keybd_event('V', 0, 0, 0);
    keybd_event(17, 0, KEYEVENTF_KEYUP, 0);
    keybd_event('V', 0, KEYEVENTF_KEYUP, 0);
}

void dialog_send(string input)
{
    string str(input);
    cout << "[Send]" + str + "\n";

    char fdialog[AnswerSize] = "";
    for (int i = 0; i < str.size(); i++) {
        fdialog[i] = str.at(i);
    }

    ToClipBoard(fdialog);

    keybd_event(17, 0, 0, 0);
    keybd_event('V', 0, 0, 0);
    keybd_event(17, 0, KEYEVENTF_KEYUP, 0);
    keybd_event('V', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(13, 0, 0, 0);
    keybd_event(13, 0, KEYEVENTF_KEYUP, 0);
}

void picture_send()
{
    chat_picture* cp = C_P_L.Rand();
    dialog_add(cp->String);
    if (!CopyFileToClipboard(cp->Path)) {
        cout << "[Info]CopyFileToClipboard() false\n";
        return;
    }

    keybd_event(17, 0, 0, 0);
    keybd_event('V', 0, 0, 0);
    keybd_event(17, 0, KEYEVENTF_KEYUP, 0);
    keybd_event('V', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(13, 0, 0, 0);
    keybd_event(13, 0, KEYEVENTF_KEYUP, 0);
}

void DialogInput(std::string strinput) {
    string strinfo = "如果看见此信息说明程序出现错误！！！";
    if (strinput.at(0) == '#') {
        string dialog2send = "";
        switch (strinput.at(1)) {
        case 's':
            cout << "[ShutDown]" + '\n';
            strinfo = "1分钟后关机,flandre已下线,此操作不可逆";
            dialog_send(strinfo);
            system("shutdown -s -t 60");
            break;
        case 'd':
            strinput = strinput.substr(2, strinput.length());
            cout << "[Draw]" + strinput + '\n';
            rem6PenID = Post6pen(strinput);
            dialog2send = "任务已接受!id = " + rem6PenID;
            dialog_send(dialog2send);
            break;
        case 'a':
            cout << "[Ask]6Pen Ask for URL" + '\n';
            dialog2send = Get6pen(rem6PenID);
            dialog_send(dialog2send);
            break;
        case 'g':
            cout << "[Give]\n";
            picture_send();
            break;
        default:
            break;
        }
        return;
    }
    else
        dialog(strinput);
    return;
}