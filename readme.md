# Tinyhttpd4cpp
## 说明
本例子仅处于自我学习目的
## 使用
```bash
./build.sh
./bin/httpd
```
然后使用浏览器访问127.0.0.1:4000
## 版本ver1
修改Tinyhttpd为c++代码

### 1. 下个目标
1. 学习Webbench的使用
2. 加入线程池

### 2. BUG修复
* 在配合webbench的时候发现服务器总是会异常中断，最后发现是由于`SIGPIPE`导致。忽略了`SIGPIPE`和`SIGALERM`信号
=======
这里使用的是one tcp-connection per thread。接下来的目的是学习压测工具。

## 版本ver2
添加了线程池

### 1. 下个目标
1. 加入日志系统
2. 添加BlockingQueue

## 版本ver3
改善了一部分代码结构，更加容易理解看懂

完成了日志系统，剥离自muduo（去掉了自己看不懂的东西），有时间的话修改为日志滚动类
添加BlockingQueue

### 1. 下个目标
1. 修改为reactor模式
2. 学习lighttpd，完善业务功能
