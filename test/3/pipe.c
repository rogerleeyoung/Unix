#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{

  int     fd[2], nbytes; 
  pid_t   childpid;
  char    string[] = "Hello, world!\n";
  char    readbuffer[80];
  pipe(fd);
  if(( childpid = fork() ) == 0)        /* 子进程是管道的写进程 */
  {
      sleep(10);
      close(fd[0]);      /*关闭管道的读端 */
      write(fd[1], string, strlen(string)); 
      exit(0);
  }
  else                           /* 父进程是管道的读进程 */
  {
      close(fd[1]);    /*关闭管道的写端 */
      nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
      printf("Received string: %s", readbuffer);
  }        
  return(0);
}

