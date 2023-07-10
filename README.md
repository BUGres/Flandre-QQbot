### Flandre-QQbot

本项目基于窗口点击，**不会被QQ风控**，首先请打开想代理的QQ群聊

请确保屏幕坐标(400,400)为聊天界面，bot将点击此处复制群聊信息

请确保屏幕坐标(400,700)为消息输入界面，bot将从此处输入回答

请确保QQ发送消息的方法为：Enter键直接发送消息

### 编译

请使用realease x64 编译，vs版本2019，**如更换vs版本请重新部署curl！**

### ChatGPT配置

请打开项目中的`Flandre-QQbot.cpp`

```c++
// 设置API密钥和请求URL
    const std::string api_key = "sk-???";//你的API key
    const std::string url = "https://api.openai.com/v1/chat/completions";//官方站需要翻墙，也可以输入国内镜像
```

生成改为Release **x64** ，编译器为VS2019，更换编译器需要部署新的 **libcurl**

Flandre的人格咒语在`Chat.h`中，可以更换为你喜欢的人格

### 6penAI绘画配置

请将您的apikey填写至`6pen.h`，需填写两处

使用方法：@flandre #d一个女孩

接受任务后，等待绘画完成，之后@flandre #a

#s命令可以快捷关机
