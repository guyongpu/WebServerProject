# webserver4.0
在上一个版本的基础上，引入引入nocopyable，对时间轮进行封装，重写了RAII机制的锁，对MimeType使用pthread_once