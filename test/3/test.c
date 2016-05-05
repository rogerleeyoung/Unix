/********************************************************************************
    > File Name: test.c
    > Author: liyscut
    > Mail: liyang.nenu@gmail.com 
    > Created Time: 2016年05月05日 星期四 12时30分25秒
********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    char buffer[]="abcabcabcabc\0";
    char* buf=buffer;
    int len;
    printf("%s\n",buf);
    len=strlen(buf);
    printf("strlen(buf)=%d\n",len);
    printf("%s\n",buf);
    len=int(sizeof(*buf));
    printf("sizeof(buf)=%d\n",len);
    len=(int)(sizeof(char*));
    printf("sizeof(char*)=%d\n",len);
    return 0;
}
