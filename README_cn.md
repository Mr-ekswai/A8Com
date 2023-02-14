## A8串口调试助手是a8blog.com网站的一款使用直观，操作简单的串口调试软件

![Intra screenshot](screenshot_cn.jpg?raw=true)


## [下载编译后的Exe文件](https://a8blog.com/uart_rs232_debug.htm)

## 项目情况

* 直接Windows api编写，无需MFC支持
* 主要用C语言编写
* 使用Microsoft Visual Studio Community 2022 编译
* 没有外部依赖

## 主要特性：

* 超小执行文件，仅33kB，绿色软件无需安装。
* 支持CH340、PL2303、FT232、cp2102等USB转串口芯片的高波特率和自定义波特率传输。
* 支持usb转串口设备的动态拔出、插入监测。自动识别。无需重新关闭再打开本软件，也不会导致本软件crash。
* 支持HEX和ASCII的显示方式。
* 显示速度快，不易丢数据。
* 支持选择串口、改变波特率（可以输入任意波特率，只要串口支持）、数据位、停止位、校验位。
* 支持发送文件。
* 支持循环定时发送。
* 支持发送字符串后追加换行符。
* 更多信息可访问[https://a8blog.com/en_uart_rs232_debug.htm](https://a8blog.com/en_uart_rs232_debug.htm)
