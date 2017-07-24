# STM32WorkSpace
## 硬件介绍
**STM32工作空间，硬件平台使用的两个硬件平台；
* F0:STM32F03K6T6;
* F4:使用的板子是使用了STM32F401RET6;
**

## 工作进度描述
### ARC4Test
使用的加密算法库是Xysslk开源加密算法库:http://xyssl.sourcearchive.com/downloads/0.9-2/
，特点是简单，小巧，全部是使用了标准的C语言编写的库，
### FlashEEPROM
对FlashEEPROM进行编程
参考的是ST官网的一个Package:STM32SnippetsF0:http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32snippets/stm32snippetsf0.html
### Verfint
使用ADC获取内部参考电压
#### ADC测试电压时引脚配置
![ADC测试电压时引脚配置](https://github.com/Twsa/STM32WorkSpace/blob/master/F0/STM32F03K6T6/Verfint/Graph/1.png)
#### ADC电路连接图
![ADC测试电压时引脚配置](https://github.com/Twsa/STM32WorkSpace/blob/master/F0/STM32F03K6T6/Verfint/Graph/2.png)

### ThinkGate项目
