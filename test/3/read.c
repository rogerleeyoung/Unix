/********************************************************************************
    > File Name: read.c
    > Author: liyscut
    > Mail: liyang.nenu@gmail.com 
    > Created Time: 2016年05月05日 星期四 12时25分28秒
********************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define SIZE 100


int main(void)
{
    int n;
    char buf[SIZE];
    while(n=read(STDIN_FILENO,buf,SIZE))   //读取标准输入到buf中，返回读取字节数
        if(n!=write(STDOUT_FILENO,buf,n)) //把buf 写到标准输出中
            perror("write error");
    if(n<0) 
        perror("read error");   
    return 0;

}
