#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc ,char **argv)
{

	//判断传几个参数的方案
	int n;
	if(argc < 3)
	{
		printf("data error...\n");
		exit(-1);
	}
	else if(argc == 3)
	{
		n = 5;    // 用户未指定，默认创建5个进程
	}
	else if(argc == 4)
	{
		if(argv[3] < 0 || argv[3] >100)
		{
			printf("error....\n");
		}
		else
		{
			n = argv[3];
    	}
	}
	else
	{
		printf("data error...\n");
	}

	int size;
	int fd1 = open(argv[1],O_RDONLY);  // 打开源文件
	size = lseek(fd1,0,SEEK_END);  //获取文件大小
	if(size % n ==0)
	{
		size = size/n;
	}
	else
	{
		size = size/n;
		size = size+1;
	}
	char size_nNum[n][szie];  //将文件内容分块装到二维数组中
	for(int j=0;j<n;j++)
	{
        fread(size_nNum[j][size],size,n,argv[3]);
    }
	//创建相应的子线程
	pid_t  pid;
	for(int i=0;i<n;i++)
	{
		pid = fork();
		if(pid == 0)
		{
			break;
		}
	}

	if(pid ==0)
	{
		printf("now is running\n");
		for(int i=0;i<n;i++)   //利用execl进行重载工作
		{
		execl("/home/colin/0601第五阶段/21-0709/mycp.c","mycp.c",argv[1],argv[2],size_nNum[i][size],NULL);
		}
	}

	//回收僵尸进程
	pid_t wpid;
	int status;
	int ecode;

	while((wpid = waitpid(-1,&status,WNOHANG)) !=-1)
	{
		if(wpid >0)
		{
			//判断是否是正常退出
			if(WIFEXITSTATUS(status))
			{
				//获取退出码
				ecode = WEXITSTATUS(status);
				printf("wait successly..\n");
			}
		}
		else
		{
			printf("try again...\n");
			usleep(100);
		}
	}

	return 0;
}
