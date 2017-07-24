# STM32WorkSpace
## 硬件描述
STM32工作空间，硬件平台使用的两个硬件平台；
F0:STM32F03K6T6;
F4:使用的板子是使用了STM32F401RET6;

## 工作进度描述
### ARC4Test
使用的加密算法库是Xysslk开源加密算法库:http://xyssl.sourcearchive.com/downloads/0.9-2/
，特点是简单，小巧，全部是使用了标准的C语言编写的库，
### FlashEEPROM
对FlashEEPROM进行编程
参考的是ST官网的一个Package:STM32SnippetsF0:http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32snippets/stm32snippetsf0.html
### Verfint
使用ADC获取内部参考电压
![ADC测试电压时引脚配置](D:\GitHub\STM32WorkSpace\F0\STM32F03K6T6\Verfint\Graph\ADC测试电压时引脚配置.png)
### ThinkGate项目


# 串口调试助手
------------------
## 介绍
**一款使用 C# 及 WPF 框架编写的串口助手软件。该串口助手界面优雅、简洁，易于使用。软件实现了基本的串口通讯需要的功能，开发者可以基于此添加自定义的功能。此外，可以基于此开发出一些简单的串口控制类软件，进而与你的单片机或 Arduino 互动。**

## 项目主页
* [基于WPF开放源码的串口调试助手(https://github.com/ChrisLeeGit/SerialAssistant)](https://github.com/ChrisLeeGit/SerialAssistant)
 

## 基本功能
* 串口数据接收，可以采用多种模式显示接收到的数据：字符，十六进制等；
* 串口数据发送，可以手动/间隔自动发送；
* 保存串口接收到显示区的数据；
* 保存/加载软件配置；
* 独创的**简洁视图模式**， 便于用户专注于数据的接收和发送。


## 运行测试
### 启动初始化截图
![启动初始化截图](D:\GitHub\STM32WorkSpace\F0\STM32F03K6T6\Verfint\Graph\ADC测试电压时引脚配置.png)