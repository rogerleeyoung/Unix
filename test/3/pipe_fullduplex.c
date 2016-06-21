#include <stdio.h> 
#include <stdlib.h>
#include <errno.h>  
#include <unistd.h>  
#include <sys/socket.h>  
#include <sys/types.h> 
#include <string.h>
  
#define MAXLINE 255  
  
void error_msg_quit(char *string, int line)  
{  
    char msg[MAXLINE] = {0};  
    int len = 0;  
  
    sprintf(msg, "%s", string);  
    len = strlen(string);  
    snprintf(msg + len, strlen(strerror(errno)), ",line:%d,%s\n", line, strerror(errno));  
    fputs(msg, stdout);  
    exit(errno);  
}  
  
int main(int argc, char **argv)  
{  
    int fd[2], n;  
    char ch;  
    pid_t child_pid;  
  
    //create pipe  
    //pipe(fd);  
  
    //socketpair(AF_UNIX, SOCK_STREAM, 0, fd);//if donot set this option,it won't work properly.  
  
    if ((child_pid = fork()) == 0)  
    {  
        //child  
        sleep(3);  
        if ((n = read(fd[0], &ch, 1)) != 1)  
        {  
            error_msg_quit("read error", __LINE__);  
        }  
  
        printf("child read:%c\n", ch);  
        write(fd[0], "c", 1);  
        exit(0);  
    }  
  
    //parent  
    write(fd[1], "p", 1);
    if ((n = read(fd[1], &ch, 1)) != 1)  
    {  
        error_msg_quit("read error", __LINE__);  
    }  
  
    printf("parent read:%c\n", ch);  
  
    exit(0);  
  
}  