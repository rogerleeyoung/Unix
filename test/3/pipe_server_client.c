#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

#define MAXLINE 1000

void client(int, int);
void server(int, int);

/*server*/
void server(int readfd, int writefd)
{
	int		fd;
	ssize_t	n;
	char	buff[MAXLINE+1];

		/* 4read pathname from IPC channel */
	if ( (n = read(readfd, buff, MAXLINE)) == 0)
	{
		printf("end-of-file while reading pathname");
		exit(1);
	}
	buff[n] = '\0';		/* null terminate pathname */

	if ( (fd = open(buff, O_RDONLY)) < 0) {
			/* 4error: must tell client */
		snprintf(buff + n, sizeof(buff) - n, ": can't open, %s\n",
				 strerror(errno));
		n = strlen(buff);
		write(writefd, buff, n);

	} else {
			/* 4open succeeded: copy file to IPC channel */
		while ( (n = read(fd, buff, MAXLINE)) > 0)
			write(writefd, buff, n);
		close(fd);
	}
}

/*client*/
void client(int readfd, int writefd)
{
	size_t	len;
	ssize_t	n;
	char	buff[MAXLINE];

		/* 4read pathname */
	fgets(buff, MAXLINE, stdin);
	len = strlen(buff);		/* fgets() guarantees null byte at end */
	if (buff[len-1] == '\n')
		len--;				/* delete newline from fgets() */

		/* 4write pathname to IPC channel */
	write(writefd, buff, len);

		/* 4read from IPC, write to standard output */
	while ( (n = read(readfd, buff, MAXLINE)) > 0)
		write(STDOUT_FILENO, buff, n);
}

int main(int argc, char **argv)
{
	int		pipe1[2], pipe2[2];
	pid_t	childpid;

	/* create two pipes */
	pipe(pipe1);
	pipe(pipe2);

	if ( (childpid = fork()) == 0) {		/* child */
		close(pipe1[1]);
		close(pipe2[0]);

		server(pipe1[0], pipe2[1]);
		exit(0);
	}
		/* 4parent */
	close(pipe1[0]);
	close(pipe2[1]);

	client(pipe2[0], pipe1[1]);

	waitpid(childpid, NULL, 0);		/* wait for child to terminate */
	exit(0);
}