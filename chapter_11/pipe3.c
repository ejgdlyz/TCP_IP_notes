#include <stdio.h>
#include <unistd.h>

/*
    管道例子: 双向通信，双管道
*/

#define BUF_SIZE 30

int main(int argc, char const *argv[])
{
    int fds1[2], fds2[2];
    char str1[] = "who are you?";
    char str2[] = "Thank you for your message.";
    char buf[BUF_SIZE];
    pid_t pid;

    pipe(fds1), pipe(fds2);
    pid = fork();

    if (pid == 0)  // 子进程 向管道传输字符串
    {
        write(fds1[1], str1, sizeof(str1));
        read(fds2[0], buf, BUF_SIZE);
        printf("Child Proc output: %s\n", buf);
    }
    else
    {
        read(fds1[0], buf, BUF_SIZE);
        printf("Parent proc output: %s\n", buf);
        write(fds2[1], str2, sizeof(str2));
        sleep(3);  // 无实际意义，为防止父进程终止而延迟
    }
    
    return 0;
}
