# A QT Latex Editor

## 简介
用QT实现一个所见即所得的Latex编辑器，能够在图形化界面的IDE里面，采用类似Word的方式，所见即所得书写文档，生成Latex语法的源文件（.tex文件）。

将此文件传递到服务器端，保存到数据库中，编译成pdf文件返回客户端显示。 

## 使用技术

- CMake
- QT 6.7.0
- KDE FrameWork6
- Glog

## 实现功能

与后端通过 HTTP 协议进行传输,将 .tex 文件传输到后端进行编译,并将编译结果展示到前端中,编辑器支持代码搜索,代码折叠,保存与未保存对比,查找最近打开文件,从服务器端下载文件到本地

## 参考代码

- [Kate](https://github.com/KDE/kate)