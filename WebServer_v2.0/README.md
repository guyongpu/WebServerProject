# Web服务器——HTTP状态机解析

## 程序说明
&emsp;&emsp;主要练习HTTP解析的状态机的使用。接收一个客户端请求，判断是否是一个正确的GET请求，并解析出相应字段。  
&emsp;&emsp;有两个状态机，主状态机和从状态机，分别解析出相关字段。  
&emsp;&emsp;注意一个地方，每次recv时，并没有把buffer给覆盖，而是继续加到buffer现有字段的后面，类似于append方式读取。  
&emsp;&emsp;当读取到构成一个完整的行（携带\r\n）时，然后开始进行解析，分两步：  
&emsp;&emsp;&emsp;&emsp;第一步，解析GET、 index.html、HTTP/1.1等信息  
&emsp;&emsp;&emsp;&emsp;第二步，解析Host信息  
&emsp;&emsp;其实就是按照请求消息的内容顺序解析储这4个字段。

## 运行方法
编译
~~~
g++ main.cpp -o main
直接运行也可以，默认ip为127.0.0.1,默认端口为8888
~~~
运行
~~~
curl 127.0.0.1:7777/index.html
~~~

运行结果：
~~~
客户端发起请求：
# 方式1：命令行curl方式
yongpu@ubuntu:~$ curl 127.0.0.1:7777/index.html
I get a correct result

# 方式2：浏览器
输入: 127.0.0.1:7777/index.html
浏览器页面无法显示结果，但是后台可以看到解析成功！
~~~

## 报文说明 
~~~
使用curl 127.0.0.1:8888/index.html 的请求报文如下：
----------------------------------------
GET /index.html HTTP/1.1
Host: 127.0.0.1:9999
User-Agent: curl/7.58.0
Accept: *//*


----------------------------------------
 
程序输出为：
----------------------------------------
The request method is GET
The request URL is :/index.html
the request host is: 127.0.0.1:9999
I can not handle this header
response:I get a correct result
----------------------------------------
~~~