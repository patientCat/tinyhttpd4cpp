# Tinyhttpd4cpp
## 说明
本例子仅处于自我学习目的
## 版本0.0.1
修改Tinyhttpd为c++代码
<<<<<<< HEAD

BUG修复
* 在配合webbench的时候发现服务器总是会异常中断，最后发现是由于`SIGPIPE`导致。忽略了`SIGPIPE`和`SIGALERM`信号
=======
这里使用的是one tcp-connection per thread。接下来的目的是学习压测工具。
