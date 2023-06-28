## My First GUI Project

- CMake的基本用法
- Qt的基本用法、信号槽机制(观察者模式)
- Qt的基本控件、布局、事件处理
- Qt的LGPL协议研究: 可以以闭源方式发布Qt应用(静态链接方式亦可，需要提供中间产品.obj文件的获取渠道以保障Qt库可以被替换) [GNU Lesser General Public License (LGPL)](https://doc.qt.io/qt-5/lgpl.html)
- Qt静态链接库的编译: 官方提供的SDK静态编译方式不可用，需要自行从源码编译
- MSVC的命令行编译方式， 64位系统用 "x64 Native Tools Command Prompt"， 32位系统用 "x86 Native Tools Command Prompt"。 注意不是 "Developer Command Prompt" / "Developer PowerShell"，后面这两个是x86，避免踩坑。

## 项目预览

![Screenshoot](Screenshoot.png)

## ChatGPT聊天记录

https://shareg.pt/OegN52O

# 相关链接

- [Qt：windows下Qt安装教程](https://zhuanlan.zhihu.com/p/634273644)
- [用静态链接qt库的方式使用qt（上）](https://systemisbusy.info/blog/2019/09/28/%E7%94%A8%E9%9D%99%E6%80%81%E9%93%BE%E6%8E%A5qt%E5%BA%93%E7%9A%84%E6%96%B9%E5%BC%8F%E4%BD%BF%E7%94%A8qt%EF%BC%88%E4%B8%8A%EF%BC%89/)
- [用静态链接Qt库的方式使用Qt（下）](https://systemisbusy.info/blog/2019/10/13/%e7%94%a8%e9%9d%99%e6%80%81%e9%93%be%e6%8e%a5qt%e5%ba%93%e7%9a%84%e6%96%b9%e5%bc%8f%e4%bd%bf%e7%94%a8qt%ef%bc%88%e4%b8%8b%ef%bc%89/)
- [关于LGPL授权能否静态链接的几个说法](https://bbs.csdn.net/topics/330104257)
- [Qt5静态编译时configure的static和static-runtime有什么区别](https://blog.csdn.net/piaopiaolanghua/article/details/118060886)
- [Qt5如何静态编译和部署](https://www.cnblogs.com/cheungxiongwei/p/8251537.html)