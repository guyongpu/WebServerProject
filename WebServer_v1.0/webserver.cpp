#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

using namespace std;

const int BUFFSIZE = 1024;
const int MAXLINK = 10; // 未经过处理的连接请求队列可以容纳的最大数目
const int DEFAULT_PORT = 9000; //默认端口

void deal_get_http(int connect_fd);

int main() {
    //参数1：family指明了协议族/域.   AF_INET:IPv4网络通信; AF_INET6:IPv6网络通信; AF_PACKET:链路层通信
    //参数2：type是套接口类型, 主要SOCK_STREAM字节流套接字 /  SOCK_DGRAM数据报套接字 /  SOCK_RAW原始套接字 /  SOCK_SEQPACKET有序分组套接字；
    //参数3：protocol一般取为0(缺省值);   IPPROTO_TCP：TCP传输协议;  IPPTOTO_UDP:UDP传输协议;   IPPROTO_SCTP:STCP传输协议;   IPPROTO_TIPCTCP:TIPC传输协议
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0); //正常情况返回0,异常返回-1
    if(socket_fd == -1){
        cout << "Create socket eoor" << endl;
        return -1;
    }

    struct sockaddr_in serv_adr;
    serv_adr.sin_family = AF_INET;                  //IPV4网络
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);   //服务器监听ip
    serv_adr.sin_port = htons(DEFAULT_PORT);        //监听端口

    if(bind(socket_fd, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1){
        cout << "Bind error" << endl;
        close(socket_fd);
        return 0;
    }

    if(listen(socket_fd, MAXLINK) == -1){ //最大并发数
        cout << "Listen error";
    }

    cout << "WebServer start...." << endl;

    while(1)
    {
        int connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL);

        if(connect_fd == -1){
            cout << "Accept error" << endl;
        }
        else{
            cout << "--------------------------------------------------------------------------" << endl;
            cout << "Connect success" << endl;
        }

        char buff[BUFFSIZE];
        memset(buff, '\0', sizeof(buff));
        recv(connect_fd, buff, BUFFSIZE-1, 0);
//        cout << "Recive message from client: " << endl << buff << endl;
        deal_get_http(connect_fd);
        close(connect_fd);
    }
    close(socket_fd);

    cout << "Close the server" << endl;

    return 0;
}

//发送html文件
void deal_get_http(int connect_fd)
{
    //获取html文件大小,open为高级I/O函数，配合sendfile使用
    string filename = "index.html";
    int fd = open(filename.c_str(),O_RDONLY);//消息体
    struct stat stat_buf;
    fstat(fd,&stat_buf);
    cout << filename << " size :" << stat_buf.st_size << endl; //输入文件长度

    //构造响应消息头
    string reshead = string("HTTP/1.0 200 OK\r\n");
    reshead = reshead + string("Content-Type: text/html;charset=UTF-8\r\n");
    reshead = reshead + string("Content-Length: ") + to_string(stat_buf.st_size) + string("\r\n\r\n");//写入文件长度

    send(connect_fd, reshead.c_str(), reshead.length(), 0); //发送响应头
    sendfile(connect_fd,fd,NULL, stat_buf.st_size);//零拷贝发送消息体  //发送文件
    close(fd); //关闭连接
}

