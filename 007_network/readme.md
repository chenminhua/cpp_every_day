### socket系统调用
```c
#include<sys/socket.h>
// 创建一个socket文件用作通信，返回文件描述符
int socket(int domain, int type, int ptotocol);
```
domain指定通信协议，使用ipv4则选择AF_INET。

type 指定通信语义，支持SOCK_STREAM, SOCK_DGRAM, SOCK_RAW。

protocol 指定具体的协议。此参数取值IPPROTO_IP（值为0）或IPPROTO_TCP（值为6）代表TCP协议。取值为0也能代表TCP协议，是因为protocol为0时代表取给定domain的type中的默认协议，而TCP是AF_INET｜AF_INET6中SOCK_STREAM类型的默认协议。

### bind系统调用 (man 2 bind)
```c
// 给socket系统调用创建的socket绑定名字，其实就是把ip:port绑定到这个socket上
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

// 内核用于保存地址的结构体
struct sockaddr {
	__uint8_t	sa_len;		/* total length */
	sa_family_t	sa_family;	/* [XSI] address family */
	char		sa_data[14];	/* [XSI] addr value (actually larger) */
};

struct sockaddr_in {
	__uint8_t	sin_len;
	sa_family_t	sin_family;
	in_port_t	sin_port;
	struct	in_addr sin_addr;
	char		sin_zero[8];
};

server.sin_family = AF_INET;    // ipv4
server.sin_addr.s_addr = INADDR_ANY;    // 0.0.0.0
server.sin_port = htons(5000);    // <arpa/inet.h>
```

### listen系统调用
```c
// 告诉内核准备好接入请求，并定义pending队列容量。
int listen(int sockfd, int backlog);
```

其中backlog参数定义pending的连接队列的最大长度。 如果连接在队列已满的情况下到达，客户端可能会收到ECONNREFUSED指示的错误。如果底层协议支持重传，则可以忽略请求，重试可能会成功。

### accept系统调用 (man 2 accept)
在完成三次握手后，server端TCP会创建一个sock结构来与client端的scoket进行一对一的数据传递。但这个sock进存在于内核中，server端用户进程还无法使用。进程要想使用这个新的连接，必须调用accept系统调用生成一个与sock关联的socket，然后进程通过对这个socket进行recv、send等操作来实现与client端的数据传递。连接建立完成后，服务器端的应用进程会从listening socket上得到可读事件通告，这时应用进程就可以调用accept系统调用。accept如果调用成功则返回一个新的文件描述符，用于代表被接收的socket。

```c
int accept(int sockfd, struct sockaddr * restrict address, socklen_t *restrict address_len)
```


### recv系统调用
```c
ssize_t recv(int newsockfd, void *buffer, size_t length, int flags);
// buffer为读取到的请求，size_t为读取长度，flags为读取方式，0表示 process out-of-band data
```

### close系统调用
记住处理完请求一定要关闭掉newsockfd

```c
int close(int fileds);
```

### connect系统调用（客户端）
```c
int connect(int sockfd, const struct sockaddr *address, socklen_t address_len);
// sockfd是客户端打开的socket,address是服务端地址。连接成功返回0，否则返回-1
```

### send系统调用（客户端）
```c
ssize_t send(int socket, const void *buffer, size_t length, int flags);
```

### select 系统调用
```c
int select(int nfds, fd_set *restrict reasdfds, fd_set *restrict writefds, fd_set *restrict errorfds, struct timeval *restrict timeout);

#include <stdio.h>
#include <string.h>
#include <sys/select.h>

int main(int argc, char *argv[]){
    int fd = 0;
    char buf[11];
    int ret, sret;

    fd_set readfds;
    struct timeval timeout;

    while (1) {
        // 初始化一组fdset
        FD_ZERO(&readfds);
        // 将文件描述符加入fdset
        FD_SET(fd, &readfds);

        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        sret = select(8, &readfds, NULL, NULL, &timeout);

        if (sret == 0) {
            printf("sret = %d\n", sret);
            printf(" timeout\n");
        } else {
            printf("sret = %d\n", sret);
            memset((void *) buf, 0, 11);
            ret = read(fd, (void *)buf, 10);
            printf("ret = %d\n", ret);
            if (ret != -1) {
                printf(" buf = %s\n", buf);
            }
        }
    }
    return 0;
}
```