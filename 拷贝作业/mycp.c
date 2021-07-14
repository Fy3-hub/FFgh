#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void mycp(char *src,char *dest,char *sizel, char *numl)
{
	int sfd = open(src,O_RDONLY);
	int dfd = open(dest,O_WRONLY|O_CREAT,0664);

	int size = atoi(sizel);
	int num = atoi(numl);

	lseek(sfd,size*num,SEEK_SET);
	lseek(sfd,size*num,SEEK_SET);

	char buffer[size];
	bzero(buffer,sizeof(buffer));

	size_t rsize = read(sfd,buffer,sizeof(buffer));
	size_t wrize = write(dfd,buffer,rsize);

	close(sfd);
	close(dfd);
}

int main(int argc,char** argv)
{
	if(argc <5)
	{
		printf("error..\n");
	}
	mycp(argv[1],argv[2],argv[3],argv[4]);
	return 0;
}

