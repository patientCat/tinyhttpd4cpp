# Tinyhttpd4cpp
## 说明
本例子仅处于自我学习目的
本例子算作总结了下这一学期学到的所有东西的集合。糅杂了比较多的东西。下面简单对目录做一个介绍
* httpd_ver1 是我阅读完tinyhttpd后转为c++的结果。其网络模型采用的是each TcpConnection per thread的概念
* httpd_ver2 依然是一个简单的http服务器，网络模型采用线程池
* httpd_ver3 添加了日志功能
* httpd_ver4 模仿mudu写了自己的网络库

大致路线从: 单纯的多线程——线程池(前面俩部分都是阻塞IO编程)——reactor+线程池+非阻塞编程。
这也是大多数网络编程学习者的一个学习路线。我认为按照我这样的思路对自己学到的东西做一个完整的东西出来对自己还是提升比较大的。

## 版本ver1
### 使用
简单配合shell脚本和cmake写了一个脚本
```bash
./build.sh
./bin/httpd
```
然后使用浏览器访问127.0.0.1:4000
### 介绍
修改Tinyhttpd为c++代码

#### 1. 下个目标
1. 学习Webbench的使用
2. 加入线程池

#### 2. BUG修复
* 在配合webbench的时候发现服务器总是会异常中断，最后发现是由于`SIGPIPE`导致。忽略了`SIGPIPE`和`SIGALERM`信号
=======
这里使用的是one tcp-connection per thread。接下来的目的是学习压测工具。

### 版本ver2
添加了线程池

#### 1. 下个目标
1. 加入日志系统
2. 添加BlockingQueue

### 版本ver3
改善了一部分代码结构，更加容易理解看懂

完成了日志系统，剥离自muduo（去掉了自己看不懂的东西），有时间的话修改为日志滚动类
添加BlockingQueue

#### 1. 下个目标
1. 修改为reactor模式
2. 学习lighttpd，完善业务功能

### 版本ver4
前面的版本我自己也不想过多去介绍，基本上只能算是玩具编程。到了版本4中自己写网络库才算是到了真正考验自己基本功的地方。
这里面涉及如下几个概念。
1. 非阻塞编程
2. reactor模式
3. 利用function/bind实现回调机制

详情请查看我的博客
1. [singsing库01](https://blog.csdn.net/weixin_43468441/article/details/93783842)
2. [singsing库02](https://blog.csdn.net/weixin_43468441/article/details/93788166)
3. [singsing库03](https://blog.csdn.net/weixin_43468441/article/details/94406374)
4. [singsing库04](https://blog.csdn.net/weixin_43468441/article/details/94407752)

#### 1. 下个目标
到达目前的阶段我准备暂停一下，这里算是做了一个基本的小的网络库。可能一些方面还不完善，但这里主要还是用作自己学习muduo的目的。

下一阶段准备利用muduo写完一个中型的完整的项目。然后去学习lighttpd，在自己的网络库中添加http的组件。最终目标是完成一个比较有完整度的http服务器，然后在上面运行自己的博客或者简历。

#### 2. 目标完成
1. 完成了一个简单的httpServer，简单实现了http解析中的几个协议。有时间看一一下前端知识，最终能够配合前端完成自己全栈工程师的梦想。
2. 完成了一个简单的银行存储系统。[github](https://github.com/patientCat/ABCBank)
3. 完成了异步日志的学习。[github](https://github.com/patientCat/logger4cpp)

#### 3. 下个目标
下个目标希望自己暂时定的方向是Go，Docker，Redis。目前对Go语言的兴趣比较大，Redis其次，Docker最末。
下面的目标按照难易程度进行排序
1. 做自己的年度总结，以及Github上部署自己的简历
2. 最近一直在学习Go语言。下一年想投入更多的时间再Go上面
3. 实现简单的Redis
4. Docker的学习
5. 了解下分布式系统的相关知识


