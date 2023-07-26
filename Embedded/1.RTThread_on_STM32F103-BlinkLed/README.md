## 尝试用Clion做嵌入式开发

### 引子

给一款旧设备刷机过程中了解到 [Breed](https://www.right.com.cn/forum/thread-161906-1-1.html), 好奇嵌入式设备的启动过程, 遗憾的是Breed是闭源的, 继而找到了 [Breed固件逆向](https://blog.csdn.net/fjh1997/article/details/120834258) 这篇文档。顺腾摸瓜找到了 [rt-boot](https://github.com/zhaohengbo/rt-boot) 作者发布的一系列技术文章:

- [开源的多线程bootloader](https://www.right.com.cn/forum/forum.php?mod=viewthread&tid=372225)
- [rt-boot技术预览，一个全新的开源多线程跨平台bootloader](https://www.right.com.cn/FORUM/thread-359098-1-1.html)
- [rt-uboot，一个开源的IPQ/QCA/AR/MTK/RT/QEMU多线程uboot mod及其实现](https://www.right.com.cn/forum/thread-337363-1-1.html)
- [手把手教你搭建多线程bootloader开发环境(基于rt-uboot)](https://www.right.com.cn/forum/thread-341079-1-1.html)

令我惊奇的是 rt-boot 的作者发布这些文章的时候还是个初中生，膜拜~~

继而了解到国产微型开源实时操作系统 [RT-Thread](https://www.rt-thread.org/document/site/#/), 之前有过对X86启动过程的研究([HelloSys](https://github.com/cfgxy/HelloSys)), 主要是汇编, 突然有了想跑个Demo试试的冲动

### 过程

一开始是用大佬推荐的 RT-Thread Studio， 也通过[qemu-arm-xpack](https://github.com/xpack-dev-tools/qemu-arm-xpack)软件模拟出了STM32F4的运行环境跑起了Demo，在移植到STM32F1的QEMU环境过程中发现跑不起来，最后调试发现是qemu-arm-xpack对STM32F1的串口支持不完整，RT-Thread卡在了启动过程中向串口打印版本号那里。且RT-Thread中对QEMU调试器很多参数没办法修改。

遂找到 [稚晖君](https://www.zhihu.com/people/zhi-hui-64-54) 写的 [配置CLion用于STM32开发](https://zhuanlan.zhihu.com/p/145801160) , 改用熟悉的CLion

后来了解到除了QEMU之外还有 [Renode](https://renode.io/) 可以模拟 STM32, Renode文档写的太粗套, 找到了以下几篇入门文章:

- [Renode_牧羊女说的博客](https://blog.csdn.net/deliapu/category_11364490.html)

尝试跑了一下，嗯有日志了，嗯居然还能以描述文件的方式配置外设，嗯能闪灯了，是这个味了~~



